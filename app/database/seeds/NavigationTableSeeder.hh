<?hh // strict
use Decouple\DBAL_CLI\Seed;
// Run the create articles table migration
class NavigationTableSeeder extends Seed {
  public function run() : void
  {
    $authors = $this->schema->table('navigation');
    $authors->delete()->execute();
    $authors->insert(Map {
      'id' => 1,
      'title' => 'Home',
      'icon' => 'home',
      'url' => '/'
    });
    $authors->insert(Map {
      'id' => 2,
      'title' => 'News',
      'icon' => 'newspaper',
      'url' => '/news'
    });
  }
}
