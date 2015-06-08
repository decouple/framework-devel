<?hh // decl
function hack_require(string $filename) : mixed {
  if(file_exists($filename)) {
    return require $filename;
  } else {
    throw new Exception(sprintf("Invalid filename: %s", $filename));
  }
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

function rutime(KeyedContainer<string,float> $ru, KeyedContainer<string,float> $rus, string $index) : int {
  return
    ($ru["ru_$index.tv_sec"] * 1000 +
     intval($ru["ru_$index.tv_usec"] / 1000)) -
    ($rus["ru_$index.tv_sec"] * 1000 +
     intval($rus["ru_$index.tv_usec"] / 1000));
}

function assign_object_property(mixed &$object, string $property, mixed $value) : void {
  if(is_object($object)) {
    $object->{$property} = $value;
  }
}
