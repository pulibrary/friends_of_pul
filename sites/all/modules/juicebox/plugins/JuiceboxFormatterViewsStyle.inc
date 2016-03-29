<?php


/**
 * @file
 * Contains the Juicebox views style plugin.
 */


/**
 * Style plugin to render each item in a views list.
 *
 * @ingroup views_style_plugins
 */
class JuiceboxFormatterViewsStyle extends views_plugin_style {

  // Special properties specific to this style formatter.
  public $juicebox;

  /**
   * Constructor.
   */
  function __construct() {
    // Add Juicebox gallery property to the object.
    // @todo: Perhaps some form of dependecy injection should be considered here
    // instead.
    $this->juicebox = juicebox();
  }

  /**
   * Define default plugin options.
   */
  function option_definition() {
    $options = parent::option_definition();
    // Get the base settings.
    $base_settings = $this->juicebox->confBaseOptions();
    $library = $this->juicebox->library;
    // Structure the base settings in the "default" format that views wants.
    foreach ($base_settings as $setting => $value) {
      $base_settings_default[$setting] = array('default' => $value);
    }
    $options = array_merge($base_settings_default, array(
      'image_field' => array('default' => ''),
      // If the library supports multi-size we can default to that for the main
      // image, otherwise use the "medium" style.
      'image_field_style' => array('default' => (!empty($library['version']) && !in_array('juicebox_multisize_image_style', $library['disallowed_conf'])) ? 'juicebox_multisize' : 'juicebox_medium'),
      'thumb_field' => array('default' => ''),
      'thumb_field_style' => array('default' => 'juicebox_square_thumbnail'),
      'title_field' => array('default' => ''),
      'caption_field' => array('default' => ''),
      'show_title' => array('default' => 0),
    ));
    return $options;
  }

