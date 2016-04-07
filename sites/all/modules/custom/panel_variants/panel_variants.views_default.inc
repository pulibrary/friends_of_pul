<?php
/**
 * @file
 * panel_variants.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function panel_variants_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'landing_page_image';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Landing Page Image';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Landing Page Image';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Landing Page Image */
  $handler->display->display_options['fields']['field_landing_page_image']['id'] = 'field_landing_page_image';
  $handler->display->display_options['fields']['field_landing_page_image']['table'] = 'field_data_field_landing_page_image';
  $handler->display->display_options['fields']['field_landing_page_image']['field'] = 'field_landing_page_image';
  $handler->display->display_options['fields']['field_landing_page_image']['label'] = '';
  $handler->display->display_options['fields']['field_landing_page_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_landing_page_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_landing_page_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_landing_page_image']['settings'] = array(
    'image_style' => 'landing_page_image',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'landing_page' => 'landing_page',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['landing_page_image'] = $view;

  return $export;
}
