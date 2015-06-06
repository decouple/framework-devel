<?hh // strict
namespace Decouple\DBAL\Driver;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Statement\StatementInterface;
use Decouple\DBAL\Connector\ConnectorInterface;
interface DriverInterface {
  public function connect(Map<string,string> $params, string $username, string $password, Map<string,mixed> $options=Map {}) : bool;
  public function schema(string $name) : SchemaInterface;
  public function isConnected() : bool;
  public function hasErrors() : bool;
  public function throwsExceptions() : bool;
  public function throwExceptions(bool $throws) : void;
  public function getErrors() : Vector<DriverException>;
  public function prepare(string $query): StatementInterface;
  public function connector() : ConnectorInterface;
  public function execute(string $query) : bool;
}
