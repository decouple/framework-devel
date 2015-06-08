<?hh // strict
namespace Decouple\Common\Contract\DB;
interface TableStructure {
  public function increments(string $name, int $length=14) : TableColumn;
  public function integer(string $name, int $length=10) : TableColumn;
  public function string(string $name, int $length=55) : TableColumn;
  public function text(string $name) : TableColumn;
  public function enum(string $name, Traversable<string> $values) : TableColumn;
  public function decimal(string $name, int $numbers=7, int $decimals=2) : TableColumn;
  public function foreign(string $name) : ForeignTableColumn;
  public function softDeletes(bool $value=true) : void;
  public function timestamps(bool $value=true) : void;
  public function timestamp(string $name, bool $value=true) : void;
  public function addColumn(TableColumn $column) : void;
  public function getColumn(string $name) : ?TableColumn;
  public function getColumns() : Map<string,TableColumn>;
  public function fromString(string $string) : void;
  public function toString() : string;
  public function getName() : string;
}
