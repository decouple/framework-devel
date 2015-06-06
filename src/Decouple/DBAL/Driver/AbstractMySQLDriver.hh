<?hh // strict
namespace Decouple\DBAL\Driver;
use Decouple\DBAL\Schema\MySQLSchema;
use Decouple\DBAL\Statement\StatementInterface;
abstract class AbstractMySQLDriver implements DriverInterface {
  protected bool $throwsExceptions=false;
  protected bool $isConnected=false;
  protected Vector<DriverException> $errors;
  abstract public function prepare(string $query): StatementInterface;
  public function isConnected() : bool {
    return $this->isConnected;
  }
  public function hasErrors() : bool {
    return $this->errors->count() ? true : false;
  }
  public function getErrors() : Vector<DriverException> {
    return $this->errors;
  }
  public function throwExceptions(bool $throws) : void {
    $this->throwsExceptions = $throws;
  }
  public function throwsExceptions() : bool {
    return $this->throwsExceptions;
  }
  public function schema(string $name) : MySQLSchema {
    return new MySQLSchema($name, $this);
  }
}
