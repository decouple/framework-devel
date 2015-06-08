<?hh // strict
namespace Decouple\Common\Contract\DB;
interface Schema {
    public function exists() : bool;
    public function create() : bool;
    public function table(string $name) : Table;
    public function driver() : Driver;
    public function execute(string $query) : bool;
}
