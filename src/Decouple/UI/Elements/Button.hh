<?hh // strict
final class :decouple:ui:button extends :decouple:ui:base {
  attribute
    :button,
    enum {'small', 'large'} size = 'small',
    enum {'red', 'blue', 'green'} color = 'red';

  protected function compose() : XHPRoot {
    $this->addClass($this->getAttribute('size'));
    $this->addClass($this->getAttribute('color'));
    return <button>{$this->getChildren()}</button>;
  }
}
