<?hh // partial
namespace Test\Http;
use Decouple\HTTP\Request\Request;
use Decouple\HTTP\Request\Uri;
use Decouple\Decoupler\Decoupler;
use Decouple\HTTP\Router\Router;
use Decouple\Test\TestCase;
use Test\HTTP\Fixture\RouteDependency;
use Test\HTTP\Fixture\RoutePropertyDependency;
use Test\HTTP\Fixture\RouteConstructorDependency;
class RouterTest extends TestCase {

  public function execute() : void {
    $this->testRouteFunctionA();
    $this->testRouteFunctionB();
    $this->testRouteMethodA();
    $this->testRouteMethodB();
  }

  public function testRouteFunctionA() : void {
    $uri = new Uri('/foo/bar');
    $result = $this->_testRoute($uri);
    $this->assertEquals($result, 'bar42');
  }

  public function testRouteFunctionB() : void {
    $uri = new Uri('/bar/foo');
    $result = $this->_testRoute($uri);
    $this->assertEquals($result, '42foo');
  }

  public function testRouteMethodA() : void {
    $uri = new Uri('/baz/bar');
    $result = $this->_testRoute($uri);
    $this->assertEquals($result, 'TestController::baz:42');
  }

  public function testRouteMethodB() : void {
    $uri = new Uri('/baz/bang');
    $result = $this->_testRoute($uri);
    $this->assertEquals($result, 'Controller::bang/42');
  }

  private function _testRoute(Uri $uri) : mixed {
    $request = new Request($uri, Map::fromArray(['baz'=>true]), Map {}, Map {});
    $dependencies = Map {
      "Test\HTTP\Fixture\RouteDependency" => new RouteDependency(),
      "Decouple\HTTP\Request\Uri" => $uri,
      "Decouple\HTTP\Request\Request" => $request,
      "Test\HTTP\Fixture\RoutePropertyDependency" => new RoutePropertyDependency(),
      "Test\HTTP\Fixture\RouteConstructorDependency" => new RouteConstructorDependency()
    };
    $decoupler = new Decoupler($dependencies);
    $router = new Router($decoupler);
    $router->serve('/foo/([^/]+)', function(Request $request, RouteDependency $dep) : mixed {
      return $request->routeParams->at(1) . $dep->double(21);
    });
    $router->serve('/bar/([^/]+)', function(Request $request, RouteDependency $dep) : mixed {
      return $dep->double(21) . $request->routeParams->at(1);
    });
    $router->serve('/baz/bar', ['Test\HTTP\Fixture\TestController','baz']);
    $tc = $decoupler->injectInstance('Test\HTTP\Fixture\TestController');
    $router->serve('/baz/([^/]+)', [$tc,'bang']);
    $function = $router->route($request);
    $result = $decoupler->inject($function);
    return $result;
  }
}
