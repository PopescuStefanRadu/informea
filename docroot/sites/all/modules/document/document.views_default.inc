<?php
/**
 * @file
 * document.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function document_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'documents';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_informea_documents';
  $view->human_name = 'Documents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Documents';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'nid' => 'nid',
    'field_image' => 'field_image',
    'field_files' => 'field_files',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_image' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_files' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Indexed Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Indexed Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Content: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Content: The main body text */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Indexed Content: Attached files */
  $handler->display->display_options['fields']['field_files']['id'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['field_files']['field'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['label'] = '';
  $handler->display->display_options['fields']['field_files']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_files']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_files']['type'] = 'file_table';
  $handler->display->display_options['fields']['field_files']['delta_offset'] = '0';
  /* Field: Indexed Content: Document type */
  $handler->display->display_options['fields']['field_document_type']['id'] = 'field_document_type';
  $handler->display->display_options['fields']['field_document_type']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['field_document_type']['field'] = 'field_document_type';
  $handler->display->display_options['fields']['field_document_type']['label'] = '';
  $handler->display->display_options['fields']['field_document_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_type']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_document_type']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_document_type']['bypass_access'] = 0;
  /* Field: Indexed Content: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['label'] = '';
  $handler->display->display_options['fields']['field_treaty']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_treaty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_treaty']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_treaty']['bypass_access'] = 0;
  /* Field: Indexed Content: Country */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_country']['alter']['text'] = '<h3>[title]</h3>
<p>[body]</p>
<dl class="dl-horizontal">
<dt>Instrument:&nbsp;&nbsp;</dt><dl>[field_treaty]</dl>
<dt>Category:&nbsp;&nbsp;</dt><dl>[field_document_type]</dl>
<dt>Country:&nbsp;&nbsp;</dt><dl>[field_country]</dl>
</dl>
[field_files]';
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_country']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_country']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_country']['bypass_access'] = 0;
  /* Filter criterion: Indexed Content: Country */
  $handler->display->display_options['filters']['field_country']['id'] = 'field_country';
  $handler->display->display_options['filters']['field_country']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['filters']['field_country']['field'] = 'field_country';
  $handler->display->display_options['filters']['field_country']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_country']['expose']['operator_id'] = 'field_country_op';
  $handler->display->display_options['filters']['field_country']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['field_country']['expose']['operator'] = 'field_country_op';
  $handler->display->display_options['filters']['field_country']['expose']['identifier'] = 'field_country';
  $handler->display->display_options['filters']['field_country']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
  );
  /* Filter criterion: Indexed Content: Document type */
  $handler->display->display_options['filters']['field_document_type']['id'] = 'field_document_type';
  $handler->display->display_options['filters']['field_document_type']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['filters']['field_document_type']['field'] = 'field_document_type';
  $handler->display->display_options['filters']['field_document_type']['value'] = array();
  $handler->display->display_options['filters']['field_document_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_document_type']['expose']['operator_id'] = 'field_document_type_op';
  $handler->display->display_options['filters']['field_document_type']['expose']['label'] = 'Document type';
  $handler->display->display_options['filters']['field_document_type']['expose']['operator'] = 'field_document_type_op';
  $handler->display->display_options['filters']['field_document_type']['expose']['identifier'] = 'field_document_type';
  $handler->display->display_options['filters']['field_document_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
  );
  $handler->display->display_options['filters']['field_document_type']['type'] = 'select';
  /* Filter criterion: Indexed Content: Treaty */
  $handler->display->display_options['filters']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['filters']['field_treaty']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['filters']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['filters']['field_treaty']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_treaty']['expose']['operator_id'] = 'field_treaty_op';
  $handler->display->display_options['filters']['field_treaty']['expose']['label'] = 'Instrument';
  $handler->display->display_options['filters']['field_treaty']['expose']['operator'] = 'field_treaty_op';
  $handler->display->display_options['filters']['field_treaty']['expose']['identifier'] = 'field_treaty';
  $handler->display->display_options['filters']['field_treaty']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
  );
  /* Filter criterion: Indexed Content: InforMEA Tags */
  $handler->display->display_options['filters']['field_informea_tags']['id'] = 'field_informea_tags';
  $handler->display->display_options['filters']['field_informea_tags']['table'] = 'search_api_index_informea_documents';
  $handler->display->display_options['filters']['field_informea_tags']['field'] = 'field_informea_tags';
  $handler->display->display_options['filters']['field_informea_tags']['value'] = array();
  $handler->display->display_options['filters']['field_informea_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_informea_tags']['expose']['operator_id'] = 'field_informea_tags_op';
  $handler->display->display_options['filters']['field_informea_tags']['expose']['label'] = 'InforMEA Tags';
  $handler->display->display_options['filters']['field_informea_tags']['expose']['operator'] = 'field_informea_tags_op';
  $handler->display->display_options['filters']['field_informea_tags']['expose']['identifier'] = 'field_informea_tags';
  $handler->display->display_options['filters']['field_informea_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
  );
  $handler->display->display_options['filters']['field_informea_tags']['group_info']['label'] = 'InforMEA Tags';
  $handler->display->display_options['filters']['field_informea_tags']['group_info']['identifier'] = 'field_informea_tags';
  $handler->display->display_options['filters']['field_informea_tags']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_informea_tags']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_informea_tags']['type'] = 'select';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'documents';
  $translatables['documents'] = array(
    t('Master'),
    t('Documents'),
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
    t('Node ID'),
    t('.'),
    t(','),
    t('<h3>[title]</h3>
<p>[body]</p>
<dl class="dl-horizontal">
<dt>Instrument:&nbsp;&nbsp;</dt><dl>[field_treaty]</dl>
<dt>Category:&nbsp;&nbsp;</dt><dl>[field_document_type]</dl>
<dt>Country:&nbsp;&nbsp;</dt><dl>[field_country]</dl>
</dl>
[field_files]'),
    t('Country'),
    t('Document type'),
    t('Instrument'),
    t('InforMEA Tags'),
    t('Page'),
  );
  $export['documents'] = $view;

  return $export;
}
