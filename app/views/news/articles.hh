<?hh // decl
class :news:articles extends :decouple:ui:base {
  public function compose() {
    return
      <div class="ui items">
        {$this->getChildren()}
      </div>
    ;
  }
}
