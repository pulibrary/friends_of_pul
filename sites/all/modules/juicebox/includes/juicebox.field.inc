<?php


/**
 * @file
 * Contains all hooks and related methods for the juicebox_formatter field
 * formatter.
 */


/**
 * Implements hook_field_display_alter().
 *
 * Unlike most hook implementations in this file this one is "global" (it's not
 * invoked only for this formatter).
 */
function juicebox_field_display_alter(&$display, $context) {
  // If this display is related to a Juicebox formatter we add some additional
  // metadata that the formatter can use. Most notably we add the actual
  // view mode name that this display relates to. Normally formatters don't need
  // to know this contextual info (and should not change their behavior based
  // on anything other than the raw configured display settings), but the
  // Juicebox case is unique.
  if (isset($display['type']) && $display['type'] == 'juicebox_formatter') {
    $display['juicebox_vm'] = $context['view_mode'];
    // Also, if this is a search-related display we need to flag the fact that
    // it's incompatible with the Juicebox javascript. Adding the Juicebox
    // javascript to a search result output will lead to errors. See issue
    // #2217791. Other incompatible view modes could be added here if needed.
    if ($context['view_mode'] == 'search_result' || $context['view_mode'] == 'search_index') {
      $display['juicebox_vm_incompatible'] = TRUE;
    }
  }
}


/**
 * Implements hook_field_formatter_info().
 *
 * Add juicebox_formatter formatter. Note that this hook is only fired on cache
 * updates to set defaults.
 */
function juicebox_field_formatter_info() {
  // Get the base settings. This function may be called while clearing caches
  // so let's be extra careful about catching any errors gracefully.
  try {
    $juicebox = juicebox();
    $base_settings = $juicebox->confBaseOptions();
    $library = $juicebox->library;
  }
  catch (Exception $e) {
    $message = 'Exception fetching base configuration options for Juicebox field formatter: !message in %function (line %line of %file).';
    watchdog_exception('juicebox', $e, $message);
    return array();
  }
  $formatters = array(
    'juicebox_formatter' => array(
      'label' => t('Juicebox Gallery'),
      'description' => t('Style groups of images or files as a Juicebox gallery.'),
      'field types' => array('image', 'file'),
      'settings' => array_merge($base_settings, array(
        // If the library supports multi-size we can default to that for the
        // main image, otherwise use the "medium" style.
        'image_style' => (!empty($library['version']) && !in_array('juicebox_multisize_image_style', $library['disallowed_conf'])) ? 'juicebox_multisize' : 'juicebox_medium',
        'thumb_style' => 'juicebox_square_thumbnail',
        'caption_source' => '',
        'title_source' => '',
      )),
    ),
  );
  return $formatters;
}


/**
 * Implements hook_field_formatter_settings_form().
 */
function juicebox_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  // We need a Juicbox object to fetch some common configuration details.
  $juicebox = juicebox();
  $form = array();
  // Detect if this is a "pseudo" instance such that the field's context is
  // managed by something other than the core Field API (e.g., a fake ctools
  // instance used for a panel or a view row). This case is supported but we
  // still want to put up a notice about it.
  if (!isset($instance['id'])) {
    $form['instance_warning'] = array(
      '#prefix' => '<div class="messages warning">',
      '#markup' => t('<strong>WARNING:</strong> You appear to be using the Juicebox field formatter with a field instance that is not directly attached to an entity. Support for this configuration is currently experimental. Please test your final gallery output thoroughly.'),
      '#suffix' => '</div>',
    );
  }
  // Get available title and caption sources.
  $text_sources = _juicebox_field_text_sources($instance);
  // Get available image style presets
  $settings = $instance['display'][$view_mode]['settings'];
  // Add the field-formatter-specific elements.
  $form['image_style'] = array(
    '#type' => 'select',
    '#title' => t('Main Image Style'),
    '#default_value' => $settings['image_style'],
    '#description' => t('The style formatter for the main image.'),
    '#options' => $juicebox->confBaseStylePresets(),
    '#empty_option' => t('None (original image)'),
  );
  $form['thumb_style'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail Style'),
    '#default_value' => $settings['thumb_style'],
    '#description' => t('The style formatter for the thumbnail.'),
    '#options' => $juicebox->confBaseStylePresets(FALSE),
    '#empty_option' => t('None (original image)'),
  );
  $form['caption_source'] = array(
    '#type' => 'select',
    '#title' => t('Caption Source'),
    '#default_value' => $settings['caption_source'],
    '#description' => t('The image value that should be used for the caption.'),
    '#options' => $text_sources,
    '#empty_option' => t('No caption'),
  );
  $form['title_source'] = array(
    '#type' => 'select',
    '#title' => t('Title Source'),
    '#default_value' => $settings['title_source'],
    '#description' => t('The image value that should be used for the title.'),
    '#options' => $text_sources,
    '#empty_option' => t('No title'),
  );
  // Add common Juicebox form options.
  $form = $juicebox->confBaseForm($form, $settings);
  return $form;
}


