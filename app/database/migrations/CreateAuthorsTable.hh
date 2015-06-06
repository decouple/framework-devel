<?hh // partial
use Decouple\DBAL_CLI\MigrationInterface;
use Decouple\DBAL\Table\TableStructureInterface;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\DBAL\Schema\SchemaInterface;
// Run the create articles table migration
class CreateAuthorsTable implements MigrationInterface {
  public function up(SchemaInterface $schema) : void
  {
    $schema->table('authors')->create(function(TableCreateInterface $table) {
      $table->increments('id');
      $table->string('name', 55)->unique();
      $table->string('email', 255)->unique();
      // $table->integer('author_id')->unsigned();
      // $table->foreign('author_id')->references('id')->on('authors')->onDelete('cascade');
      $table->timestamps();
      $table->softDeletes();
    });
  }
  public function down(SchemaInterface $schema) : void
  {
    $schema->table('authors')->drop();
  }
}
