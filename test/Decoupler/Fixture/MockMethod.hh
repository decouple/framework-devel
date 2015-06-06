<?hh // strict
namespace Test\Decoupler\Fixture;

class MockMethod {
  public function getNumber(MethodDependency $dep) : int {
    return $dep->getNumber();
  }
  public function unregistered(UnregisteredDependency $dep) : bool {
    return false;
  }
}
