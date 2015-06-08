<?hh // partial
$base_path = realpath(dirname(dirname(dirname(__FILE__))));
return Map {
  "root" => $base_path,
  "src" => $base_path . '/src',
  "app" => $base_path . '/app',
  "controllers" => $base_path . '/app/controllers',
  "bootstrap" => $base_path . '/app/bootstrap',
  "logs" => $base_path . '/app/logs',
  "views" => $base_path . '/app/views',
  "public" => $base_path . '/public',
  "test" => $base_path . '/test',
  "config" => $base_path . '/app/config',
  "migrations" => $base_path . '/app/database/migrations',
  "vendor" => $base_path . '/vendor'
};
