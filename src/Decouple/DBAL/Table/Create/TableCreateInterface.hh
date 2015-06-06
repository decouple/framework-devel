<?hh // strict
namespace Decouple\DBAL\Table\Create;
use Decouple\DBAL\Table\Structure\TableColumn;
use Decouple\DBAL\Table\Structure\ForeignTableColumn;
use Decouple\DBAL\Table\Structure\TableStructureInterface;
interface TableCreateInterface extends TableStructureInterface {
  public function execute($alter=false) : bool;
}
