<?hh // strict
namespace Decouple\Common\Contract\DB;
use Decouple\Common\Contract\Buildable;
interface Queryable {
  public function select(?Vector<string> $fields = null): Queryable;
  public function update(Map<string, mixed> $data): Queryable;
  public function delete(bool $soft = false): Queryable;
  public function where(string $field, string $comp, mixed $value): Queryable;
  public function whereAll(KeyedTraversable<string, string> $array): Queryable;
  public function orderBy(string $field, string $direction): Queryable;
  public function limit(int $min = 0, int $max = 25): Queryable;
  public function insert(Map<string, mixed> $data): mixed;
}
