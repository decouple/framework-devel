<?hh // strict
namespace Decouple\DBAL;
class Connection {
  final static Map<string,string> $drivers = Map {
    "pdo_mysql" => "Decouple\ORM\DBAL\Driver\PDO\PDOMySQLDriver"
  };
  public function __construct(
    protected string $host, protected string $user, protected string $password, 
    protected string $driver='pdo_mysql', protected string $db_name=''
  ) {

  }
}
