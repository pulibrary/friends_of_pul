<?php

/**
 * @file
 * events.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function events_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_bfe5b71e-99aa-442e-bd55-629b5f6e08aa';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -25;
  $handler->conf = array(
    'title' => 'Events',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'events',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'single';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '04e5a150-b87b-4bf2-b58d-3e0ec544ed0e';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'node_view__panel_context_bfe5b71e-99aa-442e-bd55-629b5f6e08aa';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-afa59d2e-89c0-4741-b811-47e32bee9b9e';
  $pane->panel = 'middle';
  $pane->type = 'views_panes';
  $pane->subtype = 'calendar-panel_pane_1';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'path' => 'events-calendar',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'afa59d2e-89c0-4741-b811-47e32bee9b9e';
  $display->content['new-afa59d2e-89c0-4741-b811-47e32bee9b9e'] = $pane;
  $display->panels['middle'][0] = 'new-afa59d2e-89c0-4741-b811-47e32bee9b9e';
  $pane = new stdClass();
  $pane->pid = 'new-75c21320-6d29-4dad-b2a0-8f9612e36c0e';
  $pane->panel = 'middle';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'title_heading' => 'h2',
    'body' => '<iframe src="https://api3.libcal.com/embed_calendar.php?iid=771&cal_id=12260&w=800&h=600&dv=month&st=0&we=1&hl=prev%2Cnext%20today&hc=title&hr=basicWeek%20agendaDay%2CagendaWeek%2Cmonth&hd=dddd%2C%20MMM%20D%2C%20YYYY&hw=MMMM%20D&hm=MMMM%20YYYY&cd=dddd%20M%2FD&cw=ddd%20M%2FD&cm=ddd&ta=h(%3Amm)a&td=h(%3Amm)a&tm=h(%3Amm)a&fh=08%3A00%3A00&mi=00%3A00%3A00&ma=24%3A00%3A00&ts=00%3A30%3A00&eo=1&el=0&hf=1&sp=0&c1=%23000000&c2=%23000000&c3=%23F3F3F3&c4=%23D0D0D0&c5=%23000000&audience=&cam=&cat=50867&tar=0&set=0" style="border: 0" width="800" height="600" frameborder="0" scrolling="auto"></iframe>

<p><a href="https://mediacentral.princeton.edu/channel/Friends%2Bof%2Bthe%2BPrinceton%2BUniversity%2BLibrary/170320411">View recordings of previous events</a>.</p>',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'libcal-upcoming-events-calendar',
  );
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '75c21320-6d29-4dad-b2a0-8f9612e36c0e';
  $display->content['new-75c21320-6d29-4dad-b2a0-8f9612e36c0e'] = $pane;
  $display->panels['middle'][1] = 'new-75c21320-6d29-4dad-b2a0-8f9612e36c0e';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_bfe5b71e-99aa-442e-bd55-629b5f6e08aa'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function events_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'friends_events';
  $page->task = 'page';
  $page->admin_title = 'Friends Events';
  $page->admin_description = '';
  $page->path = 'events/friends';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_friends_events__panel_context_02e6e6d6-ebdd-4c18-9216-5e8bfcbec202';
  $handler->task = 'page';
  $handler->subtask = 'friends_events';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'single';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Upcoming Friends Events';
  $display->uuid = '32639aa6-cbe6-4470-aebe-5662184fe26e';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_friends_events__panel_context_02e6e6d6-ebdd-4c18-9216-5e8bfcbec202';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $pane->panel = 'middle';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'title_heading' => 'h2',
    'body' => '<div id="api_upc_cid12260_iid771"></div><script type="text/javascript" src="https://api3.libcal.com/api_events.php?iid=771&m=upc&cid=12260&audience=3531&c=&d=50867&l=50&simple=ul_date&context=object&format=js"> </script>

<p><a href="https://mediacentral.princeton.edu/channel/Friends%2Bof%2Bthe%2BPrinceton%2BUniversity%2BLibrary/170320411">View recordings of previous events</a>.</p>',
    'format' => 'full_html',
    'substitute' => TRUE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'libcal-upcoming-events-list',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $display->content['new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767'] = $pane;
  $display->panels['middle'][0] = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['friends_events'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'student_friends_events';
  $page->task = 'page';
  $page->admin_title = 'Student Friends Events';
  $page->admin_description = '';
  $page->path = 'events/student-friends';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_student_friends_events__panel';
  $handler->task = 'page';
  $handler->subtask = 'student_friends_events';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'single';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'middle' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Upcoming Student Friends Events';
  $display->uuid = '32639aa6-cbe6-4470-aebe-5662184fe26e';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_student_friends_events__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $pane->panel = 'middle';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'title_heading' => 'h2',
    'body' => '<div id="api_upc_cid12260_iid771"></div><script type="text/javascript" src="https://api3.libcal.com/api_events.php?iid=771&m=upc&cid=12260&audience=3770&c=&d=50867&l=50&simple=ul_date&context=object&format=js"> </script>',
    'format' => 'full_html',
    'substitute' => TRUE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'libcal-upcoming-events-list',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $display->content['new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767'] = $pane;
  $display->panels['middle'][0] = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-bfbb0fc2-508d-4c57-bfb0-9d4da8e17767';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['student_friends_events'] = $page;

  return $pages;

}