  /**
   * Define plugin options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $settings = $this->options;
    // Get the active field options.
    $options = $this->confGetFieldSources();
    $missing_field_warning = '';
    if (empty($options['field_options_images'])) {
      $missing_field_warning = t('<strong>You must add a field of type image, file or file ID to your view display before this value can be set.</strong><br/>');
    }
    // Add the view-specific elements.
    $form['image_field'] = array(
      '#type' => 'select',
      '#title' => t('Image Source'),
      '#default_value' => $settings['image_field'],
      '#description' => t('The field source to use for each image in the gallery. Must be an image field, file field or a file ID.'),
      '#suffix' => $missing_field_warning,
      '#options' => $options['field_options_images'],
      '#empty_option' => t('- Select -'),
    );
    $form['thumb_field'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Source'),
      '#default_value' => $settings['thumb_field'],
      '#description' => t('The field source to use for each thumbnail in the gallery. Must be an image field, file field or a file ID. Typically you will choose the same value that was set in the "Image Source" option above.'),
      '#suffix' => $missing_field_warning,
      '#options' => $options['field_options_images'],
      '#empty_option' => t('- Select -'),
    );
    $form['image_field_style'] = array(
      '#type' => 'select',
      '#title' => t('Image Field Style'),
      '#default_value' => $settings['image_field_style'],
      '#description' => t('The style formatter for the image. Any formatting settings configured on the field itself will be ignored and this style setting will always be used.'),
      '#options' => $this->juicebox->confBaseStylePresets(),
      '#empty_option' => t('None (original image)'),
    );
    $form['thumb_field_style'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Field Style'),
      '#default_value' => $settings['thumb_field_style'],
      '#description' => t('The style formatter for the thumbnail. Any formatting settings configured on the field itself will be ignored and this style setting will always be used.'),
      '#options' => $this->juicebox->confBaseStylePresets(FALSE),
      '#empty_option' => t('None (original image)'),
    );
    $form['title_field'] = array(
      '#type' => 'select',
      '#title' => t('Title Field'),
      '#default_value' => $settings['title_field'],
      '#description' => t('The view\'s field that should be used for the title of each image in the gallery. Any formatting settings configured on the field itself will be respected.'),
      '#options' => $options['field_options'],
      '#empty_option' => t('None'),
    );
    $form['caption_field'] = array(
      '#type' => 'select',
      '#title' => t('Caption Field'),
      '#default_value' => $settings['caption_field'],
      '#description' => t('The view\'s field that should be used for the caption of each image in the gallery. Any formatting settings configured on the field itself will be respected.'),
      '#options' => $options['field_options'],
      '#empty_option' => t('None'),
    );
    $form['show_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Gallery Title'),
      '#default_value' => $settings['show_title'],
      '#description' => t('Show the view display title as the gallery title.'),
    );
    // Add the common form elements.
    $form = $this->juicebox->confBaseForm($form, $settings);
    // Add view-sepcific field options for the linkURL setting.
    $linkurl_field_options = array();
    foreach ($options['field_options'] as $field_key => $field_name) {
      $linkurl_field_options[$field_key] = t('Field') . ' - ' . $field_name;
    }
    $form['linkurl_source']['#description'] = $form['linkurl_source']['#description'] . '</br><strong>' . t('If using a field source it must render a properly formatted URL and nothing else.') . '</strong>';
    $form['linkurl_source']['#options'] = array_merge($form['linkurl_source']['#options'], $linkurl_field_options);
  }

  /**
   * Define validation rules for the plugin display.
   */
  function validate() {
    $errors = parent::validate();
    // Make sure block caching is not enabled. With block caching enabled the
    // Juicebox javascript library may not get included.
    if (isset($this->display->handler->options['block_caching']) && $this->display->handler->options['block_caching'] != DRUPAL_NO_CACHE) {
      $errors[] = t('The Juicebox style cannot be used with block caching. Please disable the "Block caching" option for this display.');
    }
    // Make sure the pager is not enabled.
    if ($this->display->handler->use_pager()) {
      $errors[] = t('The Juicebox style cannot be used with a pager. Please disable the "Use pager" option for this display.');
    }
    // We want to somewhat "nag" the user if they have not yet configured the
    // Juicebox-specific plugin settings (because things won't work until they
    // do). However, we do NOT want to formally set an error. This is because
    // this validate method can run on pages where the user can't actaully touch
    // the Juicebox-specific plugin settings (such as
    // admin/structure/views/add).
    if (empty($this->options['image_field']) || empty($this->options['thumb_field'])) {
      drupal_set_message(t("To ensure a fully functional Juicebox gallery please remember to add at least one field of type Image, File or File ID to your Juicebox view display, and to configure all Juicebox Gallery format settings. Once you have completed these steps, re-save your view to remove this warning."), 'warning', FALSE);
    }
    // Set warning about depreciated "Base file ID" source option if it's used.
    if ($this->options['image_field'] == 'file_base' || $this->options['thumb_field'] == 'file_base') {
      drupal_set_message(t('A Juicebox gallery used in your view is configured with an obsolete source setting of "Base file ID". Please add a File ID field to the related display and choose that instead for your image or thumb source within the Juicebox Gallery format settings. Once you have completed these steps, re-save your view to remove this warning.'), 'warning', FALSE);
    }
    return $errors;
  }

  /**
   * Render the view page display.
   *
   * This is where the Juicebox embed code is built for the view.
   */
  function render() {
    $element = array();
    $view = $this->view;
    // If we are previewing the view in the admin interface all the necessary
    // <script> elements in our embed markup seem to get stripped. Display
    // an admin message instead in this case.
    if (strpos(current_path(), 'admin/structure/views') === 0) {
      drupal_set_message(t("Due to javascript requirements Juicebox galleries cannot be viewed as a live preview. Please save your view and visit the full page URL for this display to preview this gallery."), 'warning');
      return $element;
    }
    // Generate a unique ID that can be used to identify this gallery and view
    // source details.
    $xml_id = 'viewsstyle/' . $view->name . '/' . $view->current_display;
    foreach ($view->args as $arg) {
      $xml_id .= '/' . $arg;
    }
    $xml_args = explode('/', $xml_id);
    $xml_path = 'juicebox/xml/' . $xml_id;
    // Calculate the path to edit the view (used for admin contextual links).
    $context = array();
    $context['conf_path'] = 'admin/structure/views/view/' . $view->name . '/edit/' . $view->current_display;
    // Try to build the Juicebox gallery.
    try {
      // Initialize the gallery.
      $this->juicebox->init($xml_args, $this->options, $view);
      // Build the gallery.
      $this->buildGallery();
      // Render the embed code.
      $element = array('gallery' => $this->juicebox->buildEmbed($xml_path, TRUE, $context));
    }
    catch (Exception $e) {
      $message = 'Exception building Juicebox embed code for view: !message in %function (line %line of %file).';
      watchdog_exception('juicebox', $e, $message);
    }
    return $element;
  }

