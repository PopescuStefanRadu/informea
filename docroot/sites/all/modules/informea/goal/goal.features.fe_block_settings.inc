<?php
/**
 * @file
 * goal.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function goal_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-goals_disclaimer'] = array(
    'cache' => -1,
    'custom' => 0,
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'machine_name' => 'goals_disclaimer',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'goals',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -28,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  return $export;
}
