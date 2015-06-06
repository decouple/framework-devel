<?hh // strict
namespace Decouple\DBAL\Table\Alter;
use Decouple\DBAL\Table\Structure\TableColumnInterface;
interface TableAlterInterface {
  public function dropColumn(TableColumnInterface $column) : void;
  public function alterColumn(TableColumnInterface $column) : void;
  public function execute() : bool;
  public function fromString(string $string) : void;
  public function toString() : string;
  public function getName() : string;
}
