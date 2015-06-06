<?hh // strict
namespace Decouple\Test;
class TestCase {
  private int $assertions = 0;
  public function execute() : mixed {}

  public function assertEquals(mixed $a, mixed $b) : void {
    if($a != $b) {
      throw new TestException(sprintf("Unable to assert that %s == %s", (string)$a, (string)$b));
    }
    $this->assertions++;
  }

  public function assertEqualsExactly(mixed $a, mixed $b) : void {
    if($a !== $b) {
      throw new TestException(sprintf("Unable to assert that %s === %s", (string)$a, (string)$b));
    }
    $this->assertions++;
  }

  public function assertNotEquals(mixed $a, mixed $b) : void {
    if($a == $b) {
      throw new TestException(sprintf("Unable to assert that %s != %s", (string)$a, (string)$b));
    }
    $this->assertions++;
  }

  public function assertions() : int {
    return $this->assertions;
  }
}
