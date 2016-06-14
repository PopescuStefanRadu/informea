<?php
/**
 * @file
 * goal.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function goal_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'geg';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'GEG';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_thumbnail_plugin_style';
  $handler->display->display_options['style_options']['columns'] = '1';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: GEG Theme */
  $handler->display->display_options['fields']['field_geg_theme']['id'] = 'field_geg_theme';
  $handler->display->display_options['fields']['field_geg_theme']['table'] = 'field_data_field_geg_theme';
  $handler->display->display_options['fields']['field_geg_theme']['field'] = 'field_geg_theme';
  $handler->display->display_options['fields']['field_geg_theme']['label'] = 'Theme';
  $handler->display->display_options['fields']['field_geg_theme']['delta_offset'] = '0';
  /* Field: Content: Geographical scope */
  $handler->display->display_options['fields']['field_geographical_scope']['id'] = 'field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['table'] = 'field_data_field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['field'] = 'field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: GEG Theme (field_geg_theme) */
  $handler->display->display_options['sorts']['field_geg_theme_tid']['id'] = 'field_geg_theme_tid';
  $handler->display->display_options['sorts']['field_geg_theme_tid']['table'] = 'field_data_field_geg_theme';
  $handler->display->display_options['sorts']['field_geg_theme_tid']['field'] = 'field_geg_theme_tid';
  $handler->display->display_options['sorts']['field_geg_theme_tid']['expose']['label'] = 'Theme';
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
    'goal' => 'goal',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Goal Type (field_goal_type) */
  $handler->display->display_options['filters']['field_goal_type_tid']['id'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['table'] = 'field_data_field_goal_type';
  $handler->display->display_options['filters']['field_goal_type_tid']['field'] = 'field_goal_type_tid';
  $handler->display->display_options['filters']['field_goal_type_tid']['value'] = array(
    1733 => '1733',
  );
  $handler->display->display_options['filters']['field_goal_type_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_goal_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_goal_type_tid']['vocabulary'] = 'type_of_goal';
  /* Filter criterion: Content: GEG Theme (field_geg_theme) */
  $handler->display->display_options['filters']['field_geg_theme_tid']['id'] = 'field_geg_theme_tid';
  $handler->display->display_options['filters']['field_geg_theme_tid']['table'] = 'field_data_field_geg_theme';
  $handler->display->display_options['filters']['field_geg_theme_tid']['field'] = 'field_geg_theme_tid';
  $handler->display->display_options['filters']['field_geg_theme_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_geg_theme_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geg_theme_tid']['expose']['operator_id'] = 'field_geg_theme_tid_op';
  $handler->display->display_options['filters']['field_geg_theme_tid']['expose']['label'] = 'Theme';
  $handler->display->display_options['filters']['field_geg_theme_tid']['expose']['operator'] = 'field_geg_theme_tid_op';
  $handler->display->display_options['filters']['field_geg_theme_tid']['expose']['identifier'] = 'field_geg_theme_tid';
  $handler->display->display_options['filters']['field_geg_theme_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_geg_theme_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_geg_theme_tid']['vocabulary'] = 'geg_theme';
  /* Filter criterion: Content: Geographical scope (field_geographical_scope) */
  $handler->display->display_options['filters']['field_geographical_scope_tid']['id'] = 'field_geographical_scope_tid';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['table'] = 'field_data_field_geographical_scope';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['field'] = 'field_geographical_scope_tid';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_geographical_scope_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_scope_tid']['expose']['operator_id'] = 'field_geographical_scope_tid_op';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['expose']['label'] = 'Geographical scope';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['expose']['operator'] = 'field_geographical_scope_tid_op';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['expose']['identifier'] = 'field_geographical_scope_tid';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_geographical_scope_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_geographical_scope_tid']['vocabulary'] = 'geographical_scope';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['geg'] = array(
    t('Master'),
    t('<none>'),
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
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Theme'),
    t('Geographical scope'),
    t('Block'),
  );
  $export['geg'] = $view;

  $view = new view();
  $view->name = 'goals_geg_listing_admin_page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Goals: GEG listing admin page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Goals: GEG listing admin page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  /* Field: Content: GEG Tags */
  $handler->display->display_options['fields']['field_geg_tags']['id'] = 'field_geg_tags';
  $handler->display->display_options['fields']['field_geg_tags']['table'] = 'field_data_field_geg_tags';
  $handler->display->display_options['fields']['field_geg_tags']['field'] = 'field_geg_tags';
  $handler->display->display_options['fields']['field_geg_tags']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_geg_tags']['delta_offset'] = '0';
  /* Field: Content: Geographical scope */
  $handler->display->display_options['fields']['field_geographical_scope']['id'] = 'field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['table'] = 'field_data_field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['field'] = 'field_geographical_scope';
  $handler->display->display_options['fields']['field_geographical_scope']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_geographical_scope']['delta_offset'] = '0';
  /* Field: Content: Document URL */
  $handler->display->display_options['fields']['field_document_url']['id'] = 'field_document_url';
  $handler->display->display_options['fields']['field_document_url']['table'] = 'field_data_field_document_url';
  $handler->display->display_options['fields']['field_document_url']['field'] = 'field_document_url';
  $handler->display->display_options['fields']['field_document_url']['label'] = 'Reference';
  $handler->display->display_options['fields']['field_document_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_document_url']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
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
    'goal' => 'goal',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/goals/geg';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'GEG Goals';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['goals_geg_listing_admin_page'] = array(
    t('Master'),
    t('Goals: GEG listing admin page'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Title'),
    t('Body'),
    t('GEG Tags'),
    t('Geographical scope'),
    t('Reference'),
    t('Page'),
  );
  $export['goals_geg_listing_admin_page'] = $view;

  $view = new view();
  $view->name = 'list_of_principles_declarations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'List of principles (Declarations)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List of principles (Declarations)';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns'] = '4';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Field: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['label'] = '';
  $handler->display->display_options['fields']['field_abbreviation']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'declaration' => 'declaration',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_description'] = 'Grid with principles';
  $translatables['list_of_principles_declarations'] = array(
    t('Master'),
    t('List of principles (Declarations)'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Block'),
    t('Grid with principles'),
  );
  $export['list_of_principles_declarations'] = $view;

  $view = new view();
  $view->name = 'strategic_goals_and_targets';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Strategic Goals and Targets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Goals and Principles';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_grid_plugin_style';
  $handler->display->display_options['style_options']['columns'] = '4';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Taxonomy term: Entity translation: translations */
  $handler->display->display_options['relationships']['entity_translations']['id'] = 'entity_translations';
  $handler->display->display_options['relationships']['entity_translations']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['entity_translations']['field'] = 'entity_translations';
  /* Field: Field: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['label'] = '';
  $handler->display->display_options['fields']['field_abbreviation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_abbreviation']['type'] = 'title_linked';
  $handler->display->display_options['fields']['field_abbreviation']['settings'] = array(
    'title_style' => 'h2',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['element_wrapper_class'] = 'text-muted';
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'goal_sources' => 'goal_sources',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  /* Filter criterion: Entity translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'entity_translation';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['relationship'] = 'entity_translations';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
  );
  $handler->display->display_options['filters']['language']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'goals';
  $translatables['strategic_goals_and_targets'] = array(
    t('Master'),
    t('Goals and Principles'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Translations'),
    t('Page'),
  );
  $export['strategic_goals_and_targets'] = $view;

  return $export;
}
