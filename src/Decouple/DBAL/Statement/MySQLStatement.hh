<?hh // strict
use Decouple\DBAL\Statement\StatementInterface;
interface MySQLStatement extends StatementInterface {
  public function fetchColumn(int $column=0) : mixed;
}
