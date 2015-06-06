<?hh // strict
namespace Decouple\DBAL\Table\Create;
use Decouple\DBAL\Table\MySQLTable;
use Decouple\DBAL\Table\Structure\MySQLTableStructure;
use Decouple\DBAL\Table\Structure\TableColumnInterface;
class MySQLTableCreate extends MySQLTableStructure implements TableCreateInterface {
  public function __construct(protected MySQLTable $table) {
    parent::__construct($table->getName());
  }

  public function execute($alter=false): bool {
    $definition = "";
    $fields = [];
    $after = [];
    $definitions = [];
    foreach ($this->columns as $name => $column) {
      $type = $column->getType();
      $definitions[] = $this->columnDefinition($column, $alter);
      $tmp = $this->columnAfter($column);
      if(!empty($tmp)) {
        $after[] = $tmp;
      }
    }
    $definition = sprintf("%s,\n%s", implode(",\n", $definitions), implode(",\n", $after));
    $fields = implode(',', $fields);
    $query = sprintf("CREATE TABLE `%s` (\n%s\n)", $this->table->getName(), $definition);
    return $this->table->schema()->execute($query);
  }
}
