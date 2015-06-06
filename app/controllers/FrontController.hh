<?hh // partial
use Decouple\Ui\Ui;
use Decouple\DBAL\Driver\DriverInterface;
use Decouple\DBAL\Query\Raw;
class FrontController {
  public function index(
    DriverInterface $driver,
    DebugRegistry $debug,
  ): string {
    $view =
      <front:index>
      </front:index>;
    $db = $driver->schema('decouple');

    /*
     $users = $db->table('authors');
     $users->insert(Map {
     'name' => 'Author A',
     'email' => 'authora@phenocode.com',
     'created_at' => new Raw('CURRENT_TIMESTAMP')
     })->execute();
     $news->insert(Map {
     'title' => 'Article C',
     'content' => 'Another article content',
     'author_id' => 1,
     'image' => '(empty)',
     'created_at' => new Raw('CURRENT_TIMESTAMP')
     })->execute();
     */
    $news = $db->table('articles');
    $articles = $news->select(
      Vector {'id', 'title', 'content', 'author_id', 'created_at', 'image'},
    )->where('deleted_at', '=', '0000-00-00 00:00:00')->fetchAll();

    $content = <div />;
    if (is_null($articles)) {
      $error =
        <div class="ui error message">
          <h2>
            Oops!
          </h2>
          <p>
            I couldn{"'"}t find any news articles to display... Try again?
          </p>
        </div>;
      $content->appendChild($error);
    } else {
      $container = <news:articles />;
      foreach ($articles as $article) {
        $body =
          <news:article
            title={$article['title']}
            content={$article['content']}
            date={$article['created_at']}
            image={$article['image']}
          />;
        $container->appendChild($body);
      }
      $content->appendChild($container);
    }
    $view->appendChild($content);
    $view->appendChild(<br />);
    $view->appendChild(<hr />);
    $view->appendChild(<br />);
    $view->appendChild(perf_info($debug));

    return (string) $view;
  }

  public function test(): string {
    return "Test";
  }
}
