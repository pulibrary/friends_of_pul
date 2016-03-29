<?php


/**
 * @file
 * Class to extend a JuiceboxGalleryDecorator object with Drupal-specific logic
 * and structures.
 */


/**
 * Class to extend a JuiceboxGalleryDecorator object with Drupal-specific logic
 * and structures.
 */
class JuiceboxGalleryDrupal extends JuiceboxGalleryDecorator implements JuiceboxGalleryDrupalInterface {

  // Base injected properties.
  public $library = array();
  // Properties set only upon initializing into a specific gallery.
  protected $idArgs = array();
  protected $settings = array();
  protected $initialized = FALSE;
  protected $data;

  /**
   * Constructor.
   *
   * @param JuiceboxGalleryInterface $gallery
   *   A plain-PHP Juicebox gallery object.
   * @param array $library
   *   An associative array of Library data as made available by the Libraries
   *   API.
   */
  public function __construct(JuiceboxGalleryInterface $gallery, $library) {
    $this->gallery = $gallery;
    $this->library = $library;
  }

  /**
   * {@inheritdoc}
   */
  public function init($id_args, $settings = array(), $data = NULL) {
    // Set path for reference.
    $this->idArgs = $id_args;
    $this->settings = $settings;
    $this->data = $data;
    // Calculate and set the gallery ID.
    $id = '';
    foreach ($id_args as $arg) {
      $id .= $arg . '--';
    }
    // Make sure no special characters slipped through inside individual args.
    $id = trim(preg_replace('/[^0-9a-zA-Z-]/', '-', $id), '- ');
    $this->setId($id);
    $this->initialized = TRUE;
  }


