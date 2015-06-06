<?hh // strict
namespace Test\Cli\Fixture;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\CLI\Console;
class FooCommand extends AbstractCommand {
  public static string $name = "foo:bar";
  public function execute() : void {
    Console::output("FooBar!");
  }
}
