<?hh // strict
namespace Test\HTTP\Fixture;
use Decouple\HTTP\Request\Request;
class BarController {
  public function bar(Request $request) : string {
    return $request->routeParams[0];
  }
  public function baz(Request $request) : string {
    return "baz";
  }
}
