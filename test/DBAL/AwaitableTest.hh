<?hh // strict
namespace Test\DBAL;
use Decouple\Test\TestCase;
use Decouple\DBAL\DPDO\DPDOMySQLDriver;
use Decouple\Common\Contract\DB\Table;
use Decouple\DBAL\Table\Create\TableCreateInterface;
use Decouple\Common\Contract\DB\ExecutableTableStructure;
use Decouple\CLI\Console;
class AwaitableTest extends TestCase {
  public async function execute(): Awaitable<void> {
    $driver = new DPDOMySQLDriver();
    $connected = $driver->connect(
      Map {
        "dbname" => "decouple_test",
        "type" => "mysql",
        "host" => "localhost",
      },
      "decouple",
      "secret",
    );
    $schema = $driver->schema('decouple');
    $articles = $schema->table('articles');
    $authors = $schema->table('authors');

    if (!$articles->exists()) {
      Console::output('Attempting to create articles table');
      $res = $articles->create(
        function (ExecutableTableStructure $table) {
          $table->increments('id');
          $table->string('title', 55)->unique();
          $table->text('content');
          $table->string('image', 255);
          $table->integer('author_id')->unsigned();
          $table->foreign('author_id')
            ->references('id')
            ->on('authors')
            ->onDelete('cascade');
          $table->timestamps();
          $table->softDeletes();
        },
      );
      $this->assertEquals($res, true);
    }

    if (!$authors->exists()) {
      Console::output('Attempting to create authors table');
      $res = $authors->create(
        function (ExecutableTableStructure $table) {
          $table->increments('id');
          $table->string('name', 55)->unique();
          $table->string('email', 255)->unique();
          $table->timestamps();
          $table->softDeletes();
        },
      );
    }

    // Clear tables
    $authors->delete()->execute();
    $articles->delete()->execute();

    $author_ids = [];
    $article_ids = [];

    // Seed tables
    Console::output('Inserting author');
    $author_id = $authors->insert(
      Map {
        'id' => 1,
        'name' => 'Administrator',
        'email' => 'drew@phenocode.com',
      },
    );
    Console::output('Inserting awaitable 1');
    await $article_ids[] = $articles->awaitable()->insert(
      Map {
        'author_id' => 1,
        'title' => 'Title',
        'content' => 'Content',
        'image' => 'http://lorempixel.com/400/200',
      },
    );
    Console::output('Inserting awaitable 2');
    await $article_ids[] = $articles->awaitable()->insert(
      Map {
        'author_id' => 1,
        'title' => 'Title 2',
        'content' => 'Content 2',
        'image' => 'http://lorempixel.com/400/200',
      },
    );
    Console::output('Inserting awaitable 3');
    await $article_ids[] = $articles->awaitable()->insert(
      Map {
        'author_id' => 1,
        'title' => 'Title 3',
        'content' => 'Content 3',
        'image' => 'http://lorempixel.com/400/200',
      },
    );

    Console::output('Asserting count(articles) == 3');
    $this->assertEquals(count($article_ids), 3);

    Console::output('Cleaning up');
    $articles->drop();
    $authors->drop();
  }
}