/**
 * Implements hook_field_formatter_settings_summary().
 */
function juicebox_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  // Get available image style presets
  $presets = juicebox()->confBaseStylePresets();
  $settings_display = array();
  // Image style setting.
  if (!empty($settings['image_style']) && isset($presets[$settings['image_style']])) {
    $style = $presets[$settings['image_style']];
  }
  else {
    $style = t('Original Image');
  }
  $settings_display[] = t("Image style: @style", array('@style' => $style));
  // Thumb style setting.
  if (!empty($settings['thumb_style']) && isset($presets[$settings['thumb_style']])) {
    $style = $presets[$settings['thumb_style']];
  }
  else {
    $style = t('Original Image');
  }
  $settings_display[] = t("Thumbnail style: @style", array('@style' => $style));
  // Define display options for caption and title source.
  $text_sources = _juicebox_field_text_sources($instance);
  // Caption source setting.
  if (!empty($text_sources[$settings['caption_source']])) {
    $source = $text_sources[$settings['caption_source']];
  }
  else {
    $source = t('None');
  }
  $settings_display[] = t("Caption source: @source", array('@source' => $source));
  // Title source setting.
  if (!empty($text_sources[$settings['title_source']])) {
    $source = $text_sources[$settings['title_source']];
  }
  else {
    $source = t('None');
  }
  $settings_display[] = t("Title source: @source", array('@source' => $source));
  // Add-in a note about the additional fieldsets.
  $settings_display[] = t("Additional Juicebox library configuration options may also be set.");
  $summary = implode('<br />', $settings_display);
  return $summary;
}


/**
 * Implements hook_field_formatter_view().
 */
function juicebox_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  // If there are no images, don't do anything else.
  if (empty($items)) {
    return $element;
  }
  // The gallery shown in preview view will only display field data from the
  // previously saved version (that is the only version the XML generation
  // methods will have access to). Display a warning because of this.
  if (!empty($entity->in_preview)) {
    drupal_set_message(t('Juicebox galleries may not display correctly in preview mode. Any edits made to gallery data will only be visible after all changes are saved.'), 'warning', FALSE);
  }
  $field_name = $instance['field_name'];
  $entity_type_info = entity_get_info($entity_type);
  $entity_id = $entity->{$entity_type_info['entity keys']['id']};
  // Get display data (such as the view mode) from our custom display variable.
  // This was set for us in juicebox_field_display_alter().
  $psuedo_instance = empty($display['juicebox_vm']) ? TRUE : FALSE;
  $add_js = empty($display['juicebox_vm_incompatible']) ? TRUE : FALSE;
  $display_name = !$psuedo_instance ? $display['juicebox_vm'] : 'unknown';
  // Generate xml path details.
  $xml_id = 'field/' . $entity_type . '/' . $entity_id . '/' . $field_name . '/' . $display_name;
  $xml_args = explode('/', $xml_id);
  $xml_path = 'juicebox/xml/' . $xml_id;
  // If this is a field on a node, we can calculate the path to edit the field
  // (used for admin contextual links).
  $context = array();
  if ($entity_type == 'node' && !$psuedo_instance) {
    $vm_settings = field_view_mode_settings($entity_type, $instance['bundle']);
    $display_name_conf = !empty($vm_settings[$display_name]['custom_settings']) ? $display_name : 'default';
    $context['conf_path'] = 'admin/structure/types/manage/' . $instance['bundle'] . '/display/' . $display_name_conf;
  }
  // Try building the gallery and its XML.
  try {
    // Initialize the gallery.
    $juicebox = juicebox();
    $juicebox->init($xml_args, $display['settings'], $items);
    // Build the gallery.
    juicebox_field_build_gallery($juicebox, $items);
    // Create a render array with the gallery markup. Also include the built
    // gallery for external reference.
    $element[0] = array(
      'gallery' => $juicebox->buildEmbed($xml_path, $add_js, $context, $psuedo_instance),
      '#juicebox' => $juicebox
    );
  }
  catch (Exception $e) {
    $message = 'Exception building Juicebox embed code for field: !message in %function (line %line of %file).';
    watchdog_exception('juicebox', $e, $message);
  }
  return $element;
}


/**
 * Utility to build a Juicebox gallery based on field formatter data.
 *
 * @param JuiceboxGalleryWrapperInterface $juicebox
 *   A juicebox object ready to be manipulated into a gallery.
 * @param array $items
 *   An array for file field items that have been loaded to represent individual
 *   gallery images.
 */
