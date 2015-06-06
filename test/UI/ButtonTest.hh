<?hh // partial 
namespace Test\Ui;
use Decouple\Ui\Ui;
use Decouple\Test\TestCase;
class ButtonTest extends TestCase {
  public function testButton() : void {
    $button = <ui:button></ui:button>;
    $button->setAttribute('size', 'large');
    $button->setAttribute('color', 'green');
    $markdown = $button->__toString();
    $this->assertEquals($markdown, '<button class="large green"></button>');
  }
}
