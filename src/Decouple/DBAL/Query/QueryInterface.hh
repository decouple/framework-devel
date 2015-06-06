<?hh // strict
namespace Decouple\DBAL\Query;
use Decouple\Common\Contract\Buildable;
interface QueryInterface extends Buildable {
  public function select(?Vector<string> $fields=null) : QueryInterface;
  public function update(Map<string,mixed> $data) : QueryInterface;
  public function delete(bool $soft=false) : QueryInterface;
  public function insert(Map<string,mixed> $data, bool $except=false) : int;
  public function where(string $field, string $comp, mixed  $value) : QueryInterface;
  public function whereAll(KeyedTraversable<string,string> $array) : QueryInterface;
  public function fetchAll() : Vector<Map<string,mixed>>;
  public function execute() : mixed;
}
