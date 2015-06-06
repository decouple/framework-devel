<?hh // strict
namespace Test\Decoupler\Fixture;
class MockInstance {
  public function __construct(public ConstructorPropertyDependency $param) {}
  public ?PropertyDependency $property = null;
}
