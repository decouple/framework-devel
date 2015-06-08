<?hh // strict
namespace Decouple\Common\Contract\ORM;
use Decouple\Common\Contract\DB\Queryable;
interface Model extends Queryable {
  public function belongsTo(string $model, string $key, string $id) : Queryable;
  public function hasMany(string $model, string $key): Queryable;
}
