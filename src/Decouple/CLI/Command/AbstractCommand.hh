<?hh // strict
namespace Decouple\CLI\Command;
abstract class AbstractCommand implements CommandInterface {
  public static string $name = '';
  public static function getName() : string {
    return static::$name;
  }
  abstract public function execute() : mixed;
}
