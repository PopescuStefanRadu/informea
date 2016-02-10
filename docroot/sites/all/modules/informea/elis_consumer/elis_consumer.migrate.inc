<?php

/**
 * Implements hook_migrate_api().
 */
function elis_consumer_migrate_api() {

  $return = array(
    'api' => 2,
    'groups' => array(
      'elis_consumer' => array(
        'title' => t('Migrations from ELIS'),
      ),
    ),
    'migrations' => array(
      'elis_treaties' => array(
        'class_name' => 'TreatyElisMigration',
        'group_name' => 'elis_consumer',
      ),
    ),
  );

  return $return;

}