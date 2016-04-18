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
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
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
    'thesaurus_ecolex' => array(
      'description' => t('Migration of ECOLEX Thesaurus from LEO'),
      'source_vocabulary' => 'thesaurus_ecolex',
      'destination_vocabulary' => 'thesaurus_ecolex',
      'class_name' => 'LeoDefaultTaxonomyMigration',
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
    ),
    'data_source' => array(
      'description' => t('Migration of Data sources from LEO'),
      'source_vocabulary' => 'data_source',
      'destination_vocabulary' => 'data_source',
      'class_name' => 'LeoDefaultTaxonomyMigration',
      'translatable_name' => TRUE,
      'translatable_description' => TRUE,
    ),
    'declaration_paragraph_type' => array(
      'description' => t('Migration of \'Declaration paragraph type\' terms from LEO'),
      'source_vocabulary' => 'declaration_paragraph_type',
      'destination_vocabulary' => 'declaration_paragraph_type',
      'class_name' => 'LeoDefaultTaxonomyMigration',
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
    'legislation' => array(
      'class_name' => 'LeoLegislationMigration',
      'description' => t('Migration of legislation nodes from LEO.'),
      'source_type' => 'legislation',
      'destination_type' => 'legislation',
      'dependencies' => array('territorial_subdivision', 'type_of_text', 'keywords', 'thesaurus_ecolex', 'data_source', 'legislation_files'),
    ),
    'declaration' => array(
      'class_name' => 'LeoDeclarationMigration',
      'description' => t('Migration of declaration nodes from LEO.'),
      'source_type' => 'declaration',
      'destination_type' => 'declaration',
    ),
    'declaration_section' => array(
      'class_name' => 'LeoDeclarationSectionMigration',
      'description' => t('Migration of declaration section nodes from LEO.'),
      'source_type' => 'declaration_section',
      'destination_type' => 'declaration_section',
      'dependencies' => array('declaration'),
    ),
    'declaration_paragraph' => array(
      'class_name' => 'LeoDeclarationParagraphMigration',
      'description' => t('Migration of declaration paragraph nodes from LEO.'),
      'source_type' => 'declaration_paragraph',
      'destination_type' => 'declaration_paragraph',
      'dependencies' => array('declaration', 'declaration_section', 'declaration_paragraph_type'),
    ),
  );

  foreach ($node_arguments as $migration_name => $arguments) {
    $arguments = array_merge_recursive($arguments, $common_arguments);
    $api['migrations'][$migration_name] = $arguments;
  }

  $file_arguments = array(
    'legislation_files' => array(
      'class_name' => 'LeoLegislationFilesMigration',
      'description' => t('Import legislation files from LEO.'),
      'default_uid' => 1,
      'source_dir' => 'http://leo.informea.org/sites/default/files',
    ),
  );

  foreach ($file_arguments as $migration_name => $arguments) {
    $arguments += $common_arguments;
    $api['migrations'][$migration_name] = $arguments;
  }
  
  return $api;
}
