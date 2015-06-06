<?hh // strict
namespace Decouple\CLI\Command;
use Decouple\CLI\Console;
class VersionCommand extends AbstractCommand {
  public static string $name = 'decouple:version';
  public function execute() : void {
    Console::output(sprintf("Decouple v%s", "0.1a"));
  }
}
