<?hh // strict
namespace Decouple\Common\Contract\DB;
interface Statement {
    public function errorCode() : int;
    public function errorInfo() : Traversable<mixed>;
    public function rowCount() : int;
    public function fetchColumn(int $id=0) : mixed;
    public function fetchAll() : Vector<Map<string,mixed>>;
    public function execute(mixed $params=null) : mixed;
    public function bindParam(int $paramno, mixed $param, ?string $type = null, int $max_value_len = 0, mixed $driver_params = null) : void;
    public function debugDumpParams() : mixed;
}
