<?php


/**
 * @file
 * Juicebox XML loader that's used to load (and build via loaded methods) the
 * XML associated with a Drupal field formatter plugin.
 */


/**
 * Class to load and build the XML associated with a Drupal field formatter
 * plugin.
 */
class JuiceboxXmlField implements JuiceboxXmlInterface {

  // Injected gallery object to build.
  protected $juicebox;
  // Base properties that reference source data.
  protected $idArgs;
  protected $entityType;
  protected $entityId;
  protected $fieldName;
  protected $displayName;
  protected $entity;
  // Helper properties for access checks.
  protected $fieldAccess;
  protected $entityAccess;
  // Dynamic loaded data storage.
  protected $settings = array();
  protected $items = array();

  /**
   * Constructor.
   *
   * @param array $id_args
   *   An indexed array of arguments that describe this gallery (and make up its
   *   XML URL). This information uniquely identifies the gallery and contains
   *   all the descriptive data needed to load it.
   */
  public function __construct($id_args) {
    // We need 5 data sources to build a file-based gallery (the type along
    // with 4 identifiers for the field data).
    if (empty($id_args) || count($id_args) < 5) {
      throw new Exception(t('Cannot initiate field-based Juicebox XML due to insufficient ID args.'));
    }
    // Set data sources as properties.
    $this->idArgs = $id_args;
    $this->entityType = $id_args[1];
    $this->entityId = $id_args[2];
    $this->fieldName = $id_args[3];
    $this->displayName = $id_args[4];
    // Grab the loaded entity as well (typically from static cache).
    $entities = entity_load($this->entityType, array($this->entityId));
    $this->entity = reset($entities);
  }

  /**
   * {@inheritdoc}
   */
  public function access() {
    $access = TRUE;
    // Check field-level access.
    if (!isset($this->fieldAccess)) {
      $field = field_info_field($this->fieldName);
      $this->fieldAccess = field_access('view', $field, $this->entityType, $this->entity);
    }
    $access = ($access && $this->fieldAccess);
    // Check entity-level access.
    if (!isset($this->entityAccess)) {
      // If the Entity API module is installed we can use entity_access() to
      // check access for numerous entity types via their access callbacks.
      // All core entities, and many custom ones, can be handled here.
      if (module_exists('entity')) {
        $this->entityAccess = entity_access('view', $this->entityType, $this->entity);
      }
      // If we can't do a check with entity_access() we only maintain checks
      // for popular core entity types that provide thier own explicit access
      // functions.
      else {
        switch ($this->entityType) {
          case 'node':
            $this->entityAccess = node_access('view', $this->entity);
            break;
          case 'user':
            $this->entityAccess = user_view_access($this->entity);
            break;
          default:
            // Log a warning and return NULL if we can't do a conclusive
            // check.
            watchdog('juicebox', 'Could not verify view access for entity type %type while building Juicebox data. This may have resulted in a broken gallery display. You may be able to remove this error by installing the Entity API module and ensuring that an access callback exists for entities of type %type.', array('%type' => $entity_type), WATCHDOG_ERROR);
            return;
        }
      }
    }
    $access = ($access && $this->entityAccess);
    return $access;
  }

  /**
   * {@inheritdoc}
   */
  public function getXml() {
    // Build the field and gallery. This is easiest to do by simply calling
    // field_view_field (as it handles all needed sub-processes).
    $field = field_view_field($this->entityType, $this->entity, $this->fieldName, $this->displayName);
    // See if if the galley is actually built. field_view_field() typically
    // triggers the Juicebox init and build processes, and passes-back the
    // built gallery, but under certain caching situations these may be skipped
    // (e.g., if the raw field html is returned from a cache instead of calling
    // the formatter logic).
    $juicebox = $this->getJuiceboxFromData($field);
    if (!$juicebox) {
      // Load the data needed to build the gallery manually.
      $this->loadFormatterData();
      // Initalize a new gallery.
      $juicebox = juicebox();
      $juicebox->init($this->idArgs, $this->settings, $field['#items']);
      // Manually build the gallery via the field formatter methods.
      juicebox_field_build_gallery($juicebox, $field['#items']);
    }
    // Render the XML.
    return $juicebox->renderXml();
  }

  /**
   * Helper to get a Juicebox gallery from a field.
   *
   * @param array $field
   *   An associative field array to extract a gallery object from.
   * @return boolean
   *   Returns a Juicebox gallery object if a gallery is both found a built.
   *   Return NULL if no gallery can be extracted.
   */
  protected function getJuiceboxFromData($field) {
    // Within this context if the gallery has been initialized we know it has
    // also been built (as both happen together within
    // juicebox_field_build_gallery()).
    if (isset($field[0]['#juicebox']) && $field[0]['#juicebox']->isInitialized()) {
      return $field[0]['#juicebox'];
    }
    return NULL;
  }

  /**
   * Load the Drupal data that's needed to initialize a field-based Juicebox
   * gallery from scratch.
   */
  protected function loadFormatterData() {
    // Get the bundle details.
    $info = entity_get_info($this->entityType);
    if (empty($info['entity keys']['bundle'])) {
      $bundle = $this->entityType;
    }
    else {
      $bundle = $this->entity->{$info['entity keys']['bundle']};
    }
    // Get the instance and display details.
    $instance = field_info_instance($this->entityType, $this->fieldName, $bundle);
    if ($instance) {
      $display = field_get_display($instance, $this->displayName, $this->entity);
      if (isset($display['type']) && $display['type'] == 'juicebox_formatter') {
        $this->settings = $display['settings'];
        // We now have the same data available that the formatter plugin would
        // have.
        return;
      }
    }
    // If we got here there was a problem loading the data.
    throw new Exception(t('There was problem loading Drupal data for a field-based Juicebox gallery.'));
  }

}
