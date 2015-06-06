<?hh // strict
namespace Decouple\DBAL\Table\Structure;
use Decouple\Common\AbstractAttributeContainer;
class ForeignTableColumn extends TableColumn {
  private string $references = '';
  private string $on = '';
  private string $onDelete = '';
  private string $type = 'foreign';
  public function __construct(private string $name) {
    parent::__construct($name);
  }
  public function references(string $field) : ForeignTableColumn {
    $this->setAttribute('references', $field);
    return $this;
  }
  public function on(string $table) : ForeignTableColumn {
    $this->setAttribute('on', $table);
    return $this;
  }
  public function getName() : string {
    return $this->name;
  }
  public function getType() : string {
    return $this->type;
  }
  public function onDelete(string $do) : void {
    $this->setAttribute('ondelete', $do);
  }
}
