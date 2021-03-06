<?php
/**
 * @file
 * informea_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function informea_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['facetapi-C0KfOYe1CTJW1tlSyl3brJVVT4qQLzy0'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'C0KfOYe1CTJW1tlSyl3brJVVT4qQLzy0',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -19,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Instrument',
    'visibility' => 0,
  );

  $export['facetapi-EeqfYRvf4OeayxrDPBXmxh0uLs695r1S'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'EeqfYRvf4OeayxrDPBXmxh0uLs695r1S',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
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
    'title' => 'Geographical region',
    'visibility' => 0,
  );

  $export['facetapi-I6RVf55CR0muKADP1zTBRoXexXDd7LN4'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'I6RVf55CR0muKADP1zTBRoXexXDd7LN4',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -16,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Keywords',
    'visibility' => 0,
  );

  $export['facetapi-qTurWYUYYufA4n4p1OFoxmFTW0m9G81J'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'qTurWYUYYufA4n4p1OFoxmFTW0m9G81J',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -17,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Country',
    'visibility' => 0,
  );

  $export['facetapi-rm0orTI2PzmJnpZ1x07XLj097DSEjQQJ'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'rm0orTI2PzmJnpZ1x07XLj097DSEjQQJ',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'informea_theme' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'informea_theme',
        'weight' => -20,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Type',
    'visibility' => 0,
  );

  return $export;
}
