<?hh // strict
namespace Decouple\CLI;
use Decouple\CLI\Request\Request;
use Decouple\Decoupler\Decoupler;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\CLI\Command\AwaitableCommand;
use Decouple\CLI\Command\CommandInterface;
use Decouple\Registry\Registry;
use Decouple\Registry\Paths;
class App {
  protected Map<string,mixed> $commands;
  protected Map<string,Registry> $config;
  public function __construct(protected Request $request, protected Decoupler $decoupler, public Paths $paths, ?Vector<string> $commands=null) {
    $this->commands = Map {'decouple:version'=>'Decouple\CLI\Command\VersionCommand'};
    $this->config = Map {};
    if(!is_null($commands)) {
      $this->registerCommands($commands);
    }
  }
  public function execute() : mixed {
    $command = $this->request->getArg(0)->getVariable();
    $command = $this->getCommand($command);
    if($command instanceof AwaitableCommand) {
      return $command->execute()->getWaitHandle()->join();
    } else if($command instanceof CommandInterface) {
      return $command->execute();
    }
    throw new \Exception(sprintf("Unable to inject command instance: %s", (string)$command));
  }
  public function addServices(KeyedTraversable<string,mixed> $services) : void {
    foreach($services as $name => $service) {
      $this->addService($name, $service);
    }
  }
  public function addService(string $name, mixed $service=true) : void {
    if($service === true) {
      if(class_exists($name)) {
        $service = $this->decoupler->injectInstance($name);
      } else {
        throw new \Exception(sprintf("Unable to automagically create service.\n Class %s is undefined.", $name));
      }
    }
    if(!is_object($service)) {
      throw new \Exception(sprintf("Services registered with HTTP must be objects! [%s is set to %s]", $name, (string)$service));
    }
    $this->decoupler->set($name, $service);
  }
  public function registerCommands(Vector<string> $commands) : void {
    foreach($commands as $command) {
      $this->registerCommand($command);
    }
  }
  public function registerCommand(mixed $command) : void {
    if(!$command instanceof CommandInterface && !class_exists($command)) {
      throw new Command\CommandNotFoundException((string)$command);
    }
    if(!is_subclass_of($command, 'Decouple\CLI\Command\CommandInterface')) {
      throw new Command\CommandNotFoundException((string)$command);
    }
    $this->commands->set(call_user_func_array([$command,'getName'], []), $command);
  }
  public function getCommand(string $name) : mixed {
    if($this->commands->contains($name)) {
      $command = $this->commands->at($name);
      return $this->decoupler->inject($command);
    }
    throw new Command\CommandNotFoundException($name);
  }
  public function getConfig(string $key) : Registry {
    if($this->config->contains($key)) {
      $reg = $this->config->get($key);
      if($reg instanceof Registry) {
        return $reg;
      }
    } else {
      $config = hack_require((string)$this->paths->get('config') . '/' . str_replace('.', '/', $key) . '.hh');
      if($config instanceof KeyedTraversable) {
        $reg = new Registry($config);
        $this->config->set($key, $reg);
        return $reg;
      }
    }
    return new Registry(Map {});
  }
  public function decoupler() : Decoupler { return $this->decoupler; }
}
