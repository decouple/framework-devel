<?hh // strict
namespace Decouple\Decoupler;
use ReflectionObject;
use ReflectionClass;
use ReflectionMethod;
use ReflectionParameter;
use ReflectionFunction;
use Exception;
class Decoupler {
  public function __construct(protected Map<string, mixed> $dependencies) {}
  public function setAll(Map<string, mixed> $dependencies): void {
    foreach ($dependencies as $name => $dependency) {
      $this->set($name, $dependency);
    }
  }
  public function set(string $name, mixed $dependency): void {
    $this->verifyName($name);
    $this->dependencies->set($name, $dependency);
  }
  public function contains(string $name): bool {
    return $this->dependencies->contains($name);
  }
  /**
   * Get a specific dependency
   */
  public function get(string $name): mixed {
    return $this->dependencies->get($name);
  }
  /**
   * Get all of the registered dependencies
   */
  public function getAll(): Map<string, mixed> {
    return $this->dependencies;
  }
  /**
   * Assert that the given class exists
   */
  protected function verifyName(string $name): void {
    if (!class_exists($name)) {
      throw new \Exception(
        sprintf("%s is not a registered class name [Decoupler]", $name),
      );
    }
  }
  /**
   * Inject an object
   */
  public function injectObject(mixed $object): mixed {
    $rfo = new ReflectionObject($object);
    // Reflect on the properties
    $rfp = $rfo->getProperties();
    foreach ($rfp as $property) {
      if (!$property->isPrivate() && !$property->isProtected()) {
        $name = $property->getName();
        $type = $property->getTypeText();
        if (substr($type, 0, 1) == '?') {
          $type = substr($type, 1);
        }
      }
    }
    return $object;
  }
  /**
   * Inject an instance
   */
  public function injectInstance(string $className): mixed {
    if (!class_exists($className)) {
      throw new Exception(
        sprintf("%s is not a valid class name [Decoupler]", $className),
      );
    }
    // Reflect on the object
    $rfo = new ReflectionClass($className);
    // Reflect on the constructor
    $rfm = $rfo->getConstructor();
    if (!is_null($rfm)) {
      $params = $this->methodParams($rfm);
    } else {
      $params = [];
    }
    $obj = $rfo->newInstanceArgs($params);
    return $this->injectObject($obj);
  }
  /**
   * Inject a method
   */
  public function injectMethod(mixed $object, string $method): mixed {
    // Create reflection object method
    $rm = new ReflectionMethod($object, $method);
    $params = $this->methodParams($rm);
    return $rm->invokeArgs($object, $params->toArray());
  }
  /**
   * Inject a function
   */
  public function injectFunction(mixed $function): mixed {
    // Create reflection object method
    $rf = new ReflectionFunction($function);
    $params = $this->functionParams($rf);
    return $rf->invokeArgs($params->toArray());
  }

  protected function functionParams(ReflectionFunction $rf): Vector<mixed> {
    $rp = $rf->getParameters();
    $params = Vector {};
    foreach ($rp as $param) {
      if (is_array($param)) {
        if (!$this->contains($param['info']['type'])) {
          throw new Exception(
            sprintf(
              "Unregistered dependency: %s [Decoupler]",
              $param['info']['type'],
            ),
          );
        } else {
          $params->add($this->get($param['info']['type']));
        }
      }
    }
    return $params;
  }

  /**
   * Reflect on the parameters for the given method
   * @param  ReflectionMethod           $rm           The ReflectionMethod
   * @return Vector<mixed>                            A vector of injected parameters
   */
  protected function methodParams(ReflectionMethod $rm): Vector<mixed> {
    $rp = $rm->getParameters();
    $params = Vector {};
    if ($rp) {
      foreach ($rp as $param) {
        if (is_array($param)) {
          $domains = explode('\\', $param['info']['type']);
          if (!$this->contains($param['info']['type'])) {
            if ($param['info']['type'] == 'Decouple\Decoupler\Decoupler') {
              $params->add($this);
            } else {
              if (!$domains || $domains[0] != 'HH') {
                throw new Exception(
                  sprintf(
                    "Unregistered dependency: %s [Decoupler]",
                    $param['info']['type'],
                  ),
                );
              }
            }
          } else {
            $params->add($this->get($param['info']['type']));
          }
        }
      }
    }
    return $params;
  }

  /**
   * Inect a function, class (instance), or object
   */
  public function inject(mixed $target): mixed {
    if (is_array($target) && count($target) == 2) {
      if (is_string($target[0])) {
        $object = $this->injectInstance($target[0]);
      } else if (is_object($target[0])) {
        $object = $this->injectObject($target[0]);
      } else {
        throw new \Exception(
          sprintf("Invalid class provided: %s", (string) $target[0]),
        );
      }
      if (!method_exists($object, $target[1])) {
        throw new \Exception(
          sprintf(
            "Invalid method requested: %s::%s",
            (string) $object,
            (string) $target[1],
          ),
        );
      }
      return $this->injectMethod($object, $target[1]);
    } else if (is_callable($target)) {
      return $this->injectFunction($target);
    } else if (is_object($target)) {
      return $this->injectObject($target);
    } else if (is_string($target) && class_exists($target)) {
      return $this->injectInstance($target);
    } else {
      throw new \Exception(
        sprintf("Unable to inject target %s", (string) $target),
      );
    }
  }
}
