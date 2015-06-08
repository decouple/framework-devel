<?hh // decl
class :layouts:header extends :decouple:ui:base {
  public string $title = '';

  public function compose() {
    $header =
    <header>
      <h1>{$this->getTitle()}</h1>
      <layouts:navigation/>
    </header>;
  }

  public function getTitle() : string {
    return $this->title;
  }

  public function setTitle(string $title) : void {
    $this->title = $title;
  }
}
