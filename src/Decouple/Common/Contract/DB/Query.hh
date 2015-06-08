<?hh // strict
namespace Decouple\Common\Contract\DB;
use Decouple\Common\Contract\Buildable;
interface Query extends Queryable {
  public function execute(): Statement;
}
