<?hh // strict
namespace Decouple\Common\Contract\DB;
use Decouple\Common\Contract\Buildable;
interface AwaitableQuery extends Queryable {
  public function execute(): Awaitable<Statement>;
  public function insert(Map<string, mixed> $data): Awaitable<int>;
  public function first(): Awaitable<?Map<string, mixed>>;
  public function fetchAll(): Awaitable<Vector<Map<string, mixed>>>;
  public function select(?Vector<string> $fields = null): AwaitableQuery;
  public function update(Map<string, mixed> $data): AwaitableQuery;
  public function delete(bool $soft = false): AwaitableQuery;
  public function where(string $field, string $comp, mixed $value): AwaitableQuery;
  public function whereAll(
    KeyedTraversable<string, string> $array,
  ): Queryable;
  public function orderBy(string $field, string $direction): AwaitableQuery;
  public function limit(int $min = 0, int $max = 25): AwaitableQuery;
}
