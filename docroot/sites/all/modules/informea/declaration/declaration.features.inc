<?php
/**
 * @file
 * declaration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function declaration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function declaration_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function declaration_node_info() {
  $items = array(
    'declaration' => array(
      'name' => t('Declaration'),
      'base' => 'node_content',
      'description' => t('This content keeps Declarations and Principles related to Goals. They are break-down in Articles and Paragraphs'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'declaration_paragraph' => array(
      'name' => t('Declaration paragraph'),
      'base' => 'node_content',
      'description' => t('This is a break-down paragraph of an declaration section text'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'declaration_section' => array(
      'name' => t('Declaration Section'),
      'base' => 'node_content',
      'description' => t('This is a section or sub-section of a declaration'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
