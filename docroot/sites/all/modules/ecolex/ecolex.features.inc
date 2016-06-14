<?php
/**
 * @file
 * ecolex.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ecolex_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ecolex_node_info() {
  $items = array(
    'court_decisions' => array(
      'name' => t('Court decisions'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'legislation' => array(
      'name' => t('Legislation'),
      'base' => 'node_content',
      'description' => t('ECOLEX legislation'),
      'has_title' => '1',
      'title_label' => t('Title of text'),
      'help' => '',
    ),
    'literature' => array(
      'name' => t('Literature'),
      'base' => 'node_content',
      'description' => t('Publications'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
