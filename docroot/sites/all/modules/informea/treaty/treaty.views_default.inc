<?php
/**
 * @file
 * treaty.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function treaty_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'decision_ordering';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Decision ordering';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'reorder decisions';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'draggableviews' => 'draggableviews',
    'field_decision_number' => 'field_decision_number',
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'draggableviews' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_decision_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['style_options']['caption'] = 'List of decisions for the selected meeting';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<b>Instructions</b>: Use this screen to reorder the decisions, per meeting:
<ol>
<li>Drag the decisions by their handler into the proper place</li>
<li>When you are satisfied with the display, press <em>Save</em> button at the bottom of the page</li>
</ol>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = 'Reordering @total decisions ...';
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['handler'] = 'draggableviews_handler_fieldapi';
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['save_button_label'] = 'Save order';
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 0;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['draggableviews_handler_fieldapi'] = array(
    'field' => 'field_data_field_sorting_order:field_sorting_order_value',
  );
  /* Field: Content: Decision number */
  $handler->display->display_options['fields']['field_decision_number']['id'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['table'] = 'field_data_field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['field'] = 'field_decision_number';
  $handler->display->display_options['fields']['field_decision_number']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_decision_number']['alter']['text'] = '<div class="col-md-4">[field_decision_number]</div>';
  $handler->display->display_options['fields']['field_decision_number']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_decision_number']['type'] = 'text_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Field: Order (field_sorting_order) */
  $handler->display->display_options['sorts']['field_sorting_order_value']['id'] = 'field_sorting_order_value';
  $handler->display->display_options['sorts']['field_sorting_order_value']['table'] = 'field_data_field_sorting_order';
  $handler->display->display_options['sorts']['field_sorting_order_value']['field'] = 'field_sorting_order_value';
  /* Contextual filter: Content: Treaty (field_treaty) */
  $handler->display->display_options['arguments']['field_treaty_target_id']['id'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['arguments']['field_treaty_target_id']['field'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_treaty_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_treaty_target_id']['summary_options']['items_per_page'] = '25';
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
  /* Filter criterion: Content: Meeting (field_meeting) */
  $handler->display->display_options['filters']['field_meeting_target_id']['id'] = 'field_meeting_target_id';
  $handler->display->display_options['filters']['field_meeting_target_id']['table'] = 'field_data_field_meeting';
  $handler->display->display_options['filters']['field_meeting_target_id']['field'] = 'field_meeting_target_id';
  $handler->display->display_options['filters']['field_meeting_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['operator_id'] = 'field_meeting_target_id_op';
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['label'] = 'Start by selecting a meeting';
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['operator'] = 'field_meeting_target_id_op';
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['identifier'] = 'field_meeting_target_id';
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['field_meeting_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Decisions ordering */
  $handler = $view->new_display('page', 'Decisions ordering', 'page_reorder');
  $handler->display->display_options['display_description'] = 'Order the appearance of decisions in listing';
  $handler->display->display_options['path'] = 'node/%/decision-reorder';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Order decisions';
  $handler->display->display_options['menu']['description'] = 'Allows you to set the order of decisions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['decision_ordering'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<b>Instructions</b>: Use this screen to reorder the decisions, per meeting:
<ol>
<li>Drag the decisions by their handler into the proper place</li>
<li>When you are satisfied with the display, press <em>Save</em> button at the bottom of the page</li>
</ol>'),
    t('Reordering @total decisions ...'),
    t('Content'),
    t('Decision number'),
    t('<div class="col-md-4">[field_decision_number]</div>'),
    t('All'),
    t('Start by selecting a meeting'),
    t('Decisions ordering'),
    t('Order the appearance of decisions in listing'),
  );
  $export['decision_ordering'] = $view;

  $view = new view();
  $view->name = 'reporting_obligations_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Reporting obligations admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Reporting obligations admin';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_treaty' => 'field_treaty',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_treaty' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_treaty']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
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
    'reporting_obligation_cycle' => 'reporting_obligation_cycle',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/reporting-obligations-';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Reporting obligations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['reporting_obligations_admin'] = array(
    t('Master'),
    t('Reporting obligations admin'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Title'),
    t('Treaty'),
    t('Edit link'),
    t('Delete link'),
    t('Page'),
  );
  $export['reporting_obligations_admin'] = $view;

  $view = new view();
  $view->name = 'treaty_listing_page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Treaty listing page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Treaties';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_logo' => 'field_logo',
    'title' => 'title',
    'field_informea_tags' => 'field_informea_tags',
    'field_official_name' => 'field_official_name',
    'field_region' => 'field_region',
    'field_entry_into_force' => 'field_entry_into_force',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_logo' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_informea_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_official_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_region' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_entry_into_force' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = 'Showing <span class="total">@total</span> treaties and protocols';
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => 'logo-large',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['label'] = '';
  $handler->display->display_options['fields']['title_field']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_field']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_field']['alter']['text'] = '<p class="text-muted">[title_field]</p>';
  $handler->display->display_options['fields']['title_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 0;
  /* Field: Content: InforMEA tags */
  $handler->display->display_options['fields']['field_informea_tags']['id'] = 'field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['table'] = 'field_data_field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['field'] = 'field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['label'] = '';
  $handler->display->display_options['fields']['field_informea_tags']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_informea_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_informea_tags']['alter']['text'] = '<p class="text-muted small"><strong>Topics:</strong> [field_informea_tags]</p>';
  $handler->display->display_options['fields']['field_informea_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_informea_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_informea_tags']['type'] = 'taxonomy_term_reference_csv';
  $handler->display->display_options['fields']['field_informea_tags']['settings'] = array(
    'links_option' => 0,
    'separator_option' => ', ',
    'element_option' => '- None -',
    'element_class' => '',
    'wrapper_option' => '- None -',
    'wrapper_class' => '',
  );
  $handler->display->display_options['fields']['field_informea_tags']['delta_offset'] = '0';
  /* Field: Content: Official name */
  $handler->display->display_options['fields']['field_official_name']['id'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['table'] = 'field_data_field_official_name';
  $handler->display->display_options['fields']['field_official_name']['field'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['label'] = '';
  $handler->display->display_options['fields']['field_official_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_official_name']['alter']['text'] = '[field_official_name]
[title_field]
[field_informea_tags]';
  $handler->display->display_options['fields']['field_official_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_official_name']['type'] = 'title_linked';
  $handler->display->display_options['fields']['field_official_name']['settings'] = array(
    'title_style' => 'h4',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: Content: Region */
  $handler->display->display_options['fields']['field_region']['id'] = 'field_region';
  $handler->display->display_options['fields']['field_region']['table'] = 'field_data_field_region';
  $handler->display->display_options['fields']['field_region']['field'] = 'field_region';
  $handler->display->display_options['fields']['field_region']['element_label_class'] = 'dropdown text-nowrap';
  $handler->display->display_options['fields']['field_region']['type'] = 'i18n_taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_region']['delta_offset'] = '0';
  /* Field: Content: Entry into force */
  $handler->display->display_options['fields']['field_entry_into_force']['id'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['table'] = 'field_data_field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['field'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['element_label_class'] = 'text-nowrap';
  $handler->display->display_options['fields']['field_entry_into_force']['empty'] = 'N/A';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'treaty_listing_page:page_reorder';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
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
    'treaty' => 'treaty',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Regional table */
  $handler = $view->new_display('page', 'Regional table', 'page');
  $handler->display->display_options['path'] = 'treaties';

  /* Display: Reorder treaties */
  $handler = $view->new_display('page', 'Reorder treaties', 'page_reorder');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'delete any treaty content';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = 'Order';
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 1;
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => 'logo',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 1;
  /* Field: Content: Official name */
  $handler->display->display_options['fields']['field_official_name']['id'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['table'] = 'field_data_field_official_name';
  $handler->display->display_options['fields']['field_official_name']['field'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_official_name']['settings'] = array(
    'title_style' => '_none',
    'title_link' => 'content',
    'title_class' => '',
  );
  $handler->display->display_options['path'] = 'admin/config/content/reorder-treaties';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Reorder treaties';
  $handler->display->display_options['menu']['description'] = 'Reorder the list of treaties in "treaties" page';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['treaty_listing_page'] = array(
    t('Master'),
    t('Treaties'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Showing <span class="total">@total</span> treaties and protocols'),
    t('<p class="text-muted">[title_field]</p>'),
    t('<p class="text-muted small"><strong>Topics:</strong> [field_informea_tags]</p>'),
    t('[field_official_name]
[title_field]
[field_informea_tags]'),
    t('Region'),
    t('Entry into force'),
    t('N/A'),
    t('Regional table'),
    t('Reorder treaties'),
    t('Order'),
    t('Title'),
    t('Official name'),
  );
  $export['treaty_listing_page'] = $view;

  return $export;
}
