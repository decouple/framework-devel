<?hh // strict
abstract class :decouple:ui:base extends :x:element {

  abstract protected function compose(): :xhp;

  final public function addClass(string $class): :decouple:ui:base {
    $this->setAttribute(
      'class',
      trim((string) $this->getAttribute('class').' '.$class),
    );
    return $this;
  }

  final protected function render(): XHPRoot {
    $root = $this->compose();
    if ($root === null) {
      return <x:frag />;
    }
    if (:base::$ENABLE_VALIDATION) {
      if (!$root instanceof :xhp:html-element &&
          !$root instanceof :decouple:ui:base) {
        throw new XHPClassException(
          $this,
          'compose() must return an xhp:html-element'.
          ' or decouple:ui:base instance.',
        );
      }
    }

    // Get all attributes declared on this instance
    $attributes = $this->getAttributes();
    // Get all allowed attributes on the node returned from compose()
    // $declared = $root->__xhpAttributeDeclaration();
    $declared = $root->getAttributes();

    // Transfer any classes that were added inline over to the root node.
    if ($attributes->contains('class')) {
      $attributes['class'] &&
      $root->setAttribute(
        'class',
        trim(
          (string) $this->getAttribute('class').
          ' '.
          (string) $attributes['class'],
        ),
      );
      $attributes->remove('class');
    }

    // Always forward data and aria attributes
    $html5Attributes =
      Map::fromArray(array('data-' => true, 'aria-' => true));

    // Transfer all valid attributes to $root
    foreach ($attributes as $attribute => $value) {
      if ($declared->contains($attribute) ||
          $html5Attributes->contains(substr($attribute, 0, 5))) {
        try {
          $root->setAttribute($attribute, $value);
        } catch (XHPInvalidAttributeException $e) {
        }
      }
    }

    return $root;
  }

}
