<?hh // strict
namespace Test\Http;
use Decouple\Decoupler\Decoupler;
use Decouple\HTTP\Request\Request;
use Decouple\HTTP\Request\Uri;
use Decouple\HTTP\Router\Router;
use Decouple\HTTP\App;
use Decouple\Registry\Paths;
use Decouple\Log\Log;
use Decouple\Test\TestCase;
use Decouple\CLI\Console;
class AppTest extends TestCase {
  public function __construct(private Paths $paths) {
    // Placeholder for injection
  }
  public function execute() : void {
    $path = (string)$this->paths->get('vendor') . '/facebook/xhp-lib/init.php';
    // Require XHP init
    hack_require($path);
    $this->testAppBootstrapA();
    $this->testAppBootstrapB();
    $this->testAppBootstrapC();
  }
  public function testAppBootstrapA() : void {
    $tmp_app = $this->__bootstrap("/foo/bar");
    $result = $tmp_app->execute();
    $this->assertEquals($result, 'FooBar!');
  }
  public function testAppBootstrapB() : void {
    $tmp_app = $this->__bootstrap("/bar/baz");
    $result = $tmp_app->execute();
    $this->assertEquals($result, 'baz');
  }
  public function testAppBootstrapC() : void {
    $tmp_app = $this->__bootstrap("/bang/bam");
    $result = $tmp_app->execute();
    $this->assertEquals($result, 'Bang!');
  }
  public function __bootstrap(string $uri) : App {
    // HTTP request
    $uri = new Uri($uri);
    $request = new Request($uri, Map {}, Map {}, Map {});

    // Paths configuration
    $root = (string)realpath((string)dirname(__FILE__) . '/../../');
    $paths = new Paths(Map {
      "root" => $root,
      "app" => $root . '/app',
      "app.logs" => $root . '/app/logs',
      "ui" => $root . '/ui'
    });

    // Decoupler configuration
    $decoupler = new Decoupler(Map {
      "Decouple\\HTTP\\Request\\Request" => $request,
      "Decouple\\HTTP\\Request\\Uri" => $uri,
      "Decouple\\Registry\\Paths" => $paths
    });

    // Router
    $router = new Router($decoupler);

    // HTTP application
    $tmp_app = new App($request, $router, $decoupler);

    // Load application services from a map
    $services = Map {
      "Decouple\\Log\\Log" => new Log((string)$paths->get('app.logs') . "/http.log"),
      "Test\\HTTP\\Fixture\\TestHTTPService" => true
    };
    $tmp_app->addServices($services);

    // Load a map of routes
    $routes = Map {
        "/foo/([^/]+)" => "Test\\HTTP\\Fixture\\FooController",
        "/bar/([^/]+)" => "Test\\HTTP\\Fixture\\BarController@baz",
    };
    $tmp_app->addRoutes($routes);
    // Add a single route
    $tmp_app->addRoute("/bang/([^/]+)", function(Log $log) {
      $log->write("Bang!");
      return "Bang!";
    });

    return $tmp_app;
  }
}
