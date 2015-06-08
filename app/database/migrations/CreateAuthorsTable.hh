<?hh // strict
use Decouple\DBAL_CLI\Migration;
// Run the create articles table migration
class CreateAuthorsTable extends Migration {
  protected string $name = 'authors';
  public function up() : void
  {
    $this->table->increments('id');
    $this->table->string('name', 55)->unique();
    $this->table->string('email', 255)->unique();
    $this->table->timestamps();
    $this->table->softDeletes();
  }
  public function down() : void
  {
    $this->schema->table($this->name)->drop();
  }
}
