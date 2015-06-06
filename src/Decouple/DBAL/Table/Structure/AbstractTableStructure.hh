<?hh // strict
namespace Decouple\DBAL\Table\Structure;
abstract class AbstractTableStructure implements TableStructureInterface {
  protected Map<string,TableColumnInterface> $columns;
  public function __construct(protected string $name) {

  }
  public function getName() : string {
    return $this->name;
  }
  public function integer(string $name, int $length=10) : TableColumn {
    $column = new TableColumn($name, 'integer', Map {'length' => $length});
    $this->columns[$name] = $column;
    return $column;
  }
  public function increments(string $name='id', int $length=14) : TableColumn {
    $column = new TableColumn($name, 'integer', Map {'length' => $length, 'auto_increment' => true});
    $this->columns[$name] = $column;
    return $column;
  }
  public function string(string $name, int $length=55) : TableColumn {
    $column = new TableColumn($name, 'string', Map {'length' => $length});
    $this->columns[$name] = $column;
    return $column;
  }
  public function text(string $name) : TableColumn {
    $column = new TableColumn($name, 'text');
    $this->columns[$name] = $column;
    return $column;
  }
  public function enum(string $name, Traversable<string> $values) : TableColumn {
    $column = new TableColumn($name, 'enum');
    $column->setAttribute('values', $values);
    $this->columns[$name] = $column;
    return $column;
  }
  public function decimal(string $name, int $numbers=7, int $decimals=2) : TableColumn {
    $column = new TableColumn($name, 'decimal');
    $column->setAttribute('numbers', $numbers);
    $column->setAttribute('decimals', $decimals);
    $this->columns[$name] = $column;
    return $column;
  }
  public function foreign(string $name) : ForeignTableColumn {
    $column = new ForeignTableColumn($name);
    $this->columns[$name] = $column;
    return $column;
  }
  public function timestamp(string $name, bool $value=true) : void {
    $created_at = new TableColumn($name, 'timestamp');
    $this->columns[$name] = $created_at;
  }
  public function softDeletes(bool $value=true) : void {
    $deleted_at = new TableColumn('deleted_at', 'timestamp');
    $this->columns['deleted_at'] = $deleted_at;
  }
  public function timestamps(bool $value=true) : void {
    $created_at = new TableColumn('created_at', 'timestamp');
    $this->columns['created_at'] = $created_at;
    $updated_at = new TableColumn('updated_at', 'timestamp');
    $this->columns['updated_at'] = $updated_at;
  }
  public function addColumn(TableColumnInterface $column) : void {
      $this->columns->set($column->getName(), $column);
  }
  public function getColumn(string $name) : ?TableColumnInterface {
    return $this->columns->contains($name) ? $this->columns->at($name) : null;
  }
  public function getColumns() : Map<string,TableColumnInterface> {
    return $this->columns;
  }
  public function toString(): string {
    return serialize($this->columns);
  }
  public function fromString(string $string): void {
    $this->columns = new Map(unserialize($string));
  }
}
