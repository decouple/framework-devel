<?hh // strict
namespace Decouple\DBAL\Table;
use Decouple\DBAL\Query\QueryInterface;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\Create\MySQLTableCreate;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Table\Alter\MySQLTableAlter;
use Decouple\DBAL\Table\Alter\TableAlterInterface;
interface TableInterface {
  public function exists() : bool;
  public function create((function(TableCreateInterface):void) $callback) : bool;
  public function getCreate() : MySQLTableCreate;
  public function alter((function(TableAlterInterface):void) $callback) : bool;
  public function getAlter() : MySQLTableAlter;
  public function drop() : bool;
  public function selectColumn(string $field) : QueryInterface;
  public function select(?Vector<string> $fields=null) : QueryInterface;
  public function insert(Map<string,mixed> $data) : int;
  public function update(Map<string,mixed> $data) : QueryInterface;
  public function delete() : QueryInterface;
  public function getName() : string;
  public function schema() : SchemaInterface;
}
