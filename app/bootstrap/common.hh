<?hh // partial
use Decouple\Log\Log;
use Decouple\Registry\Registry;
use Decouple\Decoupler\Decoupler;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;

require_once "functions.hh";

$base_dir = realpath(dirname(dirname(dirname(__FILE__))));
$paths = hack_require($base_dir.'/app/config/paths.hh');
// autoloader
$include_path = (string) $paths->get('src').PATH_SEPARATOR.get_include_path();
set_include_path($include_path);
spl_autoload_extensions('.hh,.php');
spl_autoload_register(
  function (string $class) use ($paths) {
    $path = str_replace('\\', '/', $class).".hh";
    if (file_exists($paths->get('src').'/'.$path)) {
      include_once $paths->get('src').'/'.$path;
    } elseif (file_exists($paths->get('controllers').'/'.$path)) {
      include_once $paths->get('controllers').'/'.$path;
    }
  },
);
$autoloader = new Decouple\Autoload\Autoload($paths);
$autoloader->register();

// Debug registry
class DebugRegistry extends Registry {}

// Decoupler configuration
$driver = new DPDOMySQLDriver();
$driver->connect(
  Map {'type' => 'mysql', 'host' => 'localhost'},
  'decouple',
  'secret',
);
$driver->connector()->connection()
  ->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
$schema = $driver->schema('decouple');
$decoupler = new Decoupler(
  Map {
    "Decouple\Registry\Paths" => $paths,
    "DebugRegistry" => new DebugRegistry(Map {"start_time" => time()}),
    "Decouple\Common\Contract\DB\Driver" => $driver,
    "Decouple\Common\Contract\DB\Schema" => $schema,
  },
);
