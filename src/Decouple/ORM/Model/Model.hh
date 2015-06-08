<?hh // strict
namespace Decouple\ORM\Model;
use Decouple\Common\Contract\ORM\Model as ModelContract;
use Decouple\Common\Contract\DB\Schema;
use Decouple\Common\Contract\DB\Table;
use Decouple\Common\Contract\DB\Queryable;
use Decouple\Common\Contract\DB\Query;
use Decouple\Common\AbstractAttributeContainer;
use Exception;
abstract class Model extends AbstractAttributeContainer implements ModelContract {
  protected Table $table;
  protected string $name = '';
  public function __construct(protected Schema $schema) {
    if($this->name == '') {
      throw new Exception("Invalid model name provided");
    }
    $this->table = $this->schema->table($this->name);
    parent::__construct();
  }
  public function belongsTo(string $table, string $key, string $id): Query {
    return $this->table->schema()->table($table)->select()->where($id, '=', $this->getAttribute($key));
  }
  public function hasMany(string $table, string $key): Query {
    return $this->table->schema()->table($table)->select()->where($key, '=', $this->getAttribute('id'));
  }
  public function delete(bool $soft = false): Query {
    return $this->table->delete($soft);
  }
  public function fetchAll(): Vector<Map<string, mixed>> {
    return $this->table->fetchAll();
  }
  public function first(): ?Map<string, mixed> {
    return $this->table->first();
  }
  public function select(?Vector<string> $fields = null): Query {
    return $this->table->select($fields);
  }
  public function update(Map<string, mixed> $data): Query {
    return $this->table->update($data);
  }
  public function insert(Map<string, mixed> $data): int {
    return $this->table->insert($data);
  }
  public function where(string $field, string $comp, mixed $value): Query {
    return $this->table->where($field, $comp, $value);
  }
  public function whereAll(KeyedTraversable<string, string> $array): Query {
    return $this->table->whereAll($array);
  }
  public function limit(int $min = 0, int $max = 25): Query {
    return $this->table->limit($min, $max);
  }
  public function orderBy(string $field, string $direction): Query {
    return $this->table->orderBy($field, $direction);
  }
}
