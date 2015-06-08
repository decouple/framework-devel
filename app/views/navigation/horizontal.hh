<?hh // strict
use Decouple\Common\Contract\DB\Schema;
class :navigation:horizontal extends :x:element {
  attribute
    Schema schema @required;
  use XHPAsync;
  protected ?Schema $schema = null;
  protected async function asyncRender(): Awaitable<XHPRoot> {
    $out =
      <div class="ui menu">
      </div>
    ;
    $schema = $this->getAttribute('schema');
    if (!is_null($schema)) {
      $items = $schema->table('navigation')->select()->fetchAll();
      foreach ($items as $item) {
        $out->appendChild(
          <a href={$item['url']} class="ui item">
            <i class={(string)$item['icon'] . " icon"}></i>
            {$item['title']}
          </a>
        );
      }
    }
    return $out;
  }
}
