<?hh // strict
namespace Decouple\DBAL_CLI;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\Structure\TableStructureInterface;
interface MigrationInterface {
  public function up(TableStructureInterface $table) : void;
  public function down(TableStructureInterface $table) : void;
  public function getName() : string;
  public function toString() : string;
}
