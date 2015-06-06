<?hh // strict
namespace Test\Decoupler\Fixture;

class MethodDependency {
  public function __construct(private int $number){}
    public function getNumber() : int {
      return $this->number;
    }
}
