<?hh // partial
require_once "http/functions.hh";
// Error handling
set_exception_handler('http_exception_handler');
set_error_handler('http_error_handler', E_ERROR);

require "common.hh";
require_once dirname(__FILE__).'/xhp/init.hh';

set_include_path(
  get_include_path().
  PATH_SEPARATOR.
  $paths->get('src').
  PATH_SEPARATOR.
  $paths->get('controllers').
  PATH_SEPARATOR.
  $paths->get('views'),
);

use Decouple\HTTP\Request\Uri;
use Decouple\HTTP\Request\Request;
use Decouple\Registry\Registry;
use Decouple\Registry\Paths;
use Decouple\Ui\Ui;
use Decouple\Log\Log;
use Decouple\Decoupler\Decoupler;
use Decouple\HTTP\Router\Router;
use Decouple\HTTP\App;

// Http request
$uri = new Uri($_SERVER['REQUEST_URI']);
$get = Map::fromArray($_GET);
$post = Map::fromArray($_POST);
$files = Map::fromArray($_FILES);
$request = new Request($uri, $get, $post, $files);

// Register HTTP-specific services
$decoupler->set('Decouple\Http\Request\Request', $request);
$decoupler->set('Decouple\Http\Request\Uri', $uri);

// Router
$router = new Router($decoupler);

// Http application
$app = new App($request, $router, $decoupler);

// Register map of http services
$http_services = Map {
  "Decouple\Log\Log" => new Log((string) $paths->get('logs')."/http.log"),
};
$app->addServices($http_services);

// Load a map of routes
$routes = Map {
  "/" => "FrontController@index",
  "/test" => "FrontController@test",
};
$app->addRoutes($routes);
// Add a single route
$app->addRoute(
  "/version",
  function (Ui $ui, Log $log, DebugRegistry $debug) {
    return
      <layouts:front>
        <h1>
          Version
        </h1>
        <p class="segment">
          Decouple v0.1a
        </p>
        <p class="segment">
          HHVM v{HHVM_VERSION}
        </p>
        {perf_info($debug)}
      </layouts:front>;
  },
);
