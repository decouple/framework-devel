<?hh // strict
namespace Decouple\DBAL_CLI\Contract;
interface Migration {
  public function up() : void;
  public function down() : void;
  public function getName() : string;
  public function toString() : string;
}
