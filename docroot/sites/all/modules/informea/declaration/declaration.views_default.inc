<?php
/**
 * @file
 * declaration.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function declaration_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'declaration_ordering';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Declaration ordering';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Declaration ordering';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any declaration content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = '';
  $handler->display->display_options['fields']['draggableviews']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'declaration_ordering:page';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
  /* Sort criterion: Content: Nid */
  $handler->display->display_options['sorts']['nid']['id'] = 'nid';
  $handler->display->display_options['sorts']['nid']['table'] = 'node';
  $handler->display->display_options['sorts']['nid']['field'] = 'nid';
  /* Contextual filter: Content: Parent section (field_declaration_parent_section) */
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['id'] = 'field_declaration_parent_section_target_id';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['table'] = 'field_data_field_declaration_parent_section';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['field'] = 'field_declaration_parent_section_target_id';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_declaration_parent_section_target_id']['validate_options']['types'] = array(
    'declaration_section' => 'declaration_section',
  );
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
    'declaration_section' => 'declaration_section',
    'declaration_paragraph' => 'declaration_paragraph',
  );
  /* Filter criterion: Content: Parent section (field_declaration_parent_section) */
  $handler->display->display_options['filters']['field_declaration_parent_section_target_id_1']['id'] = 'field_declaration_parent_section_target_id_1';
  $handler->display->display_options['filters']['field_declaration_parent_section_target_id_1']['table'] = 'field_data_field_declaration_parent_section';
  $handler->display->display_options['filters']['field_declaration_parent_section_target_id_1']['field'] = 'field_declaration_parent_section_target_id';
  $handler->display->display_options['filters']['field_declaration_parent_section_target_id_1']['operator'] = 'empty';

  /* Display: Declaration ordering */
  $handler = $view->new_display('page', 'Declaration ordering', 'page');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Parent declaration (field_parent_declaration) */
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['id'] = 'field_parent_declaration_target_id';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['table'] = 'field_data_field_parent_declaration';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['field'] = 'field_parent_declaration_target_id';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_parent_declaration_target_id']['validate_options']['types'] = array(
    'declaration' => 'declaration',
  );
  $handler->display->display_options['path'] = 'node/%/order';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Order declaration content';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Section ordering */
  $handler = $view->new_display('page', 'Section ordering', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Section ordering';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'declaration_section' => 'declaration_section',
    'declaration_paragraph' => 'declaration_paragraph',
  );
  $handler->display->display_options['path'] = 'node/%/order-section';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Order section content';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['declaration_ordering'] = array(
    t('Master'),
    t('Declaration ordering'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Title'),
    t('Body'),
    t('All'),
    t('Section ordering'),
  );
  $export['declaration_ordering'] = $view;

  $view = new view();
  $view->name = 'declaration_parent_section_entity_view';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Declaration parent section entity view';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_parent_declaration_target_id']['id'] = 'field_parent_declaration_target_id';
  $handler->display->display_options['relationships']['field_parent_declaration_target_id']['table'] = 'field_data_field_parent_declaration';
  $handler->display->display_options['relationships']['field_parent_declaration_target_id']['field'] = 'field_parent_declaration_target_id';
  /* Field: Field: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['relationship'] = 'field_parent_declaration_target_id';
  $handler->display->display_options['fields']['field_abbreviation']['label'] = '';
  $handler->display->display_options['fields']['field_abbreviation']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
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
    'declaration_section' => 'declaration_section',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_abbreviation' => 'field_abbreviation',
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_abbreviation' => 'field_abbreviation',
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['declaration_parent_section_entity_view'] = array(
    t('Master'),
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
    t('Content entity referenced from field_parent_declaration'),
    t('Entity Reference'),
  );
  $export['declaration_parent_section_entity_view'] = $view;

  return $export;
}