  /**
   * {@inheritdoc}
   */
  public function isInitialized() {
    if ($this->initialized) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getIdArgs() {
    return $this->idArgs;
  }

  /**
   * {@inheritdoc}
   */
  public function getSettings() {
    return $this->settings;
  }

  /**
   * {@inheritdoc}
   */
  public function runCommonBuild() {
    // Add all gallery options directly from the settings.
    $this->setGalleryOptions();
    // Also attempt to translate interface strings.
    if (variable_get('juicebox_translate_interface', FALSE)) {
      $base_string = variable_get('juicebox_translate_base_languagelist', '');
      if (!empty($base_string)) {
        $this->addOption('languagelist', check_plain(t($base_string)), FALSE);
      }
    }
    // Allow other modules to alter the built gallery data before it's
    // rendered. After this point the gallery should no longer change.
    drupal_alter('juicebox_gallery', $this, $this->data);
  }

  /**
   * {@inheritdoc}
   */
  public function buildEmbed($xml_path = '', $add_js = TRUE, $context = array(), $add_xml = FALSE) {
    // Prep the ids that may be referenced.
    $embed_id = $this->getId();
    $embed_xml_id = 'xml--' . $embed_id;
    // If we are embedding the XML we also want to set some query string values
    // on the XML URL that will allow the XML build methods to fetch it later.
    $embed_query_additions = array();
    if ($add_xml) {
      $embed_query_additions['xml-source-path'] = current_path();
      $embed_query_additions['xml-source-id'] = $embed_xml_id;
    }
    // Pass-through the current query paramaters and a checksum on the XML URL.
    $current_query = drupal_get_query_parameters();
    $xml_query = array_merge($current_query, array('checksum' => $this->getChecksum()), $embed_query_additions);
    $xml = array(
      'path' => $xml_path,
      'options' => array('query' => $xml_query),
    );
    // The returned render array will contain some common values no matter what
    // output we produce (normal and debug).
    $output = array(
      '#c_links' => $this->buildContextualLinks($xml_path, $context, $add_xml),
      '#gallery_id' => $embed_id,
      '#gallery_images' => $this->getImages(TRUE),
      '#gallery_options' => $this->getOptions(TRUE),
      '#xml' => $xml,
      '#settings' => $this->settings,
      '#suffix' => '',
    );
    // If "jb-debug" is active in the query we display debug info in place of
    // the actual gallery.
    if (array_key_exists('jb-debug', $current_query) && $this->accessDebugDisplay()) {
      $output['#theme'] = 'juicebox_debug_markup';
      $output['#attached']['css'] = array(drupal_get_path('module', 'juicebox') . '/css/admin_styles.css');
    }
    // Otherwise we display the gallery as normal.
    else {
      $output['#theme'] = 'juicebox_embed_markup';
      if ($add_js) {
        // Add the main library via libraries API.
        $output['#attached']['libraries_load'][] = array('juicebox');
        // Add the JS gallery details as Drupal.settings.
        $output['#attached']['js'][] = array(
          'data' => array('juicebox' => array($embed_id => $this->getJavascriptVars(url($xml['path'], $xml['options'])))),
          'type' => 'setting',
        );
        // Add some local JS (implementing Drupal.behaviors) that will process
        // the Drupal.settings above into a new client-side juicebox object.
        $output['#attached']['js'][] = drupal_get_path('module', 'juicebox') . '/js/juicebox_load.js';
      }
      if ($add_xml) {
        $output['#suffix'] .= $this->renderXml($embed_xml_id);
      }
    }
    return $output;
  }

  /**
   * {@inheritdoc}
   */
  public function styleImageSrcData($image_item, $image_style, $thumb_item, $thumb_style) {
    $settings = $this->settings;
    // Make sure that we have proper file field items to work with.
    if (!isset($image_item['fid']) || !isset($thumb_item['fid'])) {
      throw new Exception(t('Invalid image or thumbnail item detected while extracting Juicebox gallery source information.'));
    }
    $check_incompatible = (!empty($settings['incompatible_file_action']));
    $src_data = array();
    // Style the main item.
    $this->styleImage($image_item, $image_style, $check_incompatible);
    $src_data = $image_item['juicebox_src_data'];
    // Style the thumb.
    if (!$image_item['juicebox_compatible'] && $image_item['fid'] == $thumb_item['fid']) {
      $src_data['thumb_url'] = $src_data['image_url'];
    }
    else {
      $this->styleImage($thumb_item, $thumb_style, $check_incompatible);
      $src_data['thumb_url'] = $thumb_item['juicebox_src_data']['image_url'];
    }
    // Check if the linkURL should be customized based on settings.
    $src_data['link_url'] = $image_item['unstyled_src'];
    if ($image_item['juicebox_compatible'] && !empty($settings['linkurl_source']) && $settings['linkurl_source'] == 'image_styled') {
      $src_data['link_url'] = $src_data['image_url'];
    }
    // Set the link target directly from the gallery settings.
    $src_data['link_target'] = !empty($settings['linkurl_target']) ? $settings['linkurl_target'] : '_blank';
    // Also set a flag for incompatible files.
    $src_data['juicebox_compatible'] = $image_item['juicebox_compatible'];
    return $src_data;
  }

  /**
   * Utility to style an individual image/file field item for use in a Juicebox
   * gallery.
   *
   * This method can detect if the passed item is incompatible with Juicebox.
   * If so it styles the output as a mimetype image icon representing the file
   * type. Otherwise the item is styled normally with the passed image style.
   *
   * @param array $item
   *   An associative array of file field item data to append Juicebox styled
   *   image data to.
   * @param string $style
   *   The Drupal image style to apply to the item.
   * @param boolean $check_compatible
   *   Whether-or-not to detect if the item is compatible with Juicebox, and if
   *   so, substitute a mimetype icon for its output.
   */
  protected function styleImage(&$item, $style, $check_compatible = TRUE) {
    $item['juicebox_compatible'] = TRUE;
    // Set the normal, unstyled, url for reference.
    $item['unstyled_src'] = file_create_url($item['uri']);
    // Check compatibility if configured and if the library info contains
    // mimetype compatibitly information.
    if ($check_compatible && !empty($this->library['compatible_mimetypes']) && !in_array($item['filemime'], $this->library['compatible_mimetypes'])) {
      // If the item is not compatible, find the substitute mimetype icon.
      $item['juicebox_compatible'] = FALSE;
      $icon_dir = drupal_get_path('module', 'juicebox') . '/images/mimetypes';
      $icon_path = file_icon_path((object) $item, $icon_dir);
      if ($icon_path) {
        $item['juicebox_src_data']['image_url'] = file_create_url($icon_path);
      }
      else {
        $item['juicebox_src_data']['image_url'] = file_create_url($icon_dir . '/image-x-generic.png');
      }
    }
    // If the item is compatible, style it.
    else {
      $sizes = array('image_url' => $style);
      // The "juicebox_multisize" style is special, and actually consists of 3
      // individual styles configured globally.
      if ($style == 'juicebox_multisize') {
        $sizes = array(
          'image_url_small' => variable_get('juicebox_multisize_small', 'juicebox_small'),
          'image_url' => variable_get('juicebox_multisize_medium', 'juicebox_medium'),
          'image_url_large' => variable_get('juicebox_multisize_large', 'juicebox_large'),
        );
      }
      foreach ($sizes as $size => $style_each) {
        if (!empty($style_each)) {
          $item['juicebox_src_data'][$size] = image_style_url($style_each, $item['uri']);
        }
        else {
          $item['juicebox_src_data'][$size] = $item['unstyled_src'];
        }
      }
    }
  }

  /**
   * Utility to build a render array of contextual links that can be used to
   * administer a gallery.
   *
   * @param string $xml_path
   *   The path to the Juicebox XML for this gallery.
   * @param array $context
   *   Optional contextual information that may be used in the links:
   *   - conf_path: A Drupal path within the admin interface where the gallery
   *     can be configured.
   * @param boolean $omit_xml_link
   *   Whether-or-not to omit a contextul link to the gallery XML.
   * @return array
   *   Drupal render array for the contextual links.
   *
   * @see JuiceboxGalleryDrupalInterface::buildGallery()
   */
  protected function buildContextualLinks($xml_path = '', $context = array(), $omit_xml_link = FALSE) {
    $c_links = array();
    if (module_exists('contextual') && user_access('access contextual links')) {
      $links = array();
      // Add link to the gallery-specific configuration if we have it.
      if (!empty($context['conf_path']) && drupal_valid_path($context['conf_path'])) {
        $links['gallery_config'] = array('title' => t('Configure galleries of this type'), 'href' => $context['conf_path'], 'query' => drupal_get_destination());
      }
      // Add a link to the global Juicebox options.
      if (drupal_valid_path('admin/config/media/juicebox')) {
        $links['global_config'] = array('title' => t('Configure global Juicebox options'), 'href' => 'admin/config/media/juicebox', 'query' => drupal_get_destination());
      }
      if (!$omit_xml_link) {
        $links['xml'] = array('title' => t('View gallery XML'), 'href' => $xml_path);
      }
      // Add link to toggle debug view.
      if ($this->accessDebugDisplay()) {
        $query = drupal_get_query_parameters();
        if (empty($query['jb-debug'])) {
          $query['jb-debug'] = 1;
          $title = t('Toggle debug info on');
        }
        else {
          unset($query['jb-debug']);
          $title = t('Toggle debug info off');
        }
        $links['toggle_debug'] = array('title' => $title, 'href' => current_path(), 'query' => $query, 'fragment' => $this->getId());
      }
      // If we have links, build a render array for the contextual links.
      if ($links) {
        // Add the contextual-links-region wrapper to the Juicebox parent.
        $this->settings['custom_parent_classes'] = trim($this->settings['custom_parent_classes'] . ' contextual-links-region');
        $c_links = array(
          '#prefix' => '<div class="contextual-links-wrapper">',
          '#suffix' => '</div>',
          '#theme' => 'links__contextual',
          '#links' => $links,
          '#attributes' => array('class' => array('contextual-links')),
          '#attached' => array(
            'library' => array(array('contextual', 'contextual-links')),
            'css' => array(drupal_get_path('module', 'juicebox') . '/css/admin_styles.css'),
          ),
        );
      }
    }
    return $c_links;
  }

  /**
   * Check if the current user should have access to the "debug" output for a
   * Juicebox gallery.
   *
   * The debug info does not contain any sensitive information but we still want
   * to provide a reasonable limitation regarding who can trigger it.
   */
  protected function accessDebugDisplay() {
    return user_access('access administration pages');
  }

  /**
   * Utility to extract Juicebox options from the common Drupal display
   * settings, and add them to the gallery.
   *
   * Some common Juicebox configuration options are set via a GUI and others
   * are set as manual strings. This method fetches all of these values from
   * drupal settings data and merges them into the gallery. Note that this only
   * accounts for common settings.
   */
  protected function setGalleryOptions() {
    $settings = $this->settings;
    // Get the string options set via the GUI.
    foreach (array('jlib_galleryWidth', 'jlib_galleryHeight', 'jlib_backgroundColor', 'jlib_textColor', 'jlib_thumbFrameColor') as $name) {
      if (isset($settings[$name])) {
        $name_real = str_replace('jlib_', '', $name);
        $this->addOption(drupal_strtolower($name_real), trim(check_plain($settings[$name])));
      }
    }
    // Get the bool options set via the GUI.
    foreach (array('jlib_showOpenButton', 'jlib_showExpandButton', 'jlib_showThumbsButton', 'jlib_useThumbDots', 'jlib_useFullscreenExpand') as $name) {
      if (isset($settings[$name])) {
        $name_real = str_replace('jlib_', '', $name);
        $this->addOption(drupal_strtolower($name_real), (!empty($settings[$name]) ? 'TRUE' : 'FALSE'));
      }
    }
    // Merge-in the manually assigned options making sure they take priority
    // over any conflicting GUI options.
    if (!empty($settings['manual_config'])) {
      $manual_options = explode("\n", $settings['manual_config']);
      foreach ($manual_options as $option) {
        $option = trim($option);
        if (!empty($option)) {
          // Each manual option has only been validated (on input) to be in the
          // form optionName="optionValue". Now we need split and sanitize the
          // values.
          $matches = array();
          preg_match('/^([A-Za-z0-9]+?)="([^"]+?)"$/u', $option, $matches);
          list($full_match, $name, $value) = $matches;
          $name = drupal_strtolower($name);
          $this->addOption(drupal_strtolower($name), check_plain($value));
        }
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function confBaseOptions() {
    return array(
      'jlib_galleryWidth' => '100%',
      'jlib_galleryHeight' => '100%',
      'jlib_backgroundColor' => '#222222',
      'jlib_textColor' => 'rgba(255,255,255,1)',
      'jlib_thumbFrameColor' => 'rgba(255,255,255,.5)',
      'jlib_showOpenButton' => 1,
      'jlib_showExpandButton' => 1,
      'jlib_showThumbsButton' => 1,
      'jlib_useThumbDots' => 0,
      'jlib_useFullscreenExpand' => 0,
      'manual_config' => '',
      'custom_parent_classes' => '',
      'apply_markup_filter' => 1,
      'linkurl_source' => '',
      'linkurl_target' => '_blank',
      'incompatible_file_action' => 'show_icon_and_link',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function confBaseForm($form, $settings) {
    // Get locally installed library details.
    $library = $this->library;
    $disallowed_conf = array();
    if (!empty($library)) {
      // If we don't have a known version of the Juicebox library, just show a
      // generic warning.
      if (empty($library['version'])) {
        $notification_top = t('<strong>Notice:</strong> Your Juicebox Library version could not be detected. Some options below may not function correctly.');
      }
      // If this version does not support some LITE optins, show a message.
      elseif (!empty($library['disallowed_conf'])) {
        $disallowed_conf = $library['disallowed_conf'];
        $notification_top = t('<strong>Notice:</strong> You are currently using Juicebox library version <strong>@version</strong> which is not compatible with some of the options listed below. These options will appear disabled until you upgrade to the most recent Juicebox library version.', array('@version' => $library['version']));
        $notification_label = t('&nbsp;(not available in @version)', array('@version' => $library['version']));
      }
    }
    // If the library itself is not installed, display formal error message.
    else {
      $notification_top = t('The Juicebox Javascript library does not appear to be installed. Please download and install the most recent version of the Juicebox library.');
      drupal_set_message($notification_top, 'error');
    }
    $form['juicebox_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Juicebox Library - Lite Config'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => !empty($notification_top) ? '<p>' . $notification_top . '</p>' : '',
      '#weight' => 10,
    );
    $form['jlib_galleryWidth'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'textfield',
      '#title' => t('Gallery Width'),
      '#description' => t('Set the gallery width in a standard numeric format (such as 100% or 300px).'),
      '#element_validate' => array('juicebox_element_validate_dimension'),
    );
    $form['jlib_galleryHeight'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'textfield',
      '#title' => t('Gallery Height'),
      '#description' => t('Set the gallery height in a standard numeric format (such as 100% or 300px).'),
      '#element_validate' => array('juicebox_element_validate_dimension'),
    );
    $form['jlib_backgroundColor'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'textfield',
      '#title' => t('Background Color'),
      '#description' => t('Set the gallery background color as a CSS3 color value (such as rgba(10,50,100,0.7) or #FF00FF).'),
    );
    $form['jlib_textColor'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'textfield',
      '#title' => t('Text Color'),
      '#description' => t('Set the color of all gallery text as a CSS3 color value (such as rgba(255,255,255,1) or #FF00FF).'),
    );
    $form['jlib_thumbFrameColor'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'textfield',
      '#title' => t('Thumbnail Frame Color'),
      '#description' => t('Set the color of the thumbnail frame as a CSS3 color value (such as rgba(255,255,255,.5) or #FF00FF).'),
    );
    $form['jlib_showOpenButton'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'checkbox',
      '#title' => t('Show Open Image Button'),
      '#description' => t('Whether to show the "Open Image" button. This will link to the full size version of the image within a new tab to facilitate downloading.'),
    );
    $form['jlib_showExpandButton'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'checkbox',
      '#title' => t('Show Expand Button'),
      '#description' => t('Whether to show the "Expand" button. Clicking this button expands the gallery to fill the browser window.'),
    );
    $form['jlib_useFullscreenExpand'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'checkbox',
      '#title' => t('Use Fullscreen Expand'),
      '#description' => t('Whether to trigger fullscreen mode when clicking the expand button (for supported browsers).'),
    );
    $form['jlib_showThumbsButton'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'checkbox',
      '#title' => t('Show Thumbs Button'),
      '#description' => t('Whether to show the "Toggle Thumbnails" button.'),
    );
    $form['jlib_useThumbDots'] = array(
      '#jb_fieldset' => 'juicebox_config',
      '#type' => 'checkbox',
      '#title' => t('Show Thumbs Dots'),
      '#description' => t('Whether to replace the thumbnail images with small dots.'),
    );
    $form['juicebox_manual_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Juicebox Library - Pro / Manual Config'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => '<p>' . t('Specify any additional Juicebox library configuration options (such as "Pro" options) here.<br/>Options set here always take precedence over those set in the "Lite" options above if there is a conflict.') . '</p>',
      '#weight' => 20,
    );
    $form['manual_config'] = array(
      '#jb_fieldset' => 'juicebox_manual_config',
      '#type' => 'textarea',
      '#title' => t('Pro / Manual Configuraton Options'),
      '#description' => t('Add one option per line in the format <strong>optionName="optionValue"</strong><br/>See also: http://www.juicebox.net/support/config_options'),
      '#element_validate' => array('juicebox_element_validate_config'),
    );
    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Juicebox - Advanced Options'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 30,
    );
    $form['incompatible_file_action'] = array(
      '#jb_fieldset' => 'advanced',
      '#type' => 'select',
      '#title' => t('Incompatible File Type Handling'),
      '#options' => array('skip' => 'Bypass incompatible files', 'show_icon' => 'Show mimetype icon placehoder', 'show_icon_and_link' => 'Show mimetype icon placholder and link to file'),
      '#empty_option' => t('Do nothing'),
      '#description' => t('Specify any special handling that should be applied to files that Juicebox cannot display (non-images).'),
    );
    $form['linkurl_source'] = array(
      '#jb_fieldset' => 'advanced',
      '#type' => 'select',
      '#title' => t("LinkURL Source"),
      '#description' => t('The linkURL is an image-specific path for accessing each image outside the gallery. This is used by features such as the "Open Image Button".'),
      '#options' => array('image_styled' => 'Main Image - Styled (use this gallery\'s main image style setting)'),
      '#empty_option' => t('Main Image - Unstyled (original image)'),
    );
    $form['linkurl_target'] = array(
      '#jb_fieldset' => 'advanced',
      '#type' => 'select',
      '#title' => t('LinkURL Target'),
      '#options' => array('_blank' => '_blank', '_self' => '_self', '_parent' => '_parent', '_top' => '_top'),
      '#description' => t('Specify a target for any links that make user of the image linkURL.'),
    );
    $form['custom_parent_classes'] = array(
      '#jb_fieldset' => 'advanced',
      '#type' => 'textfield',
      '#title' => t('Custom Classes for Parent Container'),
      '#description' => t('Define any custom classes that should be added to the parent container within the Juicebox embed markup.<br/>This can be handy if you want to apply more advanced styling or dimensioning rules to this gallery via CSS. Enter as space-separated values.'),
    );
    // Set values that are directly related to each key.
    foreach ($form as $conf_key => &$conf_value) {
      if (!empty($conf_value['#type']) && $conf_value['#type'] != 'fieldset') {
        $conf_value['#default_value'] = $settings[$conf_key];
        if (in_array($conf_key, $disallowed_conf)) {
          $conf_value['#title'] .= $notification_label;
          $conf_value['#disabled'] = TRUE;
        }
      }
    }
    // Add a pre render callback that will ensure that the items are nested
    // correctly into fieldsets just before display.
    $form['#pre_render'] = array('juicebox_form_pre_render_fieldsets');
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function confBaseStylePresets($allow_multisize = TRUE) {
    // Get available image style presets.
    $presets = image_style_options(FALSE);
    // If multisize is allowed, include it with the normal styles.
    if ($allow_multisize && !in_array('juicebox_multisize_image_style', $this->library['disallowed_conf'])) {
      $presets = array('juicebox_multisize' => t('Juicebox PRO multi-size (adaptive)')) + $presets;
    }
    return $presets;
  }

}
