<?hh // strict
namespace Decouple\DBAL_CLI;
use Exception;
use Decouple\Common\Contract\DB\Schema;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL\Table\Structure\TableStructure;
use Decouple\DBAL_CLI\Contract\Seed as SeedContract;
abstract class Seed implements SeedContract {
  public function __construct(protected Schema $schema) { }
}
