<?hh // partial
namespace Test\HTTP;
use Decouple\Test\TestCase;
use Decouple\HTTP\Request\Request;
use Decouple\HTTP\Request\Uri;
use Decouple\HTTP\Router\Route\FunctionRoute;
use Test\HTTP\Fixture\RouteDependency;
use Decouple\Decoupler\Decoupler;
class RouteTest extends TestCase {
  public function execute() : void {
    $dependencies = Map {
      "Test\HTTP\Fixture\RouteDependency" => new RouteDependency()
    };

    $uri = new Uri('foo/bar');
    $decoupler = new Decoupler($dependencies);
    $request = new Request($uri, Map::fromArray(['baz'=>true]), Map {}, Map {});
    $route = new FunctionRoute('foo/([^/]+)');
    $route->from(function(RouteDependency $dep) : mixed {
      return $dep->double(21);
    });
    $function = $route->execute($request);
    $result = $decoupler->injectFunction($function);
    $this->assertEquals($result, 42);
  }
}
