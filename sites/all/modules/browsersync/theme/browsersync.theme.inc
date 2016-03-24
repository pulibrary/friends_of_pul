<?php

/**
 * @file
 * Code for the Browsersync module theme related functions.
 */

/**
 * Preprocesses variables for browsersync-snippet.tpl.php.
 */
function template_preprocess_browsersync_snippet(&$variables) {
  $variables['host'] = $variables['host'] ? check_plain($variables['host']) : BROWSERSYNC_DEFAULT_HOST;
  $variables['port'] = $variables['port'] ? check_plain($variables['port']) : BROWSERSYNC_DEFAULT_PORT;
}
