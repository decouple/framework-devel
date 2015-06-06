<?hh // strict
namespace Decouple\Common\Contract;
interface AttributeContainer {
  public function setAttribute(string $name, mixed $value) : void;
  public function getAttribute(string $name) : mixed;
}
