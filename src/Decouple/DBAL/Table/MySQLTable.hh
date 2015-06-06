<?hh // strict
namespace Decouple\DBAL\Table;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\Create\MySQLTableCreate;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Table\Alter\MySQLTableAlter;
use Decouple\DBAL\Table\Alter\TableAlterInterface;
use Decouple\DBAL\Query\MySQLQuery;
class MySQLTable implements TableInterface {
  public function __construct(protected string $name, protected SchemaInterface $schema) {

  }
  public function create((function(TableCreateInterface):void) $callback) : bool {
    $create = new MySQLTableCreate($this);
    $callback($create);
    return $create->execute();
  }
  public function getCreate() : MySQLTableCreate {
    return new MySQLTableCreate($this);
  }
  public function alter((function(TableAlterInterface):void) $callback) : bool {
    $alter = new MySQLTableAlter($this);
    $callback($alter);
    return $alter->execute();
  }
  public function getAlter() : MySQLTableAlter {
    return new MySQLTableAlter($this);
  }
  public function drop() : bool {
    return $this->schema->driver()->execute(sprintf('DROP TABLE IF EXISTS %s', $this->name));
  }
  public function delete() : MySQLQuery {
    $query = new MySQLQuery($this);
    return $query->delete();
  }
  public function exists() : bool {
    $statement = $this->schema->driver()->prepare('SHOW TABLES LIKE ?');
    $statement->bindParam(1, Vector {$this->name});
    if($statement->rowCount()) {
      return true;
    }
    return false;
  }
  public function insert(Map<string,mixed> $data) : int {
    $query = new MySQLQuery($this);
    return $query->insert($data);
  }
  public function update(Map<string,mixed> $data) : MySQLQuery {
    $query = new MySQLQuery($this);
    return $query->update($data);
  }
  public function select(?Vector<string> $fields=null) : MySQLQuery {
    return (new MySQLQuery($this))->select($fields);
  }
  public function selectColumn(string $field) : MySQLQuery {
    return (new MySQLQuery($this))->selectColumn($field);
  }
  public function getName() : string {
    return $this->name;
  }
  public function schema() : SchemaInterface {
    return $this->schema;
  }
}
