<?hh // strict
namespace Test\HTTP\Fixture;
class RouteDependency {
  public function double(int $number) : int {
    return $number * 2;
  }
}
