<?hh // strict
namespace Test\DBAL;
use Decouple\Test\TestCase;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\CLI\Console;
class TableTest extends TestCase {
  public function execute() : void {
    $driver = new DPDOMySQLDriver();
    $connected = $driver->connect(Map {
      "dbname" => "decouple",
      "type" => "mysql",
      "host" => "localhost"
    }, "decouple", "secret");
    $schema = $driver->schema('decouple');
    $table = $schema->table('articles');
    $failed = false;
    if(!$table instanceof TableInterface) {
      $failed = true;
    }
    Console::output('Asserting Driver->schema()->table() returns instanceof Decouple\DBAL\Table\TableInterface');
    $this->assertEquals($failed, false);

    Console::output('Attempting to create articles table');
    $res = $table->create(function(TableCreateInterface $table) {
      $table->increments('id');
      $table->string('title')->unique();
      $table->text('content');
      $table->softDeletes();
      $table->timestamps();
    });
    $this->assertEquals($res, true);
  }
}
