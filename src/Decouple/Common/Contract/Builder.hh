<?hh // strict
namespace Decouple\Common\Contract;
interface Builder {
  public function add(string $name, Buildable $item) : void;
  public function remove(string $name) : void;
  public function get(string $name) : Buildable;
  public function build() : void;
}
