<?hh // decl
function hack_require(string $filename) : mixed {
  if(file_exists($filename)) {
    return require $filename;
  } else {
    throw new Exception(sprintf("Invalid filename: %s", $filename));
  }
}

function app_error_handler(int $errno, string $errstr, string $errfile, int $errline) : void {
  echo sprintf("[ERROR#%s] %s on line %s of %s\n", $errno, $errstr, $errline, $errfile);
}

function app_exception_handler(Exception $e) : void {
  $body =
  <div>
    <h1>Exception</h1>
    <p class="ui error message">{$e->getMessage()}</p>
  </div>
  ;
  $errors =
  <table>
    <thead>
      <tr>
        <th>File</th><th>Line</th><th>Function</th><th>Arguments</th>
      </tr>
    </thead>
  </table>
  ;
  $errors->addClass('ui table');
  $tbody = <tbody/>;
  $trace = $e->getTrace();
  foreach($trace as $p) {
    try {
      $file = !is_null($p['file']) ? $p['file'] : 'N/A';
      $args = !is_null($p['args']) ? implode(',', (string)$p['args']) : 'N/A';
      $func = !is_null($p['class']) ? sprintf('%s->%s', $p['class'], $p['function']) : (!is_null($p['function']) ? $p['function'] : 'N/A');
      $line = !is_null($p['line']) ? $p['line'] : 'N/A';
      $error =
      <tr>
        <td>{$file}</td>
        <td>{$line}</td>
        <td>{$func}</td>
        <td>{$args}</td>
      </tr>
      ;
      $tbody->appendChild($error);
    } catch(Exception $e) {}
  }
  $errors->appendChild($tbody);
  $body->appendChild($errors);
  echo $body;
}


function perf_info(DebugRegistry $debug): :xhp {
  $start = $debug->get('start_time');
  $end = getrusage();
  if($start instanceof KeyedContainer) {
    $comptime = rutime($end, $start, "utime")/100;
    $calltime = rutime($end, $start, "stime");
  }
  return
    <div>
      <p class="ui segment">
        Computation time: {$comptime}ms
      </p>
      <p class="ui segment">
        Call time: {$calltime}ms
      </p>
    </div>;
}

function rutime(KeyedContainer<string,float> $ru, KeyedContainer<string,float> $rus, string $index) : float {
  return
    ($ru["ru_$index.tv_sec"] * 1000 +
     intval($ru["ru_$index.tv_usec"] / 1000)) -
    ($rus["ru_$index.tv_sec"] * 1000 +
     intval($rus["ru_$index.tv_usec"] / 1000));
}