function juicebox_field_build_gallery(JuiceboxGalleryDrupalInterface $juicebox, $items) {
  $settings = $juicebox->getSettings();
  foreach ($items as $id => $item) {
    // Calculate the source data that Juicebox requires.
    $src_data = $juicebox->styleImageSrcData($item, $settings['image_style'], $item, $settings['thumb_style']);
    // Short-circut this iteration if skipping an incompatible file.
    if (!$src_data['juicebox_compatible'] && $settings['incompatible_file_action'] == 'skip') {
      continue;
    }
    // Set the image title. If we have an incompatible file and are configured
    // to show a link, set the title text as the link.
    if (!$src_data['juicebox_compatible'] && $settings['incompatible_file_action'] == 'show_icon_and_link') {
      $anchor = !empty($item['description']) ? $item['description'] : $item['filename'];
      $title = l($anchor, $src_data['link_url']);
    }
    else {
      $title = _juicebox_field_get_text($item, $settings['title_source']);
    }
    // Set the image caption.
    $caption = _juicebox_field_get_text($item, $settings['caption_source']);
    // Add this image to the gallery.
    $juicebox->addImage($src_data, $title, $caption);
  }
  // Run common build tasks.
  $juicebox->runCommonBuild();
}


/**
 * Utility to fetch the title and caption source options for field-based
 * galleries (addresses File Entity and Media module support).
 *
 * @param array $instance
 *   An associative array containing the Drupal field instance information for
 *   a Juicebox field.
 * @return array
 *   An associative array representing the key => label pairs for each title
 *   and caption source option. Each key will match a keyed value on the file
 *   item source array when the gallery is built.
 *
 * @see _juicebox_field_get_text()
 */
function _juicebox_field_text_sources($instance) {
  // Check if this is a "pseudo" instance such that the field is managed by
  // something other than the core Field API (e.g., a fake ctools instance used
  // for a panel or a view row). In this case the instance data is most likely
  // fake, and cannot tell us anything about what field options are available.
  // When this happens we pretend all relevent instance options are active.
  if (!isset($instance['id'])) {
    foreach (array('alt_field', 'title_field', 'image_field_caption', 'description_field') as $value) {
      $instance['settings'][$value] = TRUE;
    }
  }
  // If this is a standard image field we can use the core image "alt" and
  // "title" values.
  if (!empty($instance['settings']['alt_field'])) {
    $text_source_options['alt'] = t('Image - Alt text (processed by fallback text format)');
  }
  if (!empty($instance['settings']['title_field'])) {
    $text_source_options['title'] = t('Image - Title text (processed by fallback text format)');
  }
  // If image field caption is installed on an image field we can also use it.
  if (module_exists('image_field_caption') && !empty($instance['settings']['image_field_caption'])) {
    $text_source_options['image_field_caption'] = t('Image - Image field caption');
  }
  // If this is a standard file field we can use the core file "description"
  // value.
  if (!empty($instance['settings']['description_field'])) {
    $text_source_options['description'] = t('File - Description text (processed by fallback text format)');
  }
  // The filename should always be an available option.
  $text_source_options['filename'] = t('File - Filename (processed by fallback text format)');
  // If file entity is installed we can use fields attached to the "image"
  // file entity.
  if (module_exists('file_entity')) {
    // Get the fields that are available on the image file type.
    $image_fields = field_info_instances('file', 'image');
    foreach ($image_fields as $image_field_name => $image_field) {
      // Only text-based fields should be options.
      if (!empty($image_field['widget']['module']) && $image_field['widget']['module'] == 'text') {
        $text_source_options[$image_field_name] = t('File Entity Image - @label', array('@label' => $image_field['label']));
      }
    }
  }
  return $text_source_options;
}


/**
 * Utility to get sanitized text directly from a file field item.
 *
 * This method will attempt to extract text, in a format safe for display,
 * from the data contained within a file field item.
 *
 * @param array $item
 *   An associative array representing a file field item.
 * @param string $source
 *   The key within the $item array that contains the text that we want to
 *   extract.
 * @return string
 *   Safe text for output or an empty string if no text can be extracted.
 *
 * @see _juicebox_field_text_sources()
 */
function _juicebox_field_get_text($item, $source) {
  $text = '';
  if (!empty($item[$source])) {
    // If a field option is specified we need to try to get the value from a
    // file entity. Note that the entity can be re-created by casting the
    // field item into an object.
    if (strpos($source, 'field_') === 0) {
      $field = field_get_items('file', (object) $item, $source);
      if (!empty($field[0]['safe_value'])) {
        $text = $field[0]['safe_value'];
      }
    }
    // If an image field caption value is specified we need to format the raw
    // caption value.
    elseif ($source == 'image_field_caption' && isset($item['image_field_caption']['value'])) {
      $format = empty($item['image_field_caption']['format']) ? filter_fallback_format() : $item['image_field_caption']['format'];
      $text = check_markup($item['image_field_caption']['value'], $format);
    }
    elseif (is_string($item[$source])) {
      $text = check_markup($item[$source]);
    }
  }
  return $text;
}
