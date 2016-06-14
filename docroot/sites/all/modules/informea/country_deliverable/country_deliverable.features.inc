<?php
/**
 * @file
 * country_deliverable.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function country_deliverable_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function country_deliverable_node_info() {
  $items = array(
    'action_plan' => array(
      'name' => t('Action Plan'),
      'base' => 'node_content',
      'description' => t('Action plans'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'national_report' => array(
      'name' => t('National Report'),
      'base' => 'node_content',
      'description' => t('National reports delivered by the MEA parties'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'national_report_paragraph' => array(
      'name' => t('National Report paragraph'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'reporting_obligation_cycle' => array(
      'name' => t('Reporting Obligation Cycle'),
      'base' => 'node_content',
      'description' => t('Country reporting obligation for national reports'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
