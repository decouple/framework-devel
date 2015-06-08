<?hh // strict
namespace Test\DBAL;
use Decouple\Test\TestCase;
use Decouple\Common\Contract\DB\Query;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;
class QueryTest extends TestCase {
  public function execute() : void {
    $driver = new DPDOMySQLDriver();
    $connected = $driver->connect(Map {
      "dbname" => "decouple",
      "type" => "mysql",
      "host" => "localhost"
    }, "decouple", "secret");
    $schema = $driver->schema('decouple');
    $table = $schema->table('articles');
    $query = $table->select();
    $failed = false;
    if(!$query instanceof Query) {
      $failed = true;
    }
    $this->assertEquals($failed, false);
  }
}
