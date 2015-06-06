<?hh // strict
namespace Decouple\DBAL\Table\Structure;
interface TableStructureInterface {
  public function increments(string $name, int $length=14) : TableColumnInterface;
  public function integer(string $name, int $length=10) : TableColumnInterface;
  public function string(string $name, int $length=55) : TableColumnInterface;
  public function text(string $name) : TableColumnInterface;
  public function enum(string $name, Traversable<string> $values) : TableColumnInterface;
  public function decimal(string $name, int $numbers=7, int $decimals=2) : TableColumnInterface;
  public function foreign(string $name) : ForeignTableColumn;
  public function softDeletes(bool $value=true) : void;
  public function timestamps(bool $value=true) : void;
  public function timestamp(string $name, bool $value=true) : void;
  public function addColumn(TableColumnInterface $column) : void;
  public function getColumn(string $name) : ?TableColumnInterface;
  public function getColumns() : Map<string,TableColumnInterface>;
  public function fromString(string $string) : void;
  public function toString() : string;
  public function getName() : string;
}
