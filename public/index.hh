<?hh // partial
$start = getrusage();
session_name('decouple');
session_start();
require_once dirname(__FILE__) . '/../app/bootstrap/http.hh';
echo $app->execute();
