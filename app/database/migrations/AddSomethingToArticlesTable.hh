<?hh // partial
use Decouple\DBAL_CLI\AbstractMigration;
// Run the create articles table migration
class AddSomethingToArticlesTable extends AbstractMigration {
  protected string $name = 'articles';
  public function up() : void
  {
    $this->table->text('something');
  }
  public function down() : void
  {
    $this->table->dropColumn('something');
  }
}
