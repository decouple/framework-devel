<?hh // strict
namespace Test\DBAL;
use Decouple\Console\CLI\CLI;
use Decouple\Test\TestCase;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;
class DriverTest extends TestCase {
  public function __construct() {}
  public function execute() : void {
    $driver = new DPDOMySQLDriver();
    $connected = $driver->connect(Map {
      "host" => "localhost",
    }, "decouple", "secret");
    $this->assertEquals($connected, true);
    $schema = $driver->schema('decouple_test');
    if(!$schema->exists()) {
      $schema->create();
    }
    $this->assertEquals($schema->exists(), true);
  }
}
