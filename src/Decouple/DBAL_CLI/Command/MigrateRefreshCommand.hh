<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\MigrationInterface;
use Decouple\CLI\Console;
class MigrateRefreshCommand extends AbstractMigrateCommand {
  public static string $name = 'migrate:refresh';
  public function execute(): void {
    Console::output("Refreshing migrations");
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=0;');
    $migrations = $this->getMigrations();
    if ($migrations instanceof Traversable) {
      foreach ($migrations as $migration) {
        Console::output(sprintf("Migration: %s", $migration));
        $this->getMigration($migration);
        $obj = $this->decoupler->injectInstance($migration);
        if ($obj instanceof MigrationInterface) {
          Console::output("\tDown...");
          $obj->down();
          Console::output("\tUp...");
          $obj->up();
          $this->saveMigration($obj);
        }
      }
    }
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=1;');
  }
}
