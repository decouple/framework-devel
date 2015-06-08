<?hh // strict
namespace Decouple\Common\Contract\DB;
interface Connector {
  public function connect(Map<string,string> $params, string $username, string $password, Map<string,mixed> $options=Map {}) : bool;
  public function isConnected() : bool;
  public function hasErrors() : bool;
  public function throwExceptions(bool $throws) : void;
  public function throwsExceptions() : bool;
  public function lastInsertId() : int;
}
