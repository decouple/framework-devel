<?hh // partial
namespace Test\DBAL;
use Decouple\Test\TestCase;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;
use Decouple\DBAL\Schema\SchemaInterface;
class SchemaTest extends TestCase {
  public function execute() : void {
    $driver = new DPDOMySQLDriver();
    $connected = $driver->connect(Map {
      "dbname" => "decouple",
      "type" => "mysql",
      "host" => "localhost"
    }, "decouple", "secret");
    $schema = $driver->schema('decouple');
    $failed = false;
    if(!$schema instanceof SchemaInterface) {
      $failed = true;
    }
    $this->assertEquals($failed, false);
  }
}
