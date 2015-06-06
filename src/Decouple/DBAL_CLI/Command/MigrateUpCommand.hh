<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\MigrationInterface;
class MigrateUpCommand extends AbstractMigrateCommand {
  public static string $name = 'migrate:up';
  public function execute(): void {
    $migrations = $this->getMigrations();
    if ($migrations instanceof Traversable) {
      foreach ($migrations as $migration) {
        $this->getMigration($migration);
        $obj = $this->decoupler->injectInstance($migration);
        if ($migration instanceof MigrationInterface) {
          $migration->up($this->driver->schema('decouple'));
        }
      }
    }
  }
}
