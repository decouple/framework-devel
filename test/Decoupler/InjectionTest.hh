<?hh // strict
namespace Test\Decoupler;
use Decouple\Test\TestCase;
use Test\Decoupler\Fixture\MockMethod;
use Test\Decoupler\Fixture\MockObject;
use Test\Decoupler\Fixture\MockInstance;
use Test\Decoupler\Fixture\PropertyDependency;
use Test\Decoupler\Fixture\MethodDependency;
use Test\Decoupler\Fixture\ConstructorPropertyDependency;
use Decouple\Decoupler\Decoupler;
use Exception;
use Decouple\CLI\Console;
/**
 * Test the Decouple dependency injector
 */
class InjectionTest extends TestCase {
  public function execute() : void {
    Console::output('... Testing object method injection');
    $this->testObjectMethodInjection();
    Console::output('... Testing object method injection failure');
    $this->testObjectMethodInjectionFailure();
    Console::output('... Testing instance injection');
    $this->testInstanceInjection();
    Console::output('... Testing object injection');
    $this->testObjectInjection();
  }
  /**
   * Test object method injection
   */
  public function testObjectMethodInjection() : void {
    // Create a mock method
    $mock = new MockMethod();
    // Method dependency stores a private int
    $decoupler = new Decoupler(Map::fromArray([
      'Test\Decoupler\Fixture\MethodDependency' => new MethodDependency(42)
    ]));
    // Get the private int 
    $result = $decoupler->injectMethod($mock, 'getNumber');
    // Expect 42
    $this->assertEquals($result, 42);
  }

  /**
   * Test object method injection failure & error messages
   */
  public function testObjectMethodInjectionFailure() : void {
    // Create a mock method
    $mock = new MockMethod();

    // Method dependency stores a private int
    $decoupler = new Decoupler(Map::fromArray([
      'Test\Decoupler\Fixture\MethodDependency' => new MethodDependency(1)
    ]));

    // Force an unregistered dependency error
    $error = '(none)';
    try {
      $decoupler->injectMethod($mock, 'unregistered');
    } catch(Exception $e) {
      $error = $e->getMessage();
    }

    // Make sure the error message checks out
    $this->assertEquals($error, 'Unregistered dependency: Test\Decoupler\Fixture\UnregisteredDependency [Decoupler]');
  }

  /**
   * Test instance creation and property injection
   */
  public function testInstanceInjection() : void {
    // PropertyDependency & ConstructorPropertyDependency have public int $value as constructor args
    $decoupler = new Decoupler(Map::fromArray([
      'Test\Decoupler\Fixture\PropertyDependency' => new PropertyDependency(42),
      'Test\Decoupler\Fixture\ConstructorPropertyDependency' => new ConstructorPropertyDependency(42)
    ]));

    // Create a mock instance
    $mock = $decoupler->injectInstance('Test\Decoupler\Fixture\MockInstance');
    // Default propery & value
    $property = null;
    $value = null;
    // Make sure we're getting the right type of object back
    $this->assertEquals(($mock instanceof MockInstance), true);
    if ($mock instanceof MockInstance) {
      // Make sure our property was injected
      $property = $mock->property;
      $this->assertEquals(($property instanceof PropertyDependency), true);
      if($property instanceof PropertyDependency) {
        // Make sure our property value is accessible
        $value = $property->value;
        $this->assertEquals($value, 42);
        // Make sure our constructor parameter was injected
        $param = $mock->param;
        $this->assertEquals(($param instanceof ConstructorPropertyDependency), true);
        if($param instanceof ConstructorPropertyDependency) {
          // Make sure our constructor parameter value is accessible
          $pvalue = $param->value;
          $this->assertEquals($pvalue, 42);
        }
      }
    }
  }

  /**
   * Test pre-existing object property injection
   */
  public function testObjectInjection() : void {
    // Property dependency has public int $value
    $decoupler = new Decoupler(Map::fromArray([
      'Test\Decoupler\Fixture\PropertyDependency' => new PropertyDependency(21)
    ]));
    // Create a mock object
    $object = new MockObject(21);
    // Inject properties
    $decoupler->injectObject($object);
    // Make sure our properties were injected properly
    $property = $object->property;
    if($property instanceof PropertyDependency) {
      // Make sure our property value is accessible
      $value = $property->value;
      $this->assertEquals($value, 21);
      // Make sure our object methods are functioning and can access property
      $this->assertEquals($object->value(), 42);
    }
  }
}
