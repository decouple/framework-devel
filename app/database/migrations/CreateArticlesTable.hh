<?hh // partial
use Decouple\DBAL_CLI\AbstractMigration;
use Decouple\DBAL\Table\Structure\TableStructureInterface;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Schema\SchemaInterface;
// Run the create articles table migration
class CreateArticlesTable extends AbstractMigration {
  protected string $name = 'articles';
  public function up() : void
  {
    $this->table->increments('id');
    $this->table->string('title', 55)->unique();
    $this->table->text('content');
    $this->table->string('image', 255);
    $this->table->integer('author_id')->unsigned();
    $this->table->foreign('author_id')->references('id')->on('authors')->onDelete('cascade');
    $this->table->timestamps();
    $this->table->softDeletes();
  }
  public function down() : void
  {
    $this->schema->table($this->name)->drop();
  }
}
