<?hh // strict
use Decouple\DBAL_CLI\Seed;
// Run the create articles table migration
class AuthorsTableSeeder extends Seed {
  public function run() : void
  {
    $authors = $this->schema->table('authors');
    $authors->delete()->execute();
    $authors->insert(Map {
      'id' => 1,
      'name' => 'Administrator',
      'email' => 'drew@phenocode.com'
    });
  }
}
