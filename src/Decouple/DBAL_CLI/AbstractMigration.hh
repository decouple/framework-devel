<?hh // strict
namespace Decouple\DBAL_CLI;
use Exception;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL\Table\Structure\TableStructure;
abstract class AbstractMigration implements MigrationInterface {
  protected string $name = '';
  protected TableStructure $table;
  public function __construct(protected SchemaInterface $schema) {
    if(!is_null($this->name)) {
      throw new Exception("Invalid migration name");
    }
    $this->table = new TableStructure($this->name);
  }
  public function getName() : string {
    return $this->name;
  }
  public function toString() : string {
    return $this->table->toString();
  }
}
