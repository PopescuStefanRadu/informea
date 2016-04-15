<?php

/**
 * Common mappings for the Drupal 7 node migrations.
 */
class LeoDefaultNodeMigration extends DrupalNode7Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('title', 'title', FALSE);

    foreach ($this->taxonomyFields() as $field => $vocabulary) {
      $this->addFieldMapping("{$field}:source_type")
        ->defaultValue('tid');
      $this->addFieldMapping("{$field}:create_term")
        ->defaultValue(FALSE);
      $this->addFieldMapping("{$field}:ignore_case")
        ->defaultValue(FALSE);
    }
  }

  /**
   * @return array
   *  An associative array. Keys are fields names and values are vocabulary names.
   */
  protected function taxonomyFields() {
    return array();
  }

  public function map_source_term($source_tid, $taxonomy) {
    $mappings = array();
    $voc = taxonomy_vocabulary_machine_name_load($taxonomy);

    $q = db_select('taxonomy_term_data', 't')->fields('t');
    $rows = $q->execute()->fetchAllAssoc('tid');
    foreach($rows as $term) {
      $mappings[$term->vid][strtolower($term->name)] = $term->tid;
    }

    $query = Database::getConnection('default', $this->sourceConnection)
      ->select('taxonomy_term_data', 't')
      ->fields('t', array('name'))
      ->condition('tid', $source_tid);

    $source_english = $query->execute()->fetchField();

    if (!empty($mappings[$voc->vid][strtolower($source_english)])) {
      return $mappings[$voc->vid][strtolower($source_english)];
    }

    return NULL;
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    foreach ($this->taxonomyFields() as $field => $vocabulary) {
      if (!empty($row->{$field})) {
        foreach ($row->{$field} as $key => $value) {
          $row->{$field}[$key] = $this->map_source_term($value, $vocabulary);
        }
      }
    }
  }
}
