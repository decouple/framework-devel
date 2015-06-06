<?hh // strict
namespace Decouple\DBAL\Schema;
use Decouple\DBAL\Driver\DriverInterface;
use Decouple\DBAL\Table\TableInterface;
interface SchemaInterface {
  public function exists() : bool;
  public function create() : bool;
  public function table(string $name) : TableInterface;
  public function driver() : DriverInterface;
  public function execute(string $query) : bool;
}
