<?hh // partial
use Decouple\Log\Log;
use Decouple\Registry\Registry;
use Decouple\Decoupler\Decoupler;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;

// Error handling
set_exception_handler('app_exception_handler');
set_error_handler('app_error_handler', E_ERROR);

$base_dir = realpath(dirname(dirname(dirname(__FILE__))));
$paths = hack_require($base_dir . '/app/config/paths.hh');
// autoloader
$include_path = (string)$paths->get('src') . PATH_SEPARATOR . get_include_path();
set_include_path($include_path);
spl_autoload_extensions('.hh,.php');
spl_autoload_register(function(string $class) use($paths) {
  $path =  str_replace('\\', '/', $class) . ".hh";
  if(file_exists($paths->get('src') . '/' . $path)) {
    include_once $paths->get('src') . '/' . $path;
  } elseif(file_exists($paths->get('controllers') . '/' . $path)) {
    include_once $paths->get('controllers') . '/' . $path;
  }
});
$autoloader = new Decouple\Autoload\Autoload($paths);
$autoloader->register();

// Debug registry
class DebugRegistry extends Registry {}

// Decoupler configuration
$driver = new DPDOMySQLDriver();
$driver->connect(Map {
  'type' => 'mysql',
  'host' => 'localhost',
}, 'decouple', 'secret');
$decoupler = new Decoupler(Map {
  "Decouple\Registry\Paths" => $paths,
  "DebugRegistry" => new DebugRegistry(Map {"start_time" => time()}),
  "Decouple\DBAL\Driver\DriverInterface" => $driver
});

/** Service functions **/
function hack_require(string $filename) : mixed {
  if(file_exists($filename)) {
    return require $filename;
  } else {
    throw new Exception(sprintf("Invalid filename: %s", $filename));
  }
}

function app_error_handler(int $errno, string $errstr, string $errfile, int $errline, KeyedTraversable<mixed,mixed> $errcontext) : void {
  echo sprintf("[ERROR#%s] %s on line %s of %s\n", $errno, $errstr, $errline, $errfile);
}

function app_exception_handler(Exception $e) : void {
  echo sprintf("[EXCEPTION] %s", $e->getMessage());
}
