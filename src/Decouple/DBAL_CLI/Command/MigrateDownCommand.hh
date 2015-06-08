<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\Migration;
use Decouple\CLI\Console;
class MigrateDownCommand extends AbstractMigrateCommand {
  public static string $name = 'migrate:down';
  public function execute(): void {
    Console::output("Refreshing migrations");
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=0;');
    $migrations = $this->loadMigrations();
    if ($migrations instanceof Traversable) {
      foreach ($migrations as $migration) {
        $this->loadMigration($migration);
        $obj = $this->decoupler->injectInstance($migration);
        if ($obj instanceof Migration) {
          Console::output(
            sprintf("Reverse migration %s...", $migration),
          );
          $obj->down();
          $this->resetMigration($migration);
        }
      }
    }
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=1;');
  }
}
