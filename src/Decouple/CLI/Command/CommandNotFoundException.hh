<?hh // strict
namespace Decouple\CLI\Command;
use Exception;
class CommandNotFoundException extends Exception {
  public function __construct(string $name) {
    $message = sprintf("Command not found: %s", $name);
    parent::__construct($message);
  }
}
