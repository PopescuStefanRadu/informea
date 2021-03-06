<?php
/**
 * @file
 * thesaurus.drush.inc
 */

/**
 * Implements hook_drush_command().
 */
function thesaurus_drush_command() {
  $items = array();

  $items['informea-thesaurus-sync'] = array(
    'drupal dependencies' => array('easyrdf'),
    'description' => 'Updates InforMEA thesaurus.',
    'aliases' => array('imea-tu')
  );

  $items['informea-thesaurus-migrate-tags'] = array(
    'drupal dependencies' => array('easyrdf', 'phpexcel'),
    'description' => 'Migrate terms from vocbench and fix field_informea_tags.',
  );

  $items['informea-thesaurus-correct-path-alias'] = array(
    'description' => 'Updates path alias for terms in Thesaurus Informea vocabulary.',
    'aliases' => array('imea-tcpa')
  );

  return $items;
}

function drush_thesaurus_informea_thesaurus_sync() {
  thesaurus_informea_sync_vocbench();
  echo "Synchronisation finished ...\n";
}

function drush_thesaurus_informea_thesaurus_migrate_tags() {
  module_load_include('inc', 'phpexcel');

  $path = drupal_get_path('module', 'thesaurus') . '/data/informea-old-new-mappings.xlsx';

  $data = phpexcel_import($path)[0];

  if (!is_array($data)) {
    drush_log("We could not get the data from the excel file.", 'error');
    return;
  }
  $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');

  /*
   * STEP 1: Delete all terms.
   */
  drush_log("Deleting all old terms", "ok");
  foreach (taxonomy_get_tree($voc->vid) as $term) {
    drush_log("Deleting term: " . $term->name, "ok");
    taxonomy_term_delete($term->tid);
  }

  /*
   * STEP 2: Synchronization with vocbench
   */
  drush_thesaurus_informea_thesaurus_sync();

  /*
   * STEP 3: Delete actual tags
   */
  drush_log("Deleting old tags", "ok");
  // Create backup
  db_query('CREATE TABLE IF NOT EXISTS field_data_field_informea_tags_backup AS SELECT * FROM field_data_field_informea_tags');

  // Delete old data
  db_truncate('field_data_field_informea_tags')->execute();
  db_truncate('field_revision_field_informea_tags')->execute();

  /*
   * STEP 4: Add new tags
   */
  $uris_not_found_count = 0;
  foreach ($data as $row) {
    $old_term_name = $row['OLD TERM (INFORMEA.ORG/TERMS)'];
    if ($old_term_name) {
      drush_log("Remapping old term: " . $old_term_name, "ok");
      $q = db_select('thesaurus_term_mappings', 'a');
      $q->innerJoin('node', 'b', 'a.entity_id = b.nid');
      $q->fields('a', array('entity_id'));
      $q->fields('b', array('type'));
      $q->condition('a.name', $old_term_name);
      $entities_ids = $q->execute()->fetchAllKeyed();

      $new_tids = array();
      for ($i = 1 ; $i < 7 ; $i++) {
        if($row[$i]) {
          $new_tid = thesaurus_term_get_tid_by_uri($row[$i], 'thesaurus_informea');
          if ($new_tid != NULL) {
            $new_tids[] = $new_tid;
          }
          else {
            drush_log("Could not find term by uri: " . $row[$i], 'error');
            $uris_not_found_count++;
          }
        }
      }

      foreach ($entities_ids as $eid => $node_type) {
        foreach ($new_tids as $tid) {
          $q = db_select('field_data_field_informea_tags', 'a');
          $q->fields('a', array('entity_id'));
          $q->condition('a.entity_id', $eid);
          $q->condition('a.field_informea_tags_tid', $tid);
          $res = $q->execute()->fetchAll();
          if (count($res) > 0) {
            // Do not add duplicates.
            continue;
          }

          db_query("
INSERT INTO field_data_field_informea_tags (entity_type, bundle, deleted, entity_id, revision_id, language, delta, field_informea_tags_tid)
VALUES ('node', :bundle, '0', :entity_id, :entity_id, 'und', IFNULL((SELECT MAX(delta)+1 as delta from field_data_field_informea_tags b where b.entity_id = :entity_id), 0), :term_id);
        ",
            array(
              ':bundle' => $node_type,
              ':entity_id' => $eid,
              ':term_id' => $tid,
            ));
        }
      }
    }
  }
  if ($uris_not_found_count) {
    drush_log($uris_not_found_count . " uris not found.", 'warning');
  }
  else {
  drush_log("Operation completed 100% succesfully!", 'ok');
  }
}

function drush_thesaurus_informea_thesaurus_correct_path_alias() {
  $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');
  $terms = taxonomy_get_tree($voc->vid);
  $count = 0;
  foreach ($terms as $term) {
    $term = taxonomy_term_load($term->tid);
    $url = $term->field_taxonomy_term_uri[LANGUAGE_NONE][0]['url'];
    $path_alias = str_replace('http://www.informea.org/', '', $url);
    $old_alias = reset(db_select('url_alias')
      ->fields(NULL, array('alias'))
      ->condition('source', 'taxonomy/term/' . $term->tid)
      ->execute()->fetchCol());
    if (!empty($path_alias) && $old_alias != $path_alias) {
      // We need to redirect the old alias to the new one
      $redirect = new stdClass();
      redirect_object_prepare(
        $redirect,
        array(
          'source' => $old_alias,
          'source_options' => array(),
          'redirect' => $path_alias,
          'redirect_options' => array(),
          'language' => LANGUAGE_NONE,
        )
      );
      redirect_save($redirect);

      db_update('url_alias')
        ->fields(array('alias' => $path_alias))
        ->condition('source', 'taxonomy/term/' . $term->tid)
        ->execute();
      drush_log("Path alias changed for term: \"{$term->name}\". OLD: {$old_alias} | NEW: {$path_alias}", 'ok');
      $count ++;
    }
  }
  drush_log(dt('Succesfully updated path alias for @n terms.', array('@n' => $count)), 'ok');
}