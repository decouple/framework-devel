<?hh // strict
namespace Decouple\Common\Contract\DB;
interface ExecutableTableStructure extends TableStructure {
  public function execute() : bool;
}
