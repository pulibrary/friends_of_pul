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
  $view->name = 'photo_gallery';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Photo Gallery';
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
  $handler->display->display_options['style_options']['jlib_galleryHeight'] = '60%';
  $handler->display->display_options['style_options']['jlib_showOpenButton'] = 0;
  $handler->display->display_options['style_options']['jlib_useFullscreenExpand'] = 1;
  $handler->display->display_options['style_options']['image_field'] = 'field_gallery_image';
  $handler->display->display_options['style_options']['thumb_field'] = 'field_gallery_image';
  $handler->display->display_options['style_options']['title_field'] = 'title';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_gallery_image']['id'] = 'field_gallery_image';
  $handler->display->display_options['fields']['field_gallery_image']['table'] = 'field_data_field_gallery_image';
  $handler->display->display_options['fields']['field_gallery_image']['field'] = 'field_gallery_image';
  $handler->display->display_options['fields']['field_gallery_image']['label'] = '';
  $handler->display->display_options['fields']['field_gallery_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gallery_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_gallery_image']['type'] = 'juicebox_formatter';
  $handler->display->display_options['fields']['field_gallery_image']['settings'] = array(
    'image_style' => 'juicebox_small',
    'thumb_style' => 'juicebox_square_thumbnail',
    'caption_source' => 'alt',
    'title_source' => 'title',
    'jlib_galleryWidth' => '100%',
    'jlib_galleryHeight' => '60%',
    'jlib_backgroundColor' => '#222222',
    'jlib_textColor' => 'rgba(255,255,255,1)',
    'jlib_thumbFrameColor' => 'rgba(255,255,255,.5)',
    'jlib_showOpenButton' => 0,
    'jlib_showExpandButton' => 1,
    'jlib_useFullscreenExpand' => 1,
    'jlib_showThumbsButton' => 1,
    'jlib_useThumbDots' => 0,
    'manual_config' => '',
    'incompatible_file_action' => 'show_icon_and_link',
    'linkurl_source' => '',
    'linkurl_target' => '_blank',
    'custom_parent_classes' => '',
  );
  $handler->display->display_options['fields']['field_gallery_image']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_gallery_image']['delta_offset'] = '0';
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
    'photo_gallery_image' => 'photo_gallery_image',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'gallery';
  $export['photo_gallery'] = $view;

  return $export;
}
