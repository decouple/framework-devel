<?hh // strict
namespace Decouple\Common\Contract\DB;
interface TableColumn {
  public function setAttribute(string $name, mixed $value) : void;
  public function getAttribute(string $name) : mixed;
  public function getAttributes() : Map<string,mixed>;
  public function hasAttribute(string $name) : bool;
  public function getType() : string;
  public function getName() : string;
  public function unique(bool $unique=true) : TableColumn;
  public function unsigned(bool $unsigned=true) : TableColumn;
}
