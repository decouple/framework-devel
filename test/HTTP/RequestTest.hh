<?hh // partial 
namespace Test\Http;
use Decouple\Test\TestCase;
use Decouple\HTTP\Request\Request;
use Decouple\HTTP\Request\Uri;
/**
 * Test the Decouple HTTP Request class
 */
class RequestTest extends TestCase {
  /**
   * Test request
   */
  public function execute() : void {
    $uri = new Uri('/foo/bar');
    $get = [
      'bar' => 'baz'
    ];
    $post = [
      'foo' => 'bar',
    ];
    $files = [];
    $request = new Request($uri, Map::fromArray($get), Map::fromArray($post), Map::fromArray($files));

    $this->assertEquals(serialize($request->uri->parts()), serialize(Vector {'foo','bar'}));
    $this->assertEquals($request->getParam('bar'), 'baz');
    $this->assertEquals($request->postParam('foo'), 'bar');
  }
}
