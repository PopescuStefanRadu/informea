<?php
/**
 * @file
 * decision.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function decision_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'decisions_of_meeting';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Decisions of meeting';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'From the same meeting';
  $handler->display->display_options['css_class'] = 'text-overflow-ellipsis';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = 'Previous';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'Next';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Decision number */
  $handler->display->display_options['fields']['field_decision_number']['id'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['table'] = 'field_data_field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['field'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['label'] = '';
  $handler->display->display_options['fields']['field_decision_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_decision_number']['type'] = 'text_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Field: Order (field_sorting_order) */
  $handler->display->display_options['sorts']['field_sorting_order_value']['id'] = 'field_sorting_order_value';
  $handler->display->display_options['sorts']['field_sorting_order_value']['table'] = 'field_data_field_sorting_order';
  $handler->display->display_options['sorts']['field_sorting_order_value']['field'] = 'field_sorting_order_value';
  /* Contextual filter: Content: Meeting (field_meeting) */
  $handler->display->display_options['arguments']['field_meeting_target_id']['id'] = 'field_meeting_target_id';
  $handler->display->display_options['arguments']['field_meeting_target_id']['table'] = 'field_data_field_meeting';
  $handler->display->display_options['arguments']['field_meeting_target_id']['field'] = 'field_meeting_target_id';
  $handler->display->display_options['arguments']['field_meeting_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_meeting_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_meeting_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_meeting_target_id']['summary_options']['items_per_page'] = '25';
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
    'decision' => 'decision',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Related decisions';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['label'] = '';
  $handler->display->display_options['fields']['field_treaty']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_treaty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_treaty']['delta_offset'] = '0';
  /* Field: Content: Meeting */
  $handler->display->display_options['fields']['field_meeting']['id'] = 'field_meeting';
  $handler->display->display_options['fields']['field_meeting']['table'] = 'field_data_field_meeting';
  $handler->display->display_options['fields']['field_meeting']['field'] = 'field_meeting';
  $handler->display->display_options['fields']['field_meeting']['label'] = '';
  $handler->display->display_options['fields']['field_meeting']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_meeting']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_meeting']['settings'] = array(
    'link' => 1,
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_treaty] / [field_meeting]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Decision number */
  $handler->display->display_options['fields']['field_decision_number']['id'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['table'] = 'field_data_field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['field'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['label'] = '';
  $handler->display->display_options['fields']['field_decision_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_decision_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_decision_number']['type'] = 'text_plain';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_decision_number] - [title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Field: Order (field_sorting_order) */
  $handler->display->display_options['sorts']['field_sorting_order_value']['id'] = 'field_sorting_order_value';
  $handler->display->display_options['sorts']['field_sorting_order_value']['table'] = 'field_data_field_sorting_order';
  $handler->display->display_options['sorts']['field_sorting_order_value']['field'] = 'field_sorting_order_value';
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: InforMEA tags (field_informea_tags) */
  $handler->display->display_options['arguments']['field_informea_tags_tid']['id'] = 'field_informea_tags_tid';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['table'] = 'field_data_field_informea_tags';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['field'] = 'field_informea_tags_tid';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_options']['node'] = TRUE;
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_options']['anyall'] = '+';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_options']['limit'] = TRUE;
  $handler->display->display_options['arguments']['field_informea_tags_tid']['default_argument_options']['vocabularies'] = array(
    'thesaurus_informea' => 'thesaurus_informea',
  );
  $handler->display->display_options['arguments']['field_informea_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_informea_tags_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['not'] = TRUE;
  $translatables['decisions_of_meeting'] = array(
    t('Master'),
    t('From the same meeting'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('Previous'),
    t('Next'),
    t('last »'),
    t('All'),
    t('Block'),
    t('Related decisions'),
    t('[field_treaty] / [field_meeting]'),
    t('[field_decision_number] - [title]'),
  );
  $export['decisions_of_meeting'] = $view;

  $view = new view();
  $view->name = 'other_meetings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Other meetings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Other meetings';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = 'Previous';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'Next';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Date -  start date (event_calendar_date) */
  $handler->display->display_options['sorts']['event_calendar_date_value']['id'] = 'event_calendar_date_value';
  $handler->display->display_options['sorts']['event_calendar_date_value']['table'] = 'field_data_event_calendar_date';
  $handler->display->display_options['sorts']['event_calendar_date_value']['field'] = 'event_calendar_date_value';
  $handler->display->display_options['sorts']['event_calendar_date_value']['order'] = 'DESC';
  /* Contextual filter: Content: Treaty (field_treaty) */
  $handler->display->display_options['arguments']['field_treaty_target_id']['id'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['arguments']['field_treaty_target_id']['field'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['relationship'] = 'reverse_field_treaty_node';
  $handler->display->display_options['arguments']['field_treaty_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['not'] = TRUE;
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
    'event_calendar' => 'event_calendar',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['other_meetings'] = array(
    t('Master'),
    t('Other meetings'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('Previous'),
    t('Next'),
    t('last »'),
    t('All'),
    t('Block'),
  );
  $export['other_meetings'] = $view;

  return $export;
}
