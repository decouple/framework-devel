<?hh // strict
namespace Test\DBAL;
use Decouple\Console\CLI\CLI;
use Decouple\Test\TestCase;
use Decouple\DBAL\DPDO\DPDOConnector;
class ConnectorTest extends TestCase {
  public function execute() : void {
    $connector = new DPDOConnector();
    $connected = $connector->connect(Map {
      "dbname" => "decouple",
      "type" => "mysql",
      "host" => "localhost"
    }, "decouple", "secret");
    $this->assertEquals($connected, true);
  }
}
