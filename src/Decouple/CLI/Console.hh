<?hh // strict
namespace Decouple\CLI;
use STDIN;
class Console {
  static function output(string $message) : void {
    echo $message . "\n";
  }
}
