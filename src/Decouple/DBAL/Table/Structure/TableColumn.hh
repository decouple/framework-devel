<?hh // strict
namespace Decouple\DBAL\Table\Structure;
class TableColumn implements TableColumnInterface {
  public function __construct(private string $name, private string $type='string', private Map<string,mixed> $attributes=Map {}) {

  }
  public function setAttribute(string $name, mixed $value) : void {
    $this->attributes->set($name, $value);
  }
  public function getAttribute(string $name, mixed $default=null) : mixed {
    return $this->attributes->get($name);
  }
  public function getAttributes() : Map<string,mixed> {
    return $this->attributes;
  }
  public function hasAttribute(string $name) : bool {
    return $this->attributes->contains($name);
  }
  public function getType() : string {
    return $this->type;
  }
  public function getName() : string {
    return $this->name;
  }
  public function unique(bool $unique=true) : TableColumn {
    $this->attributes->set('unique', $unique);
    return $this;
  }
  public function unsigned(bool $unsigned=true) : TableColumn {
    $this->attributes->set('unsigned', $unsigned);
    return $this;
  }
}
