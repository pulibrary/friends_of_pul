<?php
/**
 * @file
 * panel_variants.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function panel_variants_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__about-the-friends';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'About the Friends',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'about-the-friends',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'front',
          'settings' => NULL,
          'not' => TRUE,
        ),
        1 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'about-friends',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'pul-base-nine-three';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'first' => NULL,
      'second' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '4b73c635-3b72-4098-bce6-21e4846d715a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2a4aad47-d717-4c0a-b701-cfde27615bc2';
    $pane->panel = 'first';
    $pane->type = 'block';
    $pane->subtype = 'views-friends_council_members-block_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Members of Council',
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
    $pane->uuid = '2a4aad47-d717-4c0a-b701-cfde27615bc2';
    $display->content['new-2a4aad47-d717-4c0a-b701-cfde27615bc2'] = $pane;
    $display->panels['first'][0] = 'new-2a4aad47-d717-4c0a-b701-cfde27615bc2';
    $pane = new stdClass();
    $pane->pid = 'new-91369b8f-2f10-463e-8263-a465e221ed52';
    $pane->panel = 'first';
    $pane->type = 'entity_view';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '91369b8f-2f10-463e-8263-a465e221ed52';
    $display->content['new-91369b8f-2f10-463e-8263-a465e221ed52'] = $pane;
    $display->panels['first'][1] = 'new-91369b8f-2f10-463e-8263-a465e221ed52';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__about-the-friends'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_5ee668ee-d594-4300-a7cb-9c9d7f8d7653';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Landing page',
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
          'name' => 'front',
          'settings' => NULL,
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'three-six-three-stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'first' => NULL,
      'middle' => NULL,
      'second' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7d49b8a2-b7cb-4f6d-8545-c7999e108ca8';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0b1d8ae7-b961-4046-af25-9233d2bff389';
    $pane->panel = 'first';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Friends Button',
      'title' => '<none>',
      'body' => '<p><a class="button--join-friends" href="https://makeagift.princeton.edu/fpul/MakeAGift.aspx">Join the Friends</a></p>
<h3 class="login_field">Benefits of Friendship</h3>
<p>Members of the Friends of the Princeton University Library make a vital contribution to the strength of the University’s collections, to the educational experience of its students, and to scholars and collectors throughout the world. Learn more about the <a href="/join-friends">Benefits of Friendship</a>.</p>',
      'format' => 'full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0b1d8ae7-b961-4046-af25-9233d2bff389';
    $display->content['new-0b1d8ae7-b961-4046-af25-9233d2bff389'] = $pane;
    $display->panels['first'][0] = 'new-0b1d8ae7-b961-4046-af25-9233d2bff389';
    $pane = new stdClass();
    $pane->pid = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $display->content['new-120eef27-73e7-41a2-bbc1-1de882dcf0c3'] = $pane;
    $display->panels['middle'][0] = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $pane = new stdClass();
    $pane->pid = 'new-dd350ad5-d5d9-4571-a17b-610434e2e738';
    $pane->panel = 'second';
    $pane->type = 'block';
    $pane->subtype = 'views-calendar-block_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Upcoming Events',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'calendar-block',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'dd350ad5-d5d9-4571-a17b-610434e2e738';
    $display->content['new-dd350ad5-d5d9-4571-a17b-610434e2e738'] = $pane;
    $display->panels['second'][0] = 'new-dd350ad5-d5d9-4571-a17b-610434e2e738';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_5ee668ee-d594-4300-a7cb-9c9d7f8d7653'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_866cf23f-5924-4796-afd6-1f64e59bf6c8';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Webform',
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
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'webform' => 'webform',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'pul-base-nine-three';
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
  $display->uuid = '8a83ceb1-2a9e-46c1-ba21-260c74c68a6d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-dfc9a3fd-f322-4b97-acdd-28c514a9ed2a';
    $pane->panel = 'first';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 1,
      'no_extras' => 0,
      'override_title' => 1,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 1,
      'leave_node_title' => 0,
      'build_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = 'dfc9a3fd-f322-4b97-acdd-28c514a9ed2a';
    $display->content['new-dfc9a3fd-f322-4b97-acdd-28c514a9ed2a'] = $pane;
    $display->panels['first'][0] = 'new-dfc9a3fd-f322-4b97-acdd-28c514a9ed2a';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-dfc9a3fd-f322-4b97-acdd-28c514a9ed2a';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_866cf23f-5924-4796-afd6-1f64e59bf6c8'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_efab4f63-8a1e-4d53-a132-e3cd71f64546';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -27;
  $handler->conf = array(
    'title' => 'Basic pages',
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
          'name' => 'front',
          'settings' => NULL,
          'not' => TRUE,
        ),
        1 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '0',
            'paths' => 'student-friends
events',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'pul-base-nine-three';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'first' => NULL,
      'second' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '4b73c635-3b72-4098-bce6-21e4846d715a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-91369b8f-2f10-463e-8263-a465e221ed52';
    $pane->panel = 'first';
    $pane->type = 'entity_view';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '91369b8f-2f10-463e-8263-a465e221ed52';
    $display->content['new-91369b8f-2f10-463e-8263-a465e221ed52'] = $pane;
    $display->panels['first'][0] = 'new-91369b8f-2f10-463e-8263-a465e221ed52';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_efab4f63-8a1e-4d53-a132-e3cd71f64546'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__student-landing-page';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -26;
  $handler->conf = array(
    'title' => 'Student - Landing page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'student-landing-page',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'student-friends',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'nine-three-stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'first' => NULL,
      'middle' => NULL,
      'second' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7d49b8a2-b7cb-4f6d-8545-c7999e108ca8';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $pane->panel = 'first';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $display->content['new-120eef27-73e7-41a2-bbc1-1de882dcf0c3'] = $pane;
    $display->panels['first'][0] = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
    $pane = new stdClass();
    $pane->pid = 'new-e6fe2a7e-6700-448e-bc40-2d92d2a0a169';
    $pane->panel = 'second';
    $pane->type = 'block';
    $pane->subtype = 'views-calendar-block_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Upcoming Student Friends Events',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'calendar-block',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e6fe2a7e-6700-448e-bc40-2d92d2a0a169';
    $display->content['new-e6fe2a7e-6700-448e-bc40-2d92d2a0a169'] = $pane;
    $display->panels['second'][0] = 'new-e6fe2a7e-6700-448e-bc40-2d92d2a0a169';
    $pane = new stdClass();
    $pane->pid = 'new-b599728a-8f5a-445f-8e41-0801eeb96651';
    $pane->panel = 'top';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Student Friends Banner',
      'title' => '',
      'body' => '<p><img src="/sites/all/themes/friends/assets/public/images/student-friends.jpg" alt="Student Friends of the Princeton University Library" /></p>',
      'format' => 'full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b599728a-8f5a-445f-8e41-0801eeb96651';
    $display->content['new-b599728a-8f5a-445f-8e41-0801eeb96651'] = $pane;
    $display->panels['top'][0] = 'new-b599728a-8f5a-445f-8e41-0801eeb96651';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-120eef27-73e7-41a2-bbc1-1de882dcf0c3';
  $handler->conf['display'] = $display;
  $export['node_view__student-landing-page'] = $handler;

  return $export;
}