  /**
   * Build the gallery based on loaded Drupal views data.
   */
  public function buildGallery() {
    $view = $this->view;
    $settings = $this->options;
    $rendered_fields = $this->render_fields($view->result);
    // Get all row image data in the format of Drupal file field items.
    $image_items = $thumb_items = $this->getItems($settings['image_field']);
    if ($settings['image_field'] != $settings['thumb_field']) {
      $thumb_items = $this->getItems($settings['thumb_field']);
    }
    // Iterate through each view row and calculate the gallery-specific details.
    foreach ($image_items as $row_index => $image_item) {
      // Make sure each main image has a thumb item.
      $thumb_item = !empty($thumb_items[$row_index]) ? $thumb_items[$row_index] : $image_item;
      // Calculate the source data that Juicebox requires.
      $src_data = $this->juicebox->styleImageSrcData($image_item, $settings['image_field_style'], $thumb_item, $settings['thumb_field_style']);
      // Short-circut this iteration if skipping an incompatible file.
      if (!$src_data['juicebox_compatible'] && $settings['incompatible_file_action'] == 'skip') {
        continue;
      }
      // Check if the linkURL should be customized based on view settings.
      if (!empty($settings['linkurl_source']) && !empty($rendered_fields[$row_index][$settings['linkurl_source']])) {
        $src_data['link_url'] = $rendered_fields[$row_index][$settings['linkurl_source']];
      }
      // Set the image title.
      $title = '';
      // If we have an incompatible file the title may need special handeling.
      if (!$src_data['juicebox_compatible'] && $settings['incompatible_file_action'] == 'show_icon_and_link') {
        $anchor = !empty($image_item['description']) ? $image_item['description'] : $image_item['filename'];
        $title = l($anchor, $src_data['link_url']);
      }
      elseif (!empty($settings['title_field']) && !empty($rendered_fields[$row_index][$settings['title_field']])) {
        $title = $rendered_fields[$row_index][$settings['title_field']];
      }
      // Set the image caption.
      $caption = '';
      if (!empty($settings['caption_field']) && !empty($rendered_fields[$row_index][$settings['caption_field']])) {
        $caption = $rendered_fields[$row_index][$settings['caption_field']];
      }
      // Add this image to the gallery.
      $this->juicebox->addImage($src_data, $title, $caption);
    }
    if ($settings['show_title']) {
      $this->juicebox->addOption('gallerytitle', check_plain($view->get_title()));
    }
    // Run common build tasks.
    $this->juicebox->runCommonBuild();
  }

