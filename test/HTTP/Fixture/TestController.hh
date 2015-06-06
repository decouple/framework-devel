<?hh // strict
namespace Test\HTTP\Fixture;
use Decouple\HTTP\Request\Request;
class TestController {
  public function baz(Request $request, RouteDependency $dep) : string {
    return 'TestController::baz:' . $dep->double(21);
  }
  public function bang(Request $request, RouteDependency $dep) : string {
    return "Controller::" . $request->routeParams[1] . "/" . $dep->double(21);
  }
}
