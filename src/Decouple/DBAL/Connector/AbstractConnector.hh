<?hh // strict
namespace Decouple\DBAL\Connector;
abstract class AbstractConnector implements ConnectorInterface {
  protected bool $throwsExceptions=false;
  protected bool $isConnected=false;
  protected Vector<ConnectorException> $errors;
  abstract public function connect(Map<string,string> $params, string $username, string $password, Map<string,mixed> $options=Map {}) : bool;
  public function isConnected() : bool {
    return $this->isConnected;
  }
  public function hasErrors() : bool {
    return $this->errors->count() ? true : false;
  }
  public function throwExceptions(bool $throws) : void {
    $this->throwsExceptions = $throws;
  }
  public function throwsExceptions() : bool {
    return $this->throwsExceptions;
  }
}