  /**
   * Utility to get the item arrays that contain image data from view rows.
   *
   * The items that this method returns are array representations of Drupal file
   * objects. This type of array is often used by Drupal to represent file
   * fields, so this a common format to work with.
   *
   * @param string $source_field
   *   The view field source that will contain a file identifer. The exact part
   *   of the row data to get the file identifer from will depend on the field
   *   type, and this method will resolve that based on the view's field handler
   *   details.
   * @return array
   *   An indexed array, keyed by row id, of file field items that were
   *   extracted based on row data.
   *
   * @see JuiceboxFormatterViewStyle::confGetFieldSources()
   */
  protected function getItems($source_field) {
    $view = $this->view;
    // Get the field source options and make sure the passed-source is valid.
    $source_options = $this->confGetFieldSources();
    if (empty($source_options['field_options_images_type'][$source_field])) {
      throw new Exception(t('Empty or invalid field source @source detected for Juicebox view-based gallery.', array('@source' => $source_field)));
    }
    else {
      $source_type = $source_options['field_options_images_type'][$source_field];
    }
    $fids = array();
    $items = array();
    // Pass 1 - get the fids based on the source type.
    foreach ($view->result as $row_index => $row) {
      switch ($source_type) {
        case 'file_base':
          // This is a file-based view so the fid is already in the row data.
          if (!empty($row->fid)) {
            $fids[$row_index] = $row->fid;
          }
          continue;
        case 'file_id_field':
          // The source is a file ID field so we can fetch the fid from row
          // data.
          if (!empty($row->{$view->field[$source_field]->field_alias})) {
            $fids[$row_index] = $row->{$view->field[$source_field]->field_alias};
          }
          continue;
        case 'file_field':
          // The source is an image or file field so views should have already
          // loaded the related file entities which will include the fid. In
          // this case we also already have our file field item array.
          if (!empty($row->{'field_' . $source_field}[0]['raw'])) {
            $fids[$row_index] = $row->{'field_' . $source_field}[0]['raw']['fid'];
            $items[$row_index] = $row->{'field_' . $source_field}[0]['raw'];
          }
      }
    }
    if (empty($items)) {
      // Bulk load all file entities.
      $file_entities = file_load_multiple($fids);
      // Pass 2 - Get field items from the file entities.
      foreach ($fids as $row_index => $fid) {
        $items[$row_index] = (array) $file_entities[$fid];
      }
    }
    return $items;
  }

  /**
   * Utility to determine which view fields can be used for image data.
   *
   * This method will extract a list of fields that can be used as "sources"
   * for a Juicebox gallery along with other useful field information.
   *
   * @return array
   *   An associative array containing a breakdown of field data that can be
   *   referenced by other build methods, including:
   *   - field_options_image: An associative array, keyed by field id, of fields
   *     that can be used as Juicebox gallery image sources.
   *   - field_options_image_type: An associative array, keyed by field id, of
   *     field "types" for all fields listed in 'field_options_image' above.
   *   - field_options: An associative array, keyed by field id, of fields that
   *     cannot be used as Juicebox gallery image sources, but may be useful
   *     for other purposes (text and caption sorces, etc.)
   *
   * @see JuiceboxFormatterViewStyle::getItems()
   */
  public function confGetFieldSources() {
    $view = $this->view;
    $options = array(
      'field_options_images' => array(),
      'field_options_images_type' => array(),
      'field_options' => array(),
    );
    $field_handlers = $view->display_handler->display->handler->get_handlers('field');
    // If we have a "file" based view we MIGHT be able to use the base row ids
    // from the view as fids. This only appears to work when some modules, like
    // File Entity, are installed which ensure the fid is listed for each row.
    // Because this option cannot be used universally it is OBSOLETE as of
    // 7.x-2.x-beta6. So we list "file_base" in the "field_options_images_type"
    // array, but NOT in the "field_options_images" array. This should ensure we
    // don't break galleries that already use this option, but remove it from
    // the source picklists going forward.
    if (!empty($view->base_table) && $view->base_table == 'file_managed') {
      $options['field_options_images_type']['file_base'] = 'file_base';
    }
    // Get the label for each field.
    foreach ($field_handlers as $field => $handler) {
      $name = $handler->ui_name();
      // Separate image fields from non-image fields. For image fields we can
      // work with fids and fields of type image or file.
      if (isset($handler->field) && $handler->field == 'fid') {
        $options['field_options_images'][$field] = $name;
        $options['field_options_images_type'][$field] = 'file_id_field';
      }
      elseif (isset($handler->field_info['type']) && ($handler->field_info['type'] == 'image' || $handler->field_info['type'] == 'file')) {
        $options['field_options_images'][$field] = $name;
        $options['field_options_images_type'][$field] = 'file_field';
      }
      else {
        $options['field_options'][$field] = $name;
      }
    }
    return $options;
  }

}
