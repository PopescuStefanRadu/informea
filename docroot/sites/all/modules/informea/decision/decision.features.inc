<?php
/**
 * @file
 * decision.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function decision_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function decision_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function decision_node_info() {
  $items = array(
    'decision' => array(
      'name' => t('Decision'),
      'base' => 'node_content',
      'description' => t('MEA decision'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'decision_paragraph' => array(
      'name' => t('Decision Paragraph'),
      'base' => 'node_content',
      'description' => t('Paragraph extracted from a decison'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
