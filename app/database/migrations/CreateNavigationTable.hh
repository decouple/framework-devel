<?hh // strict
use Decouple\DBAL_CLI\Migration;
// Run the create navigation table migration
class CreateNavigationTable extends Migration {
  protected string $name = 'navigation';
  public function up() : void
  {
    $this->table->increments('id');
    $this->table->string('title', 55)->unique();
    $this->table->string('icon', 55)->unique();
    $this->table->string('url', 255)->unique();
    $this->table->timestamps();
    $this->table->softDeletes();
  }
  public function down() : void
  {
    $this->schema->table($this->name)->drop();
  }
}
