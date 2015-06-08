<?hh // strict
namespace Decouple\Common\Contract;
interface Runner {
  public function add(string $name, Runnable $item) : void;
  public function remove(string $name) : void;
  public function get(string $name) : Runnable;
  public function run() : void;
}
