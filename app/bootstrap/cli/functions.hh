<?hh // partial
function cli_error_handler(int $errno, string $errstr, string $errfile, int $errline) : void {
  echo sprintf("[ERROR#%s] %s on line %s of %s\n", $errno, $errstr, $errline, $errfile);
}

function cli_exception_handler(Exception $e) : void {
  echo sprintf("[Exception] %s on line %s of %s\n", $e->getMessage(), $e->getLine(), $e->getFile());
  $trace = $e->getTrace();
  foreach($trace as $p) {
    $file = isset($p['file']) ? $p['file'] : 'N/A';
    $args = isset($p['args']) ? json_encode($p['args']) : 'N/A';
    $func = isset($p['class']) ? sprintf('%s->%s', $p['class'], $p['function']) : (!is_null($p['function']) ? $p['function'] : 'N/A');
    $line = isset($p['line']) ? $p['line'] : 'N/A';
    echo sprintf("\t->%s\t\t%s\t\t%s\t\t%s\n", $file, $line, $func, $args);
  }
}
