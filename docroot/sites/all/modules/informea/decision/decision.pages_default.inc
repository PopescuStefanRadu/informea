<?php
/**
 * @file
 * decision.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function decision_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_3945cec5-f166-42f9-bc42-092828e1c592';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Decision',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'Content from Content (on Content: Treaty [field_treaty])',
        'keyword' => 'treaty',
        'name' => 'entity_from_field:field_treaty-node-node',
        'delta' => '0',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
      1 => array(
        'identifier' => 'Content from Content (on Content: Meeting [field_meeting])',
        'keyword' => 'meeting',
        'name' => 'entity_from_field:field_meeting-node-node',
        'delta' => 0,
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'decision' => 'decision',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Treaties
%treaty:title-field
Decisions
%node:title-field',
    'panels_breadcrumbs_paths' => 'treaties
%treaty:url
%treaty:url/decisions
<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
        'class' => 'node-decision row',
        'column_class' => '',
        'row_class' => '',
        'region_class' => '',
        'no_scale' => FALSE,
        'fixed_width' => '',
        'column_separation' => '',
        'region_separation' => '.5em',
        'row_separation' => '',
        'hide_empty' => 0,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 2,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 3,
          1 => 4,
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '2',
        'children' => array(
          0 => 5,
          1 => 11,
          2 => 16,
          3 => 21,
          4 => 26,
        ),
        'class' => 'col-md-9',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '2',
        'children' => array(
          0 => 10,
        ),
        'class' => 'col-md-3 sidebar-right',
        'hide_empty' => 0,
      ),
      5 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 6,
          1 => 8,
        ),
        'parent' => '3',
        'class' => 'row',
        'hide_empty' => 0,
      ),
      6 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '5',
        'children' => array(
          0 => 7,
        ),
        'class' => 'col-sm-6',
        'hide_empty' => 0,
      ),
      7 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'treaty',
        ),
        'parent' => '6',
        'class' => 'row',
        'hide_empty' => 0,
      ),
      'treaty' => array(
        'type' => 'region',
        'title' => 'treaty',
        'width' => 100,
        'width_type' => '%',
        'parent' => '7',
        'class' => '',
        'hide_empty' => 0,
      ),
      8 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '5',
        'children' => array(
          0 => 9,
        ),
        'class' => 'col-sm-6',
        'hide_empty' => 0,
      ),
      9 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'meeting',
        ),
        'parent' => '8',
        'class' => '',
        'hide_empty' => 0,
      ),
      'meeting' => array(
        'type' => 'region',
        'title' => 'meeting',
        'width' => 100,
        'width_type' => '%',
        'parent' => '9',
        'class' => '',
        'hide_empty' => 0,
      ),
      10 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'sidebar_',
        ),
        'parent' => '4',
        'class' => 'row',
        'hide_empty' => 0,
      ),
      'sidebar_' => array(
        'type' => 'region',
        'title' => 'sidebar',
        'width' => 100,
        'width_type' => '%',
        'parent' => '10',
        'class' => '',
        'hide_empty' => 0,
      ),
      11 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 12,
          1 => 14,
        ),
        'parent' => '3',
        'class' => 'decision-files-other-container row',
        'hide_empty' => 0,
      ),
      12 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '11',
        'children' => array(
          0 => 13,
        ),
        'class' => 'col-sm-6',
        'hide_empty' => 0,
      ),
      13 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'files',
        ),
        'parent' => '12',
        'class' => '',
        'hide_empty' => 0,
      ),
      'files' => array(
        'type' => 'region',
        'title' => 'Files',
        'width' => 100,
        'width_type' => '%',
        'parent' => '13',
        'class' => '',
        'hide_empty' => 0,
      ),
      14 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '11',
        'children' => array(
          0 => 15,
        ),
        'class' => 'col-sm-6',
        'hide_empty' => 0,
      ),
      15 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'other',
        ),
        'parent' => '14',
        'class' => '',
        'hide_empty' => 0,
      ),
      'other' => array(
        'type' => 'region',
        'title' => 'Other',
        'width' => 100,
        'width_type' => '%',
        'parent' => '15',
        'class' => '',
        'hide_empty' => 0,
      ),
      16 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 17,
          1 => 18,
        ),
        'parent' => '3',
        'class' => 'decision-update-container row',
        'hide_empty' => 0,
      ),
      17 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '16',
        'children' => array(
          0 => 20,
        ),
        'class' => 'col-sm-9',
        'hide_empty' => 0,
      ),
      18 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '16',
        'children' => array(
          0 => 19,
        ),
        'class' => 'col-sm-3',
        'hide_empty' => 0,
      ),
      19 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tags',
        ),
        'parent' => '18',
        'class' => '',
        'hide_empty' => 0,
      ),
      'tags' => array(
        'type' => 'region',
        'title' => 'Share',
        'width' => 100,
        'width_type' => '%',
        'parent' => '19',
        'class' => '',
        'hide_empty' => 0,
      ),
      20 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'updates',
        ),
        'parent' => '17',
        'class' => 'decision-updates-form-container',
        'hide_empty' => 0,
      ),
      'updates' => array(
        'type' => 'region',
        'title' => 'Updates',
        'width' => 100,
        'width_type' => '%',
        'parent' => '20',
        'class' => 'decision-updates-form-container',
        'hide_empty' => 0,
      ),
      21 => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 22,
          1 => 23,
        ),
        'parent' => '3',
        'class' => 'decision-tags-container',
        'hide_empty' => 1,
      ),
      22 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '21',
        'children' => array(
          0 => 24,
        ),
        'class' => 'col-sm-9',
        'hide_empty' => 1,
      ),
      23 => array(
        'type' => 'column',
        'width' => 50,
        'width_type' => '%',
        'parent' => '21',
        'children' => array(
          0 => 25,
        ),
        'class' => 'col-sm-3',
        'hide_empty' => 1,
      ),
      24 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'related',
        ),
        'parent' => '22',
        'class' => 'decision-',
        'hide_empty' => 1,
      ),
      'related' => array(
        'type' => 'region',
        'title' => 'Related',
        'width' => 100,
        'width_type' => '%',
        'parent' => '24',
        'class' => '',
        'hide_empty' => 1,
      ),
      25 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'tags_',
        ),
        'parent' => '23',
        'class' => '',
        'hide_empty' => 1,
      ),
      'tags_' => array(
        'type' => 'region',
        'title' => 'Tags',
        'width' => 100,
        'width_type' => '%',
        'parent' => '25',
        'class' => '',
        'hide_empty' => 1,
      ),
      26 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'text',
        ),
        'parent' => '3',
        'class' => 'decision-text-container row',
        'hide_empty' => 0,
      ),
      'text' => array(
        'type' => 'region',
        'title' => 'Text',
        'width' => 100,
        'width_type' => '%',
        'parent' => '26',
        'class' => 'col-md-12',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'sidebar' => NULL,
      'treaty' => NULL,
      'meeting' => NULL,
      'sidebar_' => NULL,
      'files' => NULL,
      'other' => NULL,
      'tags' => NULL,
      'updates' => NULL,
      'related' => NULL,
      'tags_' => NULL,
      'text' => NULL,
    ),
    'style' => 'default',
    'sidebar_' => array(
      'style' => 'default',
    ),
    'meeting' => array(
      'style' => 'default',
    ),
    'files' => array(
      'style' => 'default',
    ),
    'center' => array(
      'style' => 'default',
    ),
    'other' => array(
      'style' => 'default',
    ),
    'treaty' => array(
      'style' => 'default',
    ),
    'tags' => array(
      'style' => 'default',
    ),
    'updates' => array(
      'style' => 'default',
    ),
    'related' => array(
      'style' => 'default',
    ),
    'tags_' => array(
      'style' => 'default',
    ),
    'text' => array(
      'style' => 'default',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'c7358b75-ee04-4833-b717-eadc41d040b6';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-6c18c74d-7074-4870-8391-d87999f9cbb1';
    $pane->panel = 'files';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_files';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'informea_file_dropdown',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
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
    $pane->uuid = '6c18c74d-7074-4870-8391-d87999f9cbb1';
    $display->content['new-6c18c74d-7074-4870-8391-d87999f9cbb1'] = $pane;
    $display->panels['files'][0] = 'new-6c18c74d-7074-4870-8391-d87999f9cbb1';
    $pane = new stdClass();
    $pane->pid = 'new-b51ac893-861c-45da-ab89-12ef777f68c4';
    $pane->panel = 'meeting';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_meeting';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'entityreference_label',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'link' => 1,
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => 'Meeting',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b51ac893-861c-45da-ab89-12ef777f68c4';
    $display->content['new-b51ac893-861c-45da-ab89-12ef777f68c4'] = $pane;
    $display->panels['meeting'][0] = 'new-b51ac893-861c-45da-ab89-12ef777f68c4';
    $pane = new stdClass();
    $pane->pid = 'new-de88f21c-d493-4515-9ac1-cbd958a0fcc1';
    $pane->panel = 'other';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_decision_type';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'taxonomy_term_reference_plain',
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
    $pane->uuid = 'de88f21c-d493-4515-9ac1-cbd958a0fcc1';
    $display->content['new-de88f21c-d493-4515-9ac1-cbd958a0fcc1'] = $pane;
    $display->panels['other'][0] = 'new-de88f21c-d493-4515-9ac1-cbd958a0fcc1';
    $pane = new stdClass();
    $pane->pid = 'new-0b7f9376-dfdd-4da6-a8f1-2a8fd6d99fa4';
    $pane->panel = 'other';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_decision_status';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'above',
      'formatter' => 'taxonomy_term_reference_plain',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '0b7f9376-dfdd-4da6-a8f1-2a8fd6d99fa4';
    $display->content['new-0b7f9376-dfdd-4da6-a8f1-2a8fd6d99fa4'] = $pane;
    $display->panels['other'][1] = 'new-0b7f9376-dfdd-4da6-a8f1-2a8fd6d99fa4';
    $pane = new stdClass();
    $pane->pid = 'new-fae01ff2-33b7-4c60-9677-ad73170eefe2';
    $pane->panel = 'other';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p><a href="#decision-body-field">Skip to full text</a></p>',
      'format' => 'full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'skip-to-body',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'fae01ff2-33b7-4c60-9677-ad73170eefe2';
    $display->content['new-fae01ff2-33b7-4c60-9677-ad73170eefe2'] = $pane;
    $display->panels['other'][2] = 'new-fae01ff2-33b7-4c60-9677-ad73170eefe2';
    $pane = new stdClass();
    $pane->pid = 'new-4dbad596-dbaa-462f-b8f5-b21b9b3b36e4';
    $pane->panel = 'other';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '4dbad596-dbaa-462f-b8f5-b21b9b3b36e4';
    $display->content['new-4dbad596-dbaa-462f-b8f5-b21b9b3b36e4'] = $pane;
    $display->panels['other'][3] = 'new-4dbad596-dbaa-462f-b8f5-b21b9b3b36e4';
    $pane = new stdClass();
    $pane->pid = 'new-0454952e-d26e-4f56-b07c-95b96095dfa3';
    $pane->panel = 'other';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_related_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'relationship_entity_from_field:field_meeting-node-node_1',
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '0454952e-d26e-4f56-b07c-95b96095dfa3';
    $display->content['new-0454952e-d26e-4f56-b07c-95b96095dfa3'] = $pane;
    $display->panels['other'][4] = 'new-0454952e-d26e-4f56-b07c-95b96095dfa3';
    $pane = new stdClass();
    $pane->pid = 'new-a8ac1704-3835-41af-ae25-eefc7723b727';
    $pane->panel = 'related';
    $pane->type = 'views';
    $pane->subtype = 'decisions_of_meeting';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '6',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'context' => array(
        0 => '',
      ),
      'override_title' => 1,
      'override_title_text' => 'Related decisions',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a8ac1704-3835-41af-ae25-eefc7723b727';
    $display->content['new-a8ac1704-3835-41af-ae25-eefc7723b727'] = $pane;
    $display->panels['related'][0] = 'new-a8ac1704-3835-41af-ae25-eefc7723b727';
    $pane = new stdClass();
    $pane->pid = 'new-8e35cbef-987c-4a4a-bbd4-b3ac85c1eb13';
    $pane->panel = 'sidebar_';
    $pane->type = 'views';
    $pane->subtype = 'decisions_of_meeting';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '6',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'context' => array(
        0 => 'relationship_entity_from_field:field_meeting-node-node_1.nid',
      ),
      'override_title' => 1,
      'override_title_text' => 'From the same meeting',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8e35cbef-987c-4a4a-bbd4-b3ac85c1eb13';
    $display->content['new-8e35cbef-987c-4a4a-bbd4-b3ac85c1eb13'] = $pane;
    $display->panels['sidebar_'][0] = 'new-8e35cbef-987c-4a4a-bbd4-b3ac85c1eb13';
    $pane = new stdClass();
    $pane->pid = 'new-4cb6f15a-ef20-4552-b762-58f6b6f692f2';
    $pane->panel = 'sidebar_';
    $pane->type = 'views';
    $pane->subtype = 'other_meetings';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '2',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'context' => array(
        0 => 'relationship_entity_from_field:field_treaty-node-node_1.nid',
        1 => '',
      ),
      'override_title' => 1,
      'override_title_text' => 'Other meetings',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '4cb6f15a-ef20-4552-b762-58f6b6f692f2';
    $display->content['new-4cb6f15a-ef20-4552-b762-58f6b6f692f2'] = $pane;
    $display->panels['sidebar_'][1] = 'new-4cb6f15a-ef20-4552-b762-58f6b6f692f2';
    $pane = new stdClass();
    $pane->pid = 'new-0ab02b61-b2c1-4556-973a-f563bb40c93a';
    $pane->panel = 'tags';
    $pane->type = 'block';
    $pane->subtype = 'informea-informea_share';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Share decision',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0ab02b61-b2c1-4556-973a-f563bb40c93a';
    $display->content['new-0ab02b61-b2c1-4556-973a-f563bb40c93a'] = $pane;
    $display->panels['tags'][0] = 'new-0ab02b61-b2c1-4556-973a-f563bb40c93a';
    $pane = new stdClass();
    $pane->pid = 'new-b07d2c94-b115-4220-b34b-8c5b6ada8f4d';
    $pane->panel = 'tags_';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_informea_tags';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'taxonomy_term_reference_link',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => 'Tags',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b07d2c94-b115-4220-b34b-8c5b6ada8f4d';
    $display->content['new-b07d2c94-b115-4220-b34b-8c5b6ada8f4d'] = $pane;
    $display->panels['tags_'][0] = 'new-b07d2c94-b115-4220-b34b-8c5b6ada8f4d';
    $pane = new stdClass();
    $pane->pid = 'new-3b880e00-5e94-455e-8004-7a43ca36aece';
    $pane->panel = 'text';
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
      'override_title' => 1,
      'override_title_text' => 'Full text',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'decision-body-field',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3b880e00-5e94-455e-8004-7a43ca36aece';
    $display->content['new-3b880e00-5e94-455e-8004-7a43ca36aece'] = $pane;
    $display->panels['text'][0] = 'new-3b880e00-5e94-455e-8004-7a43ca36aece';
    $pane = new stdClass();
    $pane->pid = 'new-4bfec490-b7b1-4f6b-8edb-ed8f2d751f31';
    $pane->panel = 'text';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_files';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'informea_pdf_js',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '4bfec490-b7b1-4f6b-8edb-ed8f2d751f31';
    $display->content['new-4bfec490-b7b1-4f6b-8edb-ed8f2d751f31'] = $pane;
    $display->panels['text'][1] = 'new-4bfec490-b7b1-4f6b-8edb-ed8f2d751f31';
    $pane = new stdClass();
    $pane->pid = 'new-042196e4-4f93-4987-9cab-133c3121514c';
    $pane->panel = 'treaty';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_official_name';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'title_linked',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'title_style' => '_none',
        'title_link' => 'content',
        'title_class' => '',
      ),
      'context' => 'relationship_entity_from_field:field_treaty-node-node_1',
      'override_title' => 1,
      'override_title_text' => 'Treaty',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '042196e4-4f93-4987-9cab-133c3121514c';
    $display->content['new-042196e4-4f93-4987-9cab-133c3121514c'] = $pane;
    $display->panels['treaty'][0] = 'new-042196e4-4f93-4987-9cab-133c3121514c';
    $pane = new stdClass();
    $pane->pid = 'new-8d4320d8-cdb4-44bb-975a-5c92088d11d1';
    $pane->panel = 'updates';
    $pane->type = 'block';
    $pane->subtype = 'informea-informea_subscribe_updates';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Stay updated',
      'override_title_heading' => 'h4',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8d4320d8-cdb4-44bb-975a-5c92088d11d1';
    $display->content['new-8d4320d8-cdb4-44bb-975a-5c92088d11d1'] = $pane;
    $display->panels['updates'][0] = 'new-8d4320d8-cdb4-44bb-975a-5c92088d11d1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_3945cec5-f166-42f9-bc42-092828e1c592'] = $handler;

  return $export;
}
