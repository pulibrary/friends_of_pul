<?php

/**
 * @file
 * photo_gallery.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function photo_gallery_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'gallery';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gallery';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Photo Gallery';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'juicebox';
  $handler->display->display_options['style_options']['image_field'] = 'field_photos';
  $handler->display->display_options['style_options']['thumb_field'] = 'field_photos';
  $handler->display->display_options['style_options']['title_field'] = 'nothing';
  $handler->display->display_options['style_options']['caption_field'] = 'nothing_1';
  /* Field: Content: Photos */
  $handler->display->display_options['fields']['field_photos']['id'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['delta_offset'] = '0';
  /* Field: Photos: Title */
  $handler->display->display_options['fields']['field_photos_1']['id'] = 'field_photos_1';
  $handler->display->display_options['fields']['field_photos_1']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos_1']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos_1']['ui_name'] = 'Photos: Title';
  $handler->display->display_options['fields']['field_photos_1']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_photos_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_photos_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_photos_1']['alter']['text'] = '[field_photos_1-title]';
  $handler->display->display_options['fields']['field_photos_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos_1']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos_1']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_photos_1']['delta_offset'] = '0';
  /* Field: Photos: Caption */
  $handler->display->display_options['fields']['field_photos_2']['id'] = 'field_photos_2';
  $handler->display->display_options['fields']['field_photos_2']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos_2']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos_2']['ui_name'] = 'Photos: Caption';
  $handler->display->display_options['fields']['field_photos_2']['label'] = 'hidden';
  $handler->display->display_options['fields']['field_photos_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_photos_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_photos_2']['alter']['text'] = '[field_photos_2-alt]';
  $handler->display->display_options['fields']['field_photos_2']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos_2']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos_2']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_photos_2']['delta_offset'] = '0';
  /* Field: Title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_photos_1]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Caption */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Caption';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[field_photos_2]';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Title */
  $handler->display->display_options['arguments']['title']['id'] = 'title';
  $handler->display->display_options['arguments']['title']['table'] = 'node';
  $handler->display->display_options['arguments']['title']['field'] = 'title';
  $handler->display->display_options['arguments']['title']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['title']['title'] = '%1';
  $handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['title']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['title']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['title']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['title']['limit'] = '0';
  $handler->display->display_options['arguments']['title']['transform_dash'] = TRUE;
  /* Filter criterion: Content: Published status */
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
    'event' => 'event',
  );

  /* Display: Gallery Index */
  $handler = $view->new_display('page', 'Gallery Index', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'gallery-item';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'gallery/[title]';
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '65';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_class'] = 'gallery--title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Photos */
  $handler->display->display_options['fields']['field_photos']['id'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['label'] = '';
  $handler->display->display_options['fields']['field_photos']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_photos']['alter']['path'] = 'gallery/[title]';
  $handler->display->display_options['fields']['field_photos']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['field_photos']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_photos']['element_class'] = 'gallery--image';
  $handler->display->display_options['fields']['field_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_photos']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_photos']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Title */
  $handler->display->display_options['arguments']['title']['id'] = 'title';
  $handler->display->display_options['arguments']['title']['table'] = 'node';
  $handler->display->display_options['arguments']['title']['field'] = 'title';
  $handler->display->display_options['arguments']['title']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['title']['title'] = '%1';
  $handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['title']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['title']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['title']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['title']['limit'] = '0';
  $handler->display->display_options['arguments']['title']['transform_dash'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
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
    'event' => 'event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'events/photos';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Photo Gallery';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Gallery */
  $handler = $view->new_display('page', 'Gallery', 'page_2');
  $handler->display->display_options['path'] = 'gallery';
  $export['gallery'] = $view;

  return $export;
}
