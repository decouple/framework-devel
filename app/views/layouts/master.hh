<?hh // strict
use Decouple\Common\Contract\DB\Schema;
class :layouts:master extends :decouple:ui:base {
  attribute
    Schema schema @required;

  protected string $title = '';
  protected Map<string,(string,string,bool)> $scripts = Map {};
  protected Map<string,(string,string,bool)> $styles = Map {};

  public function compose() : XHPRoot {
    $head =
      <head>
          <title>{$this->getTitle()}</title>
      </head>
      ;
    $this->loadScripts($head);
    $this->loadStyles($head);
    return
      <html>
        {$head}
        <body>
          <navigation:horizontal schema={$this->getAttribute('schema')}/>
          {$this->getChildren()}
        </body>
      </html>
    ;
  }

  public function getTitle() : string {
    return $this->title;
  }

  public function setTitle(string $title) : void {
    $this->title = $title;
  }

  public function addScript(string $name, string $src, string $type='text/javascript', bool $raw=false) : void {
    $this->scripts->set($name, tuple($src, $type, $raw));
  }

  public function removeScript(string $name) : void {
    $this->scripts->remove($name);
  }

  public function loadScripts(:xhp $head) : void {
    foreach($this->scripts as $name => $script) {
      if($script[2]) {
        $tag = $script[0];
      } else {
        $tag = <script></script>;
        $tag->setAttribute('src', $script[0]);
        $tag->setAttribute('type', $script[1]);
      }
      $head->appendChild($tag);
    }
  }

  public function addStyle(string $name, string $src, string $media='screen', bool $raw=false) : void {
    $this->styles->set($name, tuple($src, $media, $raw));
  }

  public function removeStyle(string $name) : void {
    $this->styles->remove($name);
  }

  public function loadStyles(:xhp $head) : void {
    foreach($this->styles as $name => $style) {
      if($style[2]) {
        $tag = $style[1];
      } else {
        $tag = <link rel="stylesheet"/>;
        $tag->setAttribute('href', $style[0]);
        $tag->setAttribute('media', $style[1]);
      }
      $head->appendChild($tag);
    }
  }
}
