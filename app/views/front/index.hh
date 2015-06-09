<?hh // decl
class :front:index extends :decouple:ui:base {
  attribute
    Decouple\Common\Contract\DB\Schema schema @required;
  public function compose() : :xhp {
    return
      <layouts:front schema={$this->getAttribute('schema')}>
        <div>
          <h2 class="ui large dividing header">Frontpage</h2>
          {$this->getChildren()}
        </div>
      </layouts:front>
    ;
  }
}
