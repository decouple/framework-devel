<?hh // strict
namespace Decouple\DBAL\Query;
use Decouple\DBAL\Table\MySQLTable;
use Decouple\Common\Contract\DB\Statement;
use Decouple\Common\Contract\DB\Query;
use Exception;
class MySQLQuery implements Query {
  protected string $action;
private Map<string, mixed> $data;
  private Vector<string> $selectFields;
  private Vector<Vector<mixed>> $whereData;
  private Map<string, string> $orderData;
  private int $limitMin = 0;
  private int $limitMax = 0;
  public string $query_raw;

  public function __construct(protected MySQLTable $table) {
    $this->action = 'select';
    $this->data = Map {};
    $this->selectFields = Vector {};
    $this->whereData = Vector {};
    $this->orderData = Map {};
    $this->query_raw = '';
  }

  public function selectColumn(string $field): MySQLQuery {
    $this->action = 'select';
    $this->selectFields->add($field);
    return $this;
  }

  public function select(?Vector<string> $fields = null): MySQLQuery {
    $this->action = 'select';
    if (is_null($fields)) {
      $fields = Vector {"*"};
    }
    if (!is_null($fields)) {
      $this->selectFields->addAll($fields);
    }
    return $this;
  }

  public function update(Map<string, mixed> $data): MySQLQuery {
    $this->action = 'update';
    $data['modified'] = time();
    $this->data->setAll($data);
    return $this;
  }

  public function delete(bool $soft = false): MySQLQuery {
    if (!$soft) {
      $this->action = 'delete';
      return $this;
    } else {
      $this->action = 'update';
      $data = Map {"deleted" => time()};
      $this->data->setAll($data);
      return $this;
    }
  }

  public function insert(Map<string, mixed> $data): int {
    $this->action = 'insert';
    $this->data->setAll($data);
    $this->execute();
    $id = $this->table->schema()->driver()->connector()->lastInsertId();
    return $id;
  }

  public function where(
    string $field,
    string $comp,
    mixed $value,
  ): MySQLQuery {
    $this->whereData->add(Vector {$field, $comp, $value});
    return $this;
  }

  public function whereAll(
    KeyedTraversable<string, string> $array,
  ): MySQLQuery {
    foreach ($array as $key => $where) {
      if (count($where) == 3) {
        $this->where($where[0], $where[1], $where[2]);
      } else {
        if (is_string($key) && (is_string($where) || is_numeric($where))) {
          $this->where($key, '=', $where);
        }
      }
    }
    return $this;
  }

  public function orderBy(
    string $field,
    string $direction = 'DESC',
  ): MySQLQuery {
    $this->orderData->set($field, $direction);
    return $this;
  }

  public function limit(int $min=0, int $max=25) : Query {
    $this->limitMin = $min;
    $this->limitMax = $max;
    return $this;
  }

  public function build(): PreparedQuery {
    $query = '';
    if ($this->action == 'select') {
      $query =
        'SELECT '.
        implode(',', $this->selectFields).
        ' FROM '.
        $this->table->getName();
    } else if ($this->action == 'update') {
      $query = 'UPDATE '.$this->table->getName().' SET ';
      foreach ($this->data as $var => $val) {
        if ($val instanceof Raw) {
          $query .= $var.' = '.(string) $val->getValue();
        } elseif ($var !== 'modified') {
          $query .= $var.' = :'.$var.', ';
        }
      }
      $query .= 'modified = FROM_UNIXTIME(:modified)';
    } else if ($this->action == 'insert') {
      $columns = [];
      $values = [];
      foreach ($this->data as $var => $val) {
        $columns[] = '`'.$var.'`';
        if ($val instanceof Raw) {
          $values[] = $val->getValue();
        } else {
          $values[] = ':'.$var;
        }
      }
      $columns = implode(', ', $columns);
      $values = implode(', ', $values);
      $query =
        'INSERT INTO '.
        $this->table->getName().
        ' ('.
        $columns.
        ') VALUES ('.
        $values.
        ')';
    } else if ($this->action == 'delete') {
      $query = 'DELETE FROM '.$this->table->getName();
    }

    $whereFields = Map {};
    if (count($this->whereData) > 0) {
      $query .= ' WHERE ';
      foreach ($this->whereData as $vec) {
        $field = (string) $vec[0];
        $operator = (string) $vec[1];
        $value = $vec[2];
        $standIn = ':'.$field;
        if (is_null($value)) {
          $val = null;
        } elseif (is_array($value)) {
          $val = json_encode($value);
        } elseif ($value instanceof Raw) {
          $val = $value->getValue();
          $standIn = (string) $val;
        } else {
          $val = $value;
        }
        $whereFields[(string) $vec[0]] = $val;

        $query .= sprintf('`%s`%s%s AND ', $field, $operator, $standIn);
      }
      $query = substr($query, 0, -4);
    }

    if($this->action == 'select') {
      if ($this->orderData->count()) {
        $query .= ' ORDER BY ';
        $orderParts = Vector {};
        foreach ($this->orderData as $field => $dir) {
          $orderParts->add(sprintf('%s %s', $field, $dir));
        }
        $query .= implode(', ', $orderParts);
      }
      if($this->limitMax > 0) {
        $query .= sprintf(' LIMIT %s, %s', $this->limitMin, $this->limitMax);
      }
    }

    $fields = Map {};
    $fields->setAll($whereFields);
    $fields->setAll($this->data);
    return new PreparedQuery($query, $fields);
  }

  public function raw(mixed $value): Raw {
    return new Raw($value);
  }

  public function reset(): void {
    $this->selectFields = Vector {};
    $this->data = Map {};
    $this->whereData = Vector {};
    $this->action = 'select';
  }

  public function fetchAll(): Vector<Map<string, mixed>> {
    $fetched = $this->execute()->fetchAll();
    $result = Vector {};
    foreach ($fetched as $row) {
      $result[] = $row;
    }
    return $result;
  }

  public function first(): ?Map<string, mixed> {
    $this->limitMin = 0;
    $this->limitMax = 1;
    $fetched = $this->execute()->fetchAll();
    if(!count($fetched)) {
      return null;
    }
    return new Map($fetched[0]);
  }

  public function fetchColumn(int $column = 0): mixed {
    return $this->execute()->fetchColumn($column);
  }

  public function execute(): Statement {
    $build = $this->build();
    $statement = $this->table->schema()->driver()->prepare($build->query);
    $values = Map {};
    foreach ($build->values as $index => $value) {
      if ($value === '') {
        $values->set($index, null);
      } else if (!$value instanceof Raw) {
        $values->set($index, $value);
      }
    }
    $statement->execute($values);
    return $statement;
  }

  public function debugQuery(
    PreparedQuery $query,
    Map<string, mixed> $values,
  ): void {
    $sql = $query->query;
    foreach ($values as $str => $val) {
      if (is_string($val))
        $val = "'$val'";
      $sql = str_replace(':'.$str, $val, $sql);
    }
    echo $sql."\n";
  }
}
