<?php


/**
 * @file
 * Juicebox XML loader that's used to load (and build via loaded methods) the
 * XML associated with a Drupal views style formatter plugin.
 */


/**
 * Class to load and build the XML associated with a Drupal views style
 * formatter plugin.
 */
class JuiceboxXmlViewsStyle implements JuiceboxXmlInterface {

  // Base properties that reference source data.
  protected $viewName;
  protected $viewDisplay;
  protected $viewArgs;
  // Dynamic loaded data storage.
  protected $settings = array();
  protected $view;

  /**
   * Constructor.
   *
   * @param array $id_args
   *   An indexed array of arguments that describe this gallery (and make up its
   *   XML URL). This information uniquely identifies the gallery and contains
   *   all the descriptive data needed to load it.
   */
  public function __construct($id_args) {
    // We need at least 3 data sources to build a view-based gallery (the type
    // along with 2 identifiers for the view display).
    if (empty($id_args) || count($id_args) < 3) {
      throw new Exception(t('Cannot initiate view style Juicebox XML due to insufficient ID args.'));
    }
    // Set data sources as properties.
    $this->viewName = $id_args[1];
    $this->viewDisplay = $id_args[2];
    $this->viewArgs = array_slice($id_args, 3);
    $this->view = views_get_view($this->viewName);
    if (empty($this->view)) {
      throw new Exception(t('Cannot initiate view style Juicebox XML because view @view cannot be found.', array('@view' => $this->viewName)));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function access() {
    // Check access directly through view methods. This should work no matter
    // what state the view is in (executed or not, etc.).
    return $this->view->access($this->viewDisplay);
  }

  /**
   * {@inheritdoc}
   */
  public function getXml() {
    // Execute the view and build the gallery. This is easiest to do by simply
    // calling the preview() method (as it handles all needed sub-processes).
    $this->view->preview($this->viewDisplay, $this->viewArgs);
    // See if if the galley is actually built. The preview() method above
    // typically triggers the Juicebox init and build processes, but under
    // certain caching situations these may be skipped (e.g., if the raw view
    // html is returned from a cache instead of calling the formatter logic).
    $juicebox = $this->getJuiceboxFromData($this->view);
    if (!$juicebox) {
      // Build the gallery manually via the formatter's render method.
      $this->view->style_plugin->render();
      // If we still don't have a built gallery something is wrong.
      $juicebox = $this->getJuiceboxFromData($this->view);
      if (!$juicebox) {
        throw new Exception(t('Could not get gallery XML from view because the gallery could not be built.'));
      }
    }
    // Render the XML.
    return $juicebox->renderXml();
  }

  /**
   * Helper to get a Juicebox gallery from a view.
   *
   * @param array $field
   *   An view object to extract a gallery object from.
   * @return boolean
   *   Returns a Juicebox gallery object if a gallery is both found a built.
   *   Return NULL if no gallery can be extracted.
   */
  protected function getJuiceboxFromData($view) {
    // Within this context if the gallery has been initialized we know it has
    // also been built (as both happen together within the formatter's render()
    // method).
    if (isset($view->style_plugin->juicebox) && $view->style_plugin->juicebox->isInitialized()) {
      return $view->style_plugin->juicebox;
    }
    return NULL;
  }

}