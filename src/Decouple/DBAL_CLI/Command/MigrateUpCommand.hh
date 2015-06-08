<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\AbstractMigration;
use Decouple\CLI\Console;
use Exception;
class MigrateUpCommand extends AbstractMigrateCommand {
  public static string $name = 'migrate:up';
  public function execute(): void {
    Console::output("Refreshing migrations");
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=0;');
    $migrations = $this->loadMigrations();
    if ($migrations instanceof Vector) {
      foreach ($migrations as $migration) {
        $this->loadMigration($migration);
        $obj = $this->decoupler->injectInstance($migration);
        if ($obj instanceof AbstractMigration) {
          // Check for the most recent stored migration
          $tableName = $obj->getName();
          $storedMigration = $this->selectMigration($migration);
          if (is_null($storedMigration)) {
            Console::output(
              sprintf("Preparing migration %s...", $migration),
            );
            $obj->up();
            $table = $this->schema->table($tableName);
            if ($table->exists()) {
              $o = $table->getAlter();
              $action = 'alter';
            } else {
              $o = $table->getCreate();
              $action = 'create';
            }
            Console::output(
              sprintf("\t-> %s table %s", $action, $tableName),
            );
            $o->fromString($obj->toString());
            $o->execute();
            $this->saveMigration($migration);
          }
        }
      }
    }
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=1;');
    Console::output('Done');
  }
}
