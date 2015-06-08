<?hh // strict
namespace Decouple\Common;
class AbstractAttributeContainer implements \Decouple\Common\Contract\AttributeContainer {
  protected Map<string,mixed> $attributes;
  public function __construct() {
    $this->attributes = Map {};
  }
  public function setAttribute(string $name, mixed $value) : void  {
    $this->attributes->set($name, $value);
  }
  public function getAttribute(string $name) : mixed {
    return $this->attributes->get($name);
  }
  public function getAttributes() : Map<string,mixed> {
    return $this->attributes;
  }
  public function hasAttribute(string $name) : bool {
    return $this->attributes->contains($name);
  }
}
