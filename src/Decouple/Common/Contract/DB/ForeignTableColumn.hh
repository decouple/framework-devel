<?hh // strict
namespace Decouple\Common\Contract\DB;
interface ForeignTableColumn extends TableColumn {
  public function references(string $field) : ForeignTableColumn;
  public function on(string $table) : ForeignTableColumn;
  public function onDelete(string $do) : ForeignTableColumn;
  public function getType() : string;
  public function getName() : string;
}
