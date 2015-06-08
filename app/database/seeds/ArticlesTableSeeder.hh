<?hh // strict
use Decouple\DBAL_CLI\Seed;
// Run the create articles table migration
class ArticlesTableSeeder extends Seed {
  public function run() : void
  {
    $articles = $this->schema->table('articles');
    $articles->delete()->execute();
    $articles->insert(Map {
      'author_id' => 1,
      'title' => 'Title',
      'content' => 'Content',
      'image' => 'http://lorempixel.com/400/200'
    });
    $articles->insert(Map {
      'author_id' => 1,
      'title' => 'Title 2',
      'content' => 'Content 2',
      'image' => 'http://lorempixel.com/400/200'
    });
    $articles->insert(Map {
      'author_id' => 1,
      'title' => 'Title 3',
      'content' => 'Content 3',
      'image' => 'http://lorempixel.com/400/200'
    });
    $articles->insert(Map {
      'author_id' => 1,
      'title' => 'Title 4',
      'content' => 'Content 4',
      'image' => 'http://lorempixel.com/400/200'
    });
  }
}
