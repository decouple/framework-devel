<?hh // strict
namespace Decouple\DBAL_CLI;
use Exception;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL\Table\Structure\TableStructureInterface;
abstract class AbstractMigration implements MigrationInterface {
  protected string $name = '';
  protected TableStructureInterface $table;
  public function __construct(private SchemaInterface $schema) {
    if(empty($this->name)) {
      throw new Exception("Invalid migration name");
    }
    $this->table = $this->schema->table($this->name);
  }
  public function getName() : string {
    return $this->name;
  }
  public function toString() : string {
    $migration = new TableStructure($this->name);
    $this->up($migration);
    return $migration->toString();
  }
}
