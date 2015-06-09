<?hh // strict
namespace Decouple\CLI\Command;
interface CommandInterface {
  public static function getName() : string;
  public function execute() : mixed;
}
