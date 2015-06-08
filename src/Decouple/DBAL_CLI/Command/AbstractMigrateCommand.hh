<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\CLI\Console;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\Registry\Paths;
use Decouple\Decoupler\Decoupler;
use Decouple\Common\Contract\DB\Table;
use Decouple\Common\Contract\DB\Schema;
use Decouple\Common\Contract\DB\TableStructure;
abstract class AbstractMigrateCommand extends AbstractCommand {
  protected Table $table;
  public function __construct(
    protected Paths $paths,
    protected Decoupler $decoupler,
    protected Schema $schema,
  ) {
    $this->table = $schema->table('migrations');
    if (!$this->table->exists()) {
      $this->table->create(
        function (TableStructure $create) {
          $create->increments('id');
          $create->string('migration');
          $create->timestamp('date');
        },
      );
    }
  }

  protected function loadMigrations(): mixed {
    return hack_require(
      sprintf("%s/cli/migrations.hh", $this->paths->get('config')),
    );
  }

  protected function loadMigration(string $migration): mixed {
    hack_require(
      sprintf(
        "%s/database/migrations/%s.hh",
        $this->paths->get('app'),
        $migration,
      ),
    );
  }

  protected function selectMigration(string $migration): ?Map<string,mixed> {
    return $this->schema
      ->table('migrations')
      ->select()
      ->where('migration', '=', $migration)
      ->first();
  }

  protected function resetMigration(string $migration) : void {
    $this->schema
      ->table('migrations')
      ->delete()
      ->where('migration', '=', $migration)
      ->execute();
  }

  protected function saveMigration(string $migration): void {
    $this->schema
      ->table('migrations')
      ->insert(Map {"migration" => $migration});
  }
}
