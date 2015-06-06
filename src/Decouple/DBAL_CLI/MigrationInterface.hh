<?hh // strict
namespace Decouple\DBAL_CLI;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\Structure\TableStructure;
interface MigrationInterface {
  public function up() : void;
  public function down() : void;
  public function getName() : string;
  public function toString() : string;
}
