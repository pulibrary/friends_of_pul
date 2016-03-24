<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * friends theme.
 */

function pul_base_page_alter(&$page) {
  if (arg(0) == 'search')
  {
    if (!empty($page['content']['system_main']['search_form']))
    {
      hide($page['content']['system_main']['search_form']);
    }
  }
}
