<?hh // strict
namespace Decouple\Common\Contract\DB;
use Decouple\Common\Contract\Buildable;
interface Query extends Queryable {
  public function execute(): Statement;
  public function insert(Map<string, mixed> $data): int;
  public function first(): ?Map<string, mixed>;
  public function fetchAll(): Vector<Map<string, mixed>>;
  public function select(?Vector<string> $fields = null): Query;
  public function update(Map<string, mixed> $data): Query;
  public function delete(bool $soft = false): Query;
  public function where(string $field, string $comp, mixed $value): Query;
  public function whereAll(
    KeyedTraversable<string, string> $array,
  ): Queryable;
  public function orderBy(string $field, string $direction): Query;
  public function limit(int $min = 0, int $max = 25): Query;
}
