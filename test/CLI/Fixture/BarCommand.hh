<?hh // strict
namespace Test\CLI\Fixture;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\CLI\Console;
use Decouple\CLI\Request\Request;
class BarCommand extends AbstractCommand {
  public static string $name = "bar:baz";
  public function __construct(protected Request $request) {
  }
  public function execute() : void {
    $arg = $this->request->getArg('bar')->getValue();
    Console::output('bar:' . (string)$arg);
  }
}
