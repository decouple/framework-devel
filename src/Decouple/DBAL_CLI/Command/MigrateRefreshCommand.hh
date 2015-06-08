<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\Migration;
use Decouple\CLI\Console;
class MigrateRefreshCommand extends AbstractMigrateCommand {
  public static string $name = 'migrate:refresh';
  public function execute(): void {
    Console::output("Refreshing migrations");
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=0;');
    $migrations = $this->loadMigrations();
    $created = Map {};
    if ($migrations instanceof Traversable) {
      foreach ($migrations as $migration) {
        Console::output(sprintf("Migration: %s", $migration));
        $this->loadMigration($migration);
        $obj = $this->decoupler->injectInstance($migration);
        if ($obj instanceof Migration) {
          // Check for the most recent stored migration
          $tableName = $obj->getName();
          $storedMigration = $this->selectMigration($migration);
          if(!is_null($storedMigration)) {
            Console::output(
              sprintf("\t-> Reverse migration %s...", $migration),
            );
            $obj->down();
            $this->resetMigration($migration);
          }
          Console::output(
            sprintf("\t-> Run migration %s...", $migration),
          );
          $obj->up();
          $table = $this->schema->table($tableName);
          if ($created->containsKey($migration) || $table->exists()) {
            $o = $table->getAlter();
            $action = 'Altering';
          } else {
            $created->set($migration, true);
            $o = $table->getCreate();
            $action = 'Creating';
          }
          Console::output(
            sprintf("\t-> %s table %s", $action, $obj->getName()),
          );
          $o->fromString($obj->toString());
          $o->execute();
          $this->saveMigration($migration);
        }
      }
    }
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=1;');
  }
}
