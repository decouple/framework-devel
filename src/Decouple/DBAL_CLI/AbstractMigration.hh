<?hh // strict
namespace Decouple\DBAL_CLI;
use Exception;
use Decouple\Common\Contract\DB\Schema;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL\Table\Structure\TableStructure;
abstract class AbstractMigration implements MigrationInterface {
  protected string $name = '';
  protected TableStructure $table;
  public function __construct(protected Schema $schema) {
    if($this->name == '') {
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
