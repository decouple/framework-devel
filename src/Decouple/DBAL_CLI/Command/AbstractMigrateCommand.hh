<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\CLI\Console;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\Registry\Paths;
use Decouple\Decoupler\Decoupler;
use Decouple\DBAL\Schema\SchemaInterface;
use Decouple\DBAL\Table\TableInterface;
use Decouple\DBAL_CLI\MigrationInterface;
abstract class AbstractMigrateCommand extends AbstractCommand {
  protected TableInterface $table;
  public function __construct(
    protected Paths $paths,
    protected Decoupler $decoupler,
    protected SchemaInterface $schema,
  ) {
    $this->table = $schema->table('migrations');
    if(!$this->table->exists()) {
      $this->table->create(function (TableCreateInterface $create) {
        $create->increments('id');
        $create->string('table');
        $create->text('data');
        $create->timestamp('date');
      });
    }
  }

  protected function getMigrations(): mixed {
    return hack_require(
      sprintf("%s/cli/migrations.hh", $this->paths->get('config')),
    );
  }

  protected function getMigration(string $migration): mixed {
    hack_require(
      sprintf(
        "%s/database/migrations/%s.hh",
        $this->paths->get('app'),
        $migration,
      ),
    );
  }

  protected function saveMigration(
    MigrationInterface $migration
  ) {
    $this->schema->table('migration')->insert(Map {
      "table" => $migration->getName(),
      "data" => $migration->toString()
    });
  }
}
