<?hh // strict
namespace Decouple\DBAL_CLI\Command;
use Decouple\DBAL_CLI\Seed;
use Decouple\CLI\Console;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\Registry\Paths;
use Decouple\Decoupler\Decoupler;
use Decouple\Common\Contract\DB\Schema;
use Exception;
class SeedCommand extends AbstractCommand {
  public static string $name = 'seed:run';
  public function __construct(
    protected Paths $paths,
    protected Decoupler $decoupler,
    protected Schema $schema,
  ) { }

  protected function loadSeeds(): mixed {
    return hack_require(
      sprintf("%s/cli/seeds.hh", $this->paths->get('config')),
    );
  }

  protected function loadSeed(string $seed): mixed {
    hack_require(
      sprintf(
        "%s/database/seeds/%s.hh",
        $this->paths->get('app'),
        $seed,
      ),
    );
  }
  public function execute(): void {
    Console::output("Running seeds");
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=0;');
    $seeds = $this->loadSeeds();
    if ($seeds instanceof Vector) {
      foreach ($seeds as $seed) {
        $this->loadSeed($seed);
        $obj = $this->decoupler->injectInstance($seed);
        if ($obj instanceof Seed) {
          Console::output(sprintf("\t->%s", $seed));
          $obj->run();
        }
      }
    }
    $this->schema->execute('SET FOREIGN_KEY_CHECKS=1;');
    Console::output('Done');
  }
}
