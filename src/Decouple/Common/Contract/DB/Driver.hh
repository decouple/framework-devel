<?hh // strict
namespace Decouple\Common\Contract\DB;
use Exception;
interface Driver {
  public function connect(Map<string,string> $params, string $username, string $password, Map<string,mixed> $options=Map {}) : bool;
  public function schema(string $name) : Schema;
  public function isConnected() : bool;
  public function hasErrors() : bool;
  public function throwsExceptions() : bool;
  public function throwExceptions(bool $throws) : void;
  public function getErrors() : Vector<Exception>;
  public function prepare(string $query): Statement;
  public function connector() : Connector;
  public function execute(string $query) : bool;
}
