<?php


/**
 * @file
 * Administrative page callbacks for the juicebox module.
 */


/**
 * Menu callback: global configuration options to control Juicebox behaviour.
 *
 * @see juicebox_menu()
 */
function juicebox_admin_settings() {
  $library = juicebox_library_detect(TRUE, TRUE);
  $version = !empty($library['version']) ? $library['version'] : t('Unknown');
  $form['juicebox_admin_intro'] = array(
    '#markup' => t("The options below apply to all Juicebox galleries. Note that most Juicebox configuration options are set within each gallery's unique configuration form and not applied on a global scope like these."),
  );
  $form['juicebox_js_scope'] = array(
    '#type' => 'select',
    '#title' => t('Javscript Scope'),
    '#options' => array('header' => t('Header'), 'footer' => t('Footer')),
    '#default_value' => variable_get('juicebox_js_scope', 'header'),
    '#description' => t('The scope in which to add the Juicebox javascript library. Choosing "footer" may offer a front-end performance advantage in some situations.'),
  );
  $form['juicebox_apply_markup_filter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filter all title and caption output for compatibility with Juicebox javascript (recommended)'),
    '#default_value' => variable_get('juicebox_apply_markup_filter', TRUE),
    '#description' => t('This option helps ensure title/caption output is syntactically compatible with the Juicebox javascript library by removing block-level tags.'),
  );
  $form['juicebox_enable_cors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow galleries to be embedded remotely (CORS support)'),
    '#default_value' => variable_get('juicebox_enable_cors', FALSE),
    '#description' => t('Enable cross-origin resource sharing (CORS) for all generated Juicebox XML. This will allow all origins/domains to use any Juicebox XML requested from this site for embedding purposes (adds a <em>Access-Control-Allow-Origin: *</em> header to all Juicebox XML responses).'),
  );
  $form['juicebox_multilingual'] = array(
    '#type' => 'fieldset',
    '#title' => t('Multilingual options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['juicebox_multilingual']['juicebox_translate_interface'] = array(
    '#type' => 'checkbox',
    '#title' => t('Translate the Juicebox javascript interface'),
    '#default_value' => variable_get('juicebox_translate_interface', FALSE),
    '#description' => t('Send interface strings to the Juicebox javascript after passing them through the Drupal translation system.'),
  );
  $form['juicebox_multilingual']['juicebox_translate_base_languagelist'] = array(
    '#type' => 'textarea',
    '#title' => t('Base string for interface translation'),
    '#default_value' => variable_get('juicebox_translate_base_languagelist', $library['base_languagelist']),
    '#description' => t('The base <strong>English</strong> interface text that Drupal should attempt to translate and pass to the Juicebox javascript for display (using the "languageList" configuration option). This text will be treated as a <strong>single string</strong> by Drupal and must be translated with a tool such as the Locale module. Note that this base string value will rarely change, and any changes made to it will break existing translations.'),
    '#wysiwyg' => FALSE,
    '#states' => array(
      // Hide the settings when the translate option is disabled.
      'invisible' => array(
        ':input[name="juicebox_translate_interface"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['juicebox_multilingual']['juicebox_translate_base_languagelist_suggestion'] = array(
    '#type' => 'item',
    '#title' => t('Suggested base string for currently detected Juicebox version (@version)', array('@version' => $version)),
    '#description' => '<pre>' . $library['base_languagelist'] . '</pre>',
    '#states' => array(
      // Hide the settings when the translate option is disabled.
      'invisible' => array(
        ':input[name="juicebox_translate_interface"]' => array('checked' => FALSE),
      ),
    ),
  );
  $multisize_disallowed = in_array('juicebox_multisize_image_style', $library['disallowed_conf']);
  $multisize_description = '<p>' . t('Some versions of the Juicebox javascript library support "multi-size" (adaptive) image delivery. Individual galleries configured to use the <strong>Juicebox PRO multi-size (adaptive)</strong> image style allow for three different source derivatives to be defined per image, each of which can be configured below. The Juicebox javascript library will then choose between these depending on the active screen mode (i.e. viewport size) of each user. See the Juicebox javascript library documentation for more information.') . '</p>';
  if ($multisize_disallowed) {
    $multisize_description .= '<p><strong>' . t('Your currently detected Juicebox version (@version) is not compatible with multi-size features, so the options below have been disabled.', array('@version' => $version)) . '</strong></p>';
  }
  $form['juicebox_multisize'] = array(
    '#type' => 'fieldset',
    '#title' => t('Juicebox PRO multi-size style configuration'),
    '#description' => $multisize_description,
    '#collapsible' => TRUE,
    '#collapsed' => $multisize_disallowed,
  );
  // Get available image style presets
  $presets = image_style_options(FALSE);
  $form['juicebox_multisize']['juicebox_multisize_small'] = array(
    '#title' => t('Small mode image style'),
    '#default_value' => variable_get('juicebox_multisize_small', 'juicebox_small'),
    '#description' => t('The style formatter to use in small screen mode (e.g., non-retina mobile devices).'),
  );
  $form['juicebox_multisize']['juicebox_multisize_medium'] = array(
    '#title' => t('Medium mode image style'),
    '#default_value' => variable_get('juicebox_multisize_medium', 'juicebox_medium'),
    '#description' => t('The style formatter to use in medium screen mode (e.g., desktops and retina mobile devices).'),
  );
  $form['juicebox_multisize']['juicebox_multisize_large'] = array(
    '#title' => t('Large mode image style'),
    '#default_value' => variable_get('juicebox_multisize_large', 'juicebox_large'),
    '#description' => t('The style formatter to use in large screen mode (e.g., expanded view and retina laptops).'),
  );
  foreach ($form['juicebox_multisize'] as &$options) {
    if (is_array($options)) {
      $options += array(
        '#type' => 'select',
        '#options' => $presets,
        '#empty_option' => t('None (original image)'),
        '#disabled' => $multisize_disallowed,
      );
    }
  }
  // Add some custom submit processing.
  $form['#submit'][] = 'juicebox_admin_settings_submit';
  return system_settings_form($form);
}


/**
 * For submission callback for Juicebox admin settings.
 *
 * @see juicebox_admin_settings()
 */
function juicebox_admin_settings_submit($form, &$form_state) {
  // Clear all cached library data as some of our global settings may impact
  // the library definition itself (e.g., JS scope).
  cache_clear_all('juicebox', 'cache_libraries');
  cache_clear_all('juicebox_local_library', 'cache');
  drupal_set_message(t('The Juicebox library caches have been reset.'));
}
