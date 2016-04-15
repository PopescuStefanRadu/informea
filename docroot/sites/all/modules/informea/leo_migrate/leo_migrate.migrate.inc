<?php

/**
 * Implements hook_migrate_api().
 */
function leo_migrate_migrate_api() {
  /**
   * Declare the api version and migration group.
   */
  $api = array(
    'api' => 2,
    'groups' => array(
      'leo_migrate' => array(
        'title' => t('Migrations from LEO website'),
      ),
      'migrations' => array(),
    ),
  );

  $common_arguments = array(
    'source_connection' => 'legacy',
    'source_database' => Database::getConnection('default', 'leo_informea')->getConnectionOptions(),
    'source_version' => 7,
    'group_name' => 'leo_migrate',
  );

  $vocabulary_arguments = array(
    'type_of_goal' => array(
      'description' => t('Migration of \'Type of goal\' terms from LEO.'),
      'source_vocabulary' => 'type_of_goal',
      'destination_vocabulary' => 'type_of_goal',
      'class_name' => 'LeoDefaultTaxonomyMigration',
    ),
    'goal_sources' => array(
      'description' => t('Migration of \'Goal sources\' terms from LEO.'),
      'source_vocabulary' => 'goal_sources',
      'destination_vocabulary' => 'goal_sources',
      'class_name' => 'LeoGoalSourcesMigration',
    ),
    'geg_theme' => array(
      'description' => t('Migration of \'GEG theme\' terms from LEO'),
      'source_vocabulary' => 'geg_theme',
      'destination_vocabulary' => 'geg_theme',
      'class_name' => 'LeoDefaultTaxonomyMigration',
    ),
    'territorial_subdivision' => array(
      'description' => t('Migration of \'Territorial subdivision\' terms from LEO'),
      'source_vocabulary' => 'territorial_subdivision',
      'destination_vocabulary' => 'territorial_subdivision',
      'class_name' => 'LeoDefaultTaxonomyMigration',
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
    ),
    'type_of_text' => array(
      'description' => t('Migration of \'Type of text\' terms from LEO'),
      'source_vocabulary' => 'type_of_text',
      'destination_vocabulary' => 'type_of_text',
      'class_name' => 'LeoDefaultTaxonomyMigration',
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
    ),
    'keywords' => array(
      'description' => t('Migration of \'Keywords\' terms from LEO'),
      'source_vocabulary' => 'keywords',
      'destination_vocabulary' => 'keywords',
      'class_name' => 'LeoDefaultTaxonomyMigration',
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
    ),
  );

  foreach ($vocabulary_arguments as $migration_name => $arguments) {
    $arguments += $common_arguments;
    $api['migrations'][$migration_name] = $arguments;
  }

  $node_arguments = array(
    'goal' => array(
      'class_name' => 'LeoGoalMigration',
      'description' => t('Migration of goals nodes from LEO.'),
      'source_type' => 'goal',
      'destination_type' => 'goal',
      'dependencies' => array('type_of_goal', 'goal_sources', 'geg_theme'),
    ),
  );

  foreach ($node_arguments as $migration_name => $arguments) {
    $arguments = array_merge_recursive($arguments, $common_arguments);
    $api['migrations'][$migration_name] = $arguments;
  }

  return $api;
}