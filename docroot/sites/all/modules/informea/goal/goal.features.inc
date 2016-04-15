<?php
/**
 * @file
 * goal.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function goal_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function goal_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function goal_node_info() {
  $items = array(
    'goal' => array(
      'name' => t('Goal'),
      'base' => 'node_content',
      'description' => t('Different type of goals (IEG, GEG etc.)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
