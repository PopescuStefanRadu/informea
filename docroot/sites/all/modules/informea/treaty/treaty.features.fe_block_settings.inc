<?php
/**
 * @file
 * treaty.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function treaty_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-treaty_listing_page-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'treaty_listing_page-block',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'treaty-listing-page',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -18,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
