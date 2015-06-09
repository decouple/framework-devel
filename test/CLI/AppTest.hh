<?hh // partial
namespace Test\CLI;
use Decouple\CLI\App;
use Decouple\CLI\Request\Request;
use Decouple\Decoupler\Decoupler;
use Decouple\Registry\Paths;
use Decouple\CLI\Console;
class AppTest extends \Decouple\Test\TestCase {
  public function execute() : void {
    Console::output('Testing CLI bootstrap (version)');
    $this->testBootstrapA();
    Console::output('Testing CLI bootstrap (FooCommand)');
    $this->testBootstrapB();
    Console::output('Testing CLI bootstrap (BarCommand)');
    $this->testBootstrapC();
  }

  public function testBootstrapA() : void {
    $app = $this->__bootstrap("decouple:version");
    $result = $this->capture($app);
    $this->assertEquals($result, "Decouple v0.1a\n");
    Console::output('Passed');
  }

  public function testBootstrapB() : void {
    $app = $this->__bootstrap("foo:bar");
    $result = $this->capture($app);
    $this->assertEquals($result, "FooBar!\n");
    Console::output('Passed');
  }

  public function testBootstrapC() : void {
    $app = $this->__bootstrap("bar:baz --bar=wtf!");
    $result = $this->capture($app);
    $this->assertEquals($result, "bar:wtf!\n");
    Console::output('Passed');
  }

  public function __bootstrap(string $args) : App {
    $args = new Vector(explode(' ', $args));
    $request = new Request($args);
    $services = Map {"Decouple\\CLI\\Request\Request" => $request};
    $decoupler = new Decoupler($services);
    $app = new App($request, $decoupler, new Paths(Map {

    }), Vector {
      "Test\CLI\Fixture\FooCommand",
      "Test\CLI\Fixture\BarCommand"
    });
    return $app;
  }

  public function capture(App $app) : string {
    ob_start();
    try {
      $app->execute();
    } catch(Exception $e) {
      echo $e->getMessage();
    }
    return ob_get_clean();
  }
}
