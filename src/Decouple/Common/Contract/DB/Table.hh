<?hh // strict
namespace Decouple\Common\Contract\DB;
interface Table extends DataStore {
  public function exists() : bool;
  public function create((function(ExecutableTableStructure):void) $callback) : bool;
  public function alter((function(ExecutableTableStructure):void) $callback) : bool;
  public function getCreate() : ExecutableTableStructure;
  public function getAlter() : ExecutableTableStructure;
  public function drop() : bool;
  public function getName() : string;
  public function schema() : Schema;
  public function awaitable() : AwaitableQuery;
}
