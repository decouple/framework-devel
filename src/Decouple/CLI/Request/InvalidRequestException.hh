<?hh // strict
namespace Decouple\CLI\Request;
class InvalidRequestException extends \Exception {
  public function __construct(string $message) {
    parent::__construct(sprintf("Invalid request; %s", $message));
  }
}
