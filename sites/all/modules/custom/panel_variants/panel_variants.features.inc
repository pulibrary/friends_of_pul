<?php
/**
 * @file
 * panel_variants.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function panel_variants_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function panel_variants_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function panel_variants_image_default_styles() {
  $styles = array();

  // Exported image style: landing_page_image.
  $styles['landing_page_image'] = array(
    'label' => 'Landing Page Image',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1180,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
