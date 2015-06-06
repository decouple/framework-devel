<?hh // partial
use Decouple\DBAL_CLI\AbstractMigration;
use Decouple\DBAL\Table\Structure\TableStructureInterface;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Schema\SchemaInterface;
// Run the create articles table migration
class CreateArticlesTable extends AbstractMigration {
  protected string $name = 'articles';
  public function up(TableStructureInterface $table) : void
  {
    $table->increments('id');
    $table->string('title', 55)->unique();
    $table->text('content');
    $table->string('image', 255);
    $table->integer('author_id')->unsigned();
    $table->foreign('author_id')->references('id')->on('authors')->onDelete('cascade');
    $table->timestamps();
    $table->softDeletes();
  }
  public function down(TableStructureInterface $table) : void
  {
    $table->drop();
  }
}
