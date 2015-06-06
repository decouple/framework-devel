<?hh // strict
namespace Test\Decoupler\Fixture;
class MockObject {
  public ?PropertyDependency $property;
  public function __construct(private int $value) {}
  public function value() : int {
    if($this->property instanceof PropertyDependency) {
      return $this->value + $this->property->value;
    }
    return $this->value;
  }
}
