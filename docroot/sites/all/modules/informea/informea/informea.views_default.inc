<?php
/**
 * @file
 * informea.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function informea_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'list_of_all_treaties';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'List of all treaties';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List of all treaties';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: OData identifier */
  $handler->display->display_options['fields']['field_odata_identifier']['id'] = 'field_odata_identifier';
  $handler->display->display_options['fields']['field_odata_identifier']['table'] = 'field_data_field_odata_identifier';
  $handler->display->display_options['fields']['field_odata_identifier']['field'] = 'field_odata_identifier';
  $handler->display->display_options['fields']['field_odata_identifier']['label'] = '';
  $handler->display->display_options['fields']['field_odata_identifier']['element_label_colon'] = FALSE;
  /* Field: Content: Content UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = '';
  $handler->display->display_options['fields']['uuid']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Official name */
  $handler->display->display_options['fields']['field_official_name']['id'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['table'] = 'field_data_field_official_name';
  $handler->display->display_options['fields']['field_official_name']['field'] = 'field_official_name';
  $handler->display->display_options['fields']['field_official_name']['label'] = '';
  $handler->display->display_options['fields']['field_official_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title abbreviation */
  $handler->display->display_options['fields']['field_title_abbreviation']['id'] = 'field_title_abbreviation';
  $handler->display->display_options['fields']['field_title_abbreviation']['table'] = 'field_data_field_title_abbreviation';
  $handler->display->display_options['fields']['field_title_abbreviation']['field'] = 'field_title_abbreviation';
  $handler->display->display_options['fields']['field_title_abbreviation']['label'] = '';
  $handler->display->display_options['fields']['field_title_abbreviation']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'description';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Entry into force */
  $handler->display->display_options['fields']['field_entry_into_force']['id'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['table'] = 'field_data_field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['field'] = 'field_entry_into_force';
  $handler->display->display_options['fields']['field_entry_into_force']['label'] = '';
  $handler->display->display_options['fields']['field_entry_into_force']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_entry_into_force']['type'] = 'services';
  $handler->display->display_options['fields']['field_entry_into_force']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: InforMEA Tags */
  $handler->display->display_options['fields']['field_informea_tags']['id'] = 'field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['table'] = 'field_data_field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['field'] = 'field_informea_tags';
  $handler->display->display_options['fields']['field_informea_tags']['label'] = '';
  $handler->display->display_options['fields']['field_informea_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_informea_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_informea_tags']['settings'] = array(
    'links_option' => 0,
    'separator_option' => ', ',
    'element_option' => '- None -',
    'element_class' => '',
    'wrapper_option' => '- None -',
    'wrapper_class' => '',
  );
  $handler->display->display_options['fields']['field_informea_tags']['delta_offset'] = '0';
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: Online course */
  $handler->display->display_options['fields']['field_online_course_link']['id'] = 'field_online_course_link';
  $handler->display->display_options['fields']['field_online_course_link']['table'] = 'field_data_field_online_course_link';
  $handler->display->display_options['fields']['field_online_course_link']['field'] = 'field_online_course_link';
  $handler->display->display_options['fields']['field_online_course_link']['label'] = '';
  $handler->display->display_options['fields']['field_online_course_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_online_course_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_online_course_link']['type'] = 'link_absolute';
  /* Field: Content: UN Treaty database link */
  $handler->display->display_options['fields']['field_un_treaty_database_link']['id'] = 'field_un_treaty_database_link';
  $handler->display->display_options['fields']['field_un_treaty_database_link']['table'] = 'field_data_field_un_treaty_database_link';
  $handler->display->display_options['fields']['field_un_treaty_database_link']['field'] = 'field_un_treaty_database_link';
  $handler->display->display_options['fields']['field_un_treaty_database_link']['label'] = '';
  $handler->display->display_options['fields']['field_un_treaty_database_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_un_treaty_database_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_un_treaty_database_link']['type'] = 'link_absolute';
  /* Field: Content: Treaty website URL */
  $handler->display->display_options['fields']['field_treaty_website_url']['id'] = 'field_treaty_website_url';
  $handler->display->display_options['fields']['field_treaty_website_url']['table'] = 'field_data_field_treaty_website_url';
  $handler->display->display_options['fields']['field_treaty_website_url']['field'] = 'field_treaty_website_url';
  $handler->display->display_options['fields']['field_treaty_website_url']['label'] = '';
  $handler->display->display_options['fields']['field_treaty_website_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty_website_url']['click_sort_column'] = 'url';
  /* Field: Content: Treaty text URL */
  $handler->display->display_options['fields']['field_treaty_text_url']['id'] = 'field_treaty_text_url';
  $handler->display->display_options['fields']['field_treaty_text_url']['table'] = 'field_data_field_treaty_text_url';
  $handler->display->display_options['fields']['field_treaty_text_url']['field'] = 'field_treaty_text_url';
  $handler->display->display_options['fields']['field_treaty_text_url']['label'] = '';
  $handler->display->display_options['fields']['field_treaty_text_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty_text_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_treaty_text_url']['type'] = 'link_absolute';
  /* Field: Content: Treaty parties URL */
  $handler->display->display_options['fields']['field_treaty_parties_url']['id'] = 'field_treaty_parties_url';
  $handler->display->display_options['fields']['field_treaty_parties_url']['table'] = 'field_data_field_treaty_parties_url';
  $handler->display->display_options['fields']['field_treaty_parties_url']['field'] = 'field_treaty_parties_url';
  $handler->display->display_options['fields']['field_treaty_parties_url']['label'] = '';
  $handler->display->display_options['fields']['field_treaty_parties_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty_parties_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_treaty_parties_url']['type'] = 'link_absolute';
  /* Field: Content: Ratification XML URL */
  $handler->display->display_options['fields']['field_ratification_xml_url']['id'] = 'field_ratification_xml_url';
  $handler->display->display_options['fields']['field_ratification_xml_url']['table'] = 'field_data_field_ratification_xml_url';
  $handler->display->display_options['fields']['field_ratification_xml_url']['field'] = 'field_ratification_xml_url';
  $handler->display->display_options['fields']['field_ratification_xml_url']['label'] = '';
  $handler->display->display_options['fields']['field_ratification_xml_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ratification_xml_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_ratification_xml_url']['type'] = 'link_absolute';
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

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'treaties');
  $handler->display->display_options['path'] = 'treaties';
  $translatables['list_of_all_treaties'] = array(
    t('Master'),
    t('List of all treaties'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('description'),
    t('Services'),
  );
  $export['list_of_all_treaties'] = $view;

  $view = new view();
  $view->name = 'mea_contextual_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'MEA Contextual Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '7';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['event_calendar_date']['id'] = 'event_calendar_date';
  $handler->display->display_options['fields']['event_calendar_date']['table'] = 'field_data_event_calendar_date';
  $handler->display->display_options['fields']['event_calendar_date']['field'] = 'event_calendar_date';
  $handler->display->display_options['fields']['event_calendar_date']['label'] = '';
  $handler->display->display_options['fields']['event_calendar_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['event_calendar_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['text'] = '[event_calendar_date] - [title]';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '80';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Date -  start date (event_calendar_date) */
  $handler->display->display_options['sorts']['event_calendar_date_value']['id'] = 'event_calendar_date_value';
  $handler->display->display_options['sorts']['event_calendar_date_value']['table'] = 'field_data_event_calendar_date';
  $handler->display->display_options['sorts']['event_calendar_date_value']['field'] = 'event_calendar_date_value';
  /* Contextual filter: Content: Treaty (field_treaty) */
  $handler->display->display_options['arguments']['field_treaty_target_id']['id'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['arguments']['field_treaty_target_id']['field'] = 'field_treaty_target_id';
  $handler->display->display_options['arguments']['field_treaty_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_treaty_target_id']['default_argument_type'] = 'node';
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
    'event_calendar' => 'event_calendar',
  );
  /* Filter criterion: Content: Date -  start date (event_calendar_date) */
  $handler->display->display_options['filters']['event_calendar_date_value']['id'] = 'event_calendar_date_value';
  $handler->display->display_options['filters']['event_calendar_date_value']['table'] = 'field_data_event_calendar_date';
  $handler->display->display_options['filters']['event_calendar_date_value']['field'] = 'event_calendar_date_value';
  $handler->display->display_options['filters']['event_calendar_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['event_calendar_date_value']['default_date'] = 'now';

  /* Display: Upcoming MEA contextual events */
  $handler = $view->new_display('block', 'Upcoming MEA contextual events', 'block');
  $handler->display->display_options['display_description'] = 'Shown in MEA treaty page';
  $translatables['mea_contextual_events'] = array(
    t('Master'),
    t('Upcoming events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('[event_calendar_date] - [title]'),
    t('All'),
    t('Upcoming MEA contextual events'),
    t('Shown in MEA treaty page'),
  );
  $export['mea_contextual_events'] = $view;

  $view = new view();
  $view->name = 'news';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_news_search_index';
  $view->human_name = 'News';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'News';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'media';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'media-list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Indexed Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'logo',
    'image_link' => '',
  );
  /* Field: Indexed Content: URL */
  $handler->display->display_options['fields']['field_url']['id'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_url']['field'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['label'] = '';
  $handler->display->display_options['fields']['field_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_url']['type'] = 'link_absolute';
  /* Field: Indexed Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<a href="[field_url]" target="blank">[title]</a>';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Indexed Content: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Content: Tags */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['list']['mode'] = 'list';
  $handler->display->display_options['fields']['field_tags']['list']['separator'] = '';
  $handler->display->display_options['fields']['field_tags']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_tags']['bypass_access'] = 0;
  /* Field: Indexed Content: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  $handler->display->display_options['fields']['created']['link_to_entity'] = 0;
  /* Field: Indexed Content: MEA topic */
  $handler->display->display_options['fields']['field_mea_topic']['id'] = 'field_mea_topic';
  $handler->display->display_options['fields']['field_mea_topic']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_mea_topic']['field'] = 'field_mea_topic';
  $handler->display->display_options['fields']['field_mea_topic']['label'] = '';
  $handler->display->display_options['fields']['field_mea_topic']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_mea_topic']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_mea_topic']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_mea_topic']['bypass_access'] = 0;
  /* Field: Indexed Content: Treaty */
  $handler->display->display_options['fields']['field_treaty']['id'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_treaty']['field'] = 'field_treaty';
  $handler->display->display_options['fields']['field_treaty']['label'] = '';
  $handler->display->display_options['fields']['field_treaty']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treaty']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_treaty']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_treaty']['bypass_access'] = 0;
  /* Sort criterion: Indexed Content: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search in news';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Indexed Content: MEA topic */
  $handler->display->display_options['filters']['field_mea_topic']['id'] = 'field_mea_topic';
  $handler->display->display_options['filters']['field_mea_topic']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['filters']['field_mea_topic']['field'] = 'field_mea_topic';
  $handler->display->display_options['filters']['field_mea_topic']['value'] = array();
  $handler->display->display_options['filters']['field_mea_topic']['group'] = 1;
  $handler->display->display_options['filters']['field_mea_topic']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_mea_topic']['expose']['operator_id'] = 'field_mea_topic_op';
  $handler->display->display_options['filters']['field_mea_topic']['expose']['label'] = 'Show';
  $handler->display->display_options['filters']['field_mea_topic']['expose']['operator'] = 'field_mea_topic_op';
  $handler->display->display_options['filters']['field_mea_topic']['expose']['identifier'] = 'field_mea_topic';
  $handler->display->display_options['filters']['field_mea_topic']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_mea_topic']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Content: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'feed_item' => 'feed_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'news';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'field_url';
  $handler->display->display_options['row_options']['description_field'] = 'field_feed_item_description';
  $handler->display->display_options['row_options']['creator_field'] = 'field_parent_feed';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'nid',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Indexed Content: URL */
  $handler->display->display_options['fields']['field_url']['id'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_url']['field'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['label'] = '';
  $handler->display->display_options['fields']['field_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_url']['type'] = 'link_absolute';
  /* Field: Indexed Content: Description */
  $handler->display->display_options['fields']['field_feed_item_description']['id'] = 'field_feed_item_description';
  $handler->display->display_options['fields']['field_feed_item_description']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_feed_item_description']['field'] = 'field_feed_item_description';
  $handler->display->display_options['fields']['field_feed_item_description']['label'] = '';
  $handler->display->display_options['fields']['field_feed_item_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_feed_item_description']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_feed_item_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Indexed Content: Parent feed */
  $handler->display->display_options['fields']['field_parent_feed']['id'] = 'field_parent_feed';
  $handler->display->display_options['fields']['field_parent_feed']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['field_parent_feed']['field'] = 'field_parent_feed';
  $handler->display->display_options['fields']['field_parent_feed']['label'] = '';
  $handler->display->display_options['fields']['field_parent_feed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_parent_feed']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_parent_feed']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_parent_feed']['bypass_access'] = 0;
  /* Field: Indexed Content: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  $handler->display->display_options['fields']['created']['link_to_entity'] = 0;
  /* Field: Indexed Content: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Content: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_news_search_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'feed_item' => 'feed_item',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'news/rss';
  $translatables['news'] = array(
    t('Master'),
    t('News'),
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
    t('<a href="[field_url]" target="blank">[title]</a>'),
    t('.'),
    t(','),
    t('Tags'),
    t('Search in news'),
    t('Show'),
    t('Page'),
    t('Feed'),
  );
  $export['news'] = $view;

  $view = new view();
  $view->name = 'taxonomy_mappings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Taxonomy mappings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Glossary mappings';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access content overview';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'tid' => 'tid',
    'name' => 'name',
    'edit_term' => 'edit_term',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'tid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_term' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'ID';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Field: Keyword(s) */
  $handler->display->display_options['fields']['field_keywords']['id'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['fields']['field_keywords']['field'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['label'] = 'ECOLEX keywords';
  $handler->display->display_options['fields']['field_keywords']['delta_offset'] = '0';
  /* Field: Taxonomy term: ECOLEX terms */
  $handler->display->display_options['fields']['field_thesaurus_map_ecolex']['id'] = 'field_thesaurus_map_ecolex';
  $handler->display->display_options['fields']['field_thesaurus_map_ecolex']['table'] = 'field_data_field_thesaurus_map_ecolex';
  $handler->display->display_options['fields']['field_thesaurus_map_ecolex']['field'] = 'field_thesaurus_map_ecolex';
  $handler->display->display_options['fields']['field_thesaurus_map_ecolex']['label'] = 'ECOLEX subjects';
  $handler->display->display_options['fields']['field_thesaurus_map_ecolex']['delta_offset'] = '0';
  /* Field: Taxonomy term: Term edit link */
  $handler->display->display_options['fields']['edit_term']['id'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['edit_term']['field'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['label'] = 'Operations';
  /* Sort criterion: Taxonomy term: Name (name_field) */
  $handler->display->display_options['sorts']['name_field_value']['id'] = 'name_field_value';
  $handler->display->display_options['sorts']['name_field_value']['table'] = 'field_data_name_field';
  $handler->display->display_options['sorts']['name_field_value']['field'] = 'name_field_value';
  $handler->display->display_options['sorts']['name_field_value']['expose']['label'] = 'Term';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'thesaurus_informea' => 'thesaurus_informea',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/informea-taxonomy-mappings';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'InforMEA Thesaurus';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['taxonomy_mappings'] = array(
    t('Master'),
    t('Glossary mappings'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('ID'),
    t('.'),
    t(','),
    t('Name'),
    t('ECOLEX keywords'),
    t('ECOLEX subjects'),
    t('Operations'),
    t('Term'),
    t('Page'),
  );
  $export['taxonomy_mappings'] = $view;

  $view = new view();
  $view->name = 'term_related_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Term related content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Term related content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/term-related-content';
  $translatables['term_related_content'] = array(
    t('Master'),
    t('Term related content'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Title'),
    t('All'),
    t('Page'),
  );
  $export['term_related_content'] = $view;

  $view = new view();
  $view->name = 'the_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'The Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Browse Content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access content overview';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 250';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'type' => 'type',
    'language' => 'language',
    'changed' => 'changed',
    'name' => 'name',
    'edit_node' => 'edit_node',
    'delete_node' => 'delete_node',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'language' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no results for your filtering';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = 'Bulk';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Data source */
  $handler->display->display_options['fields']['field_data_source']['id'] = 'field_data_source';
  $handler->display->display_options['fields']['field_data_source']['table'] = 'field_data_field_data_source';
  $handler->display->display_options['fields']['field_data_source']['field'] = 'field_data_source';
  $handler->display->display_options['fields']['field_data_source']['delta_offset'] = '0';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'medium';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'node';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[edit_node]
[delete_node]';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['description'] = 'Enter few words from the title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: User: Name (raw) */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'users';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'uid';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Author name';
  $handler->display->display_options['filters']['name']['expose']['description'] = 'Enter few letters from author name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Content type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filter criterion: Content: Data source (field_data_source) */
  $handler->display->display_options['filters']['field_data_source_tid']['id'] = 'field_data_source_tid';
  $handler->display->display_options['filters']['field_data_source_tid']['table'] = 'field_data_field_data_source';
  $handler->display->display_options['filters']['field_data_source_tid']['field'] = 'field_data_source_tid';
  $handler->display->display_options['filters']['field_data_source_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_data_source_tid']['expose']['operator_id'] = 'field_data_source_tid_op';
  $handler->display->display_options['filters']['field_data_source_tid']['expose']['label'] = 'Data source';
  $handler->display->display_options['filters']['field_data_source_tid']['expose']['operator'] = 'field_data_source_tid_op';
  $handler->display->display_options['filters']['field_data_source_tid']['expose']['identifier'] = 'field_data_source_tid';
  $handler->display->display_options['filters']['field_data_source_tid']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  $handler->display->display_options['filters']['field_data_source_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_data_source_tid']['vocabulary'] = 'data_source';
  /* Filter criterion: Content: Treaty (field_treaty) */
  $handler->display->display_options['filters']['field_treaty_target_id']['id'] = 'field_treaty_target_id';
  $handler->display->display_options['filters']['field_treaty_target_id']['table'] = 'field_data_field_treaty';
  $handler->display->display_options['filters']['field_treaty_target_id']['field'] = 'field_treaty_target_id';
  $handler->display->display_options['filters']['field_treaty_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_treaty_target_id']['expose']['operator_id'] = 'field_treaty_target_id_op';
  $handler->display->display_options['filters']['field_treaty_target_id']['expose']['label'] = 'Treaty';
  $handler->display->display_options['filters']['field_treaty_target_id']['expose']['operator'] = 'field_treaty_target_id_op';
  $handler->display->display_options['filters']['field_treaty_target_id']['expose']['identifier'] = 'field_treaty_target_id';
  $handler->display->display_options['filters']['field_treaty_target_id']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content';
  $translatables['the_content'] = array(
    t('Master'),
    t('Browse Content'),
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
    t('Displaying @start - @end of @total'),
    t('There are no results for your filtering'),
    t('author'),
    t('Bulk'),
    t('- Choose an operation -'),
    t('Title'),
    t('Type'),
    t('Data source'),
    t('Author'),
    t('Status'),
    t('Updated'),
    t('Language'),
    t('Edit link'),
    t('Delete link'),
    t('Operations'),
    t('[edit_node]
[delete_node]'),
    t('Enter few words from the title'),
    t('Published'),
    t('Author name'),
    t('Enter few letters from author name'),
    t('Content type'),
    t('Treaty'),
    t('Page'),
  );
  $export['the_content'] = $view;

  return $export;
}
