<?hh // partial
use Decouple\DBAL_CLI\AbstractMigration;
use Decouple\DBAL\Table\TableStructureInterface;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Schema\SchemaInterface;
// Run the create articles table migration
class CreateAuthorsTable extends AbstractMigration {
  protected string $name = 'authors';
  public function up() : void
  {
    $this->table->string('name', 55)->unique();
    $this->table->increments('id');
    $this->table->string('email', 255)->unique();
    // $table->integer('author_id')->unsigned();
    // $table->foreign('author_id')->references('id')->on('authors')->onDelete('cascade');
    $this->table->timestamps();
    $this->table->softDeletes();
  }
  public function down() : void
  {
    $this->schema->table($this->name)->drop();
  }
}
