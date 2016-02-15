<?php

abstract class AbstractElisMigration extends Migration {

  protected $translatable_fields = array();
  protected $taxonomy_term_fields = array();

  public function getTranslationLanguages($row) {
    $translate_in = array();
    foreach ($this->translatable_fields as $field_name) {
      if (property_exists($row, $field_name . '_languages')) {
        $translate_in = array_merge($translate_in, $row->{$field_name . '_languages'});
      }
    }
    return array_unique($translate_in);
  }

  public function translate_entity($entity_type, $entity, $translations = array()) {
    if (empty($translations)) {
      return;
    }
    $languages   = array_keys(language_list());
    $translation_handler  = entity_translation_get_handler($entity_type, $entity);
    $translation_handler->setOriginalLanguage('en');
    $translation_handler->initTranslations();
    $entity->translations = $translation_handler->getTranslations();
    foreach ($languages as $language) {
      if ($language == 'en') {
        continue;
      }
      if (in_array($language, $translations)) {
        $translation_handler->setTranslation(array(
          'translate' => 0, 'status' => 1, 'uid' => 1,
          'language' => $language,
          'source' => 'en',
        ));
      }
    }
  }

  public function setTranslation($entity, $translations = array()) {
    $migration   = Migration::currentMigration();
    $entity_type = $migration->getDestination()->getEntityType();
    $this->translate_entity($entity_type, $entity, $translations);
  }

  function prepare($entity, $row) {
    $translate_in = $this->getTranslationLanguages($row);
    $this->setTranslation($entity, $translate_in);
  }

  public function fix_link_field_multilingual_data(&$entity, $field_name, $field_values, $field_translations, $value_index) {
    foreach ($field_translations as $key => $lang) {
      $val = $field_values[$key];
      $entity->{$field_name}[$lang] = array();
      if (is_array($val)) {
        foreach ($val as $value) {
          $entity->{$field_name}[$lang][] = array($value_index => $value);
        }
      }
      else {
        $entity->{$field_name}[$lang][] = array($value_index => $val);
      }
    }
  }

  public function get_taxonomy_term_tid($name, $vocabulary = NULL) {
    $term = taxonomy_get_term_by_name($name, $vocabulary);
    return empty($term) ? NULL : reset($term)->tid;
  }

  public function create_taxonomy_term($name, $vocabulary_machine_name, $name_translations = array(), $multilingual_name_field = 'name_field') {
    $voc = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);
    $term = new stdClass();
    $term->name = $name;
    $term->vid = $voc->vid;
    if (!empty($name_translations)) {
      $term->{$multilingual_name_field} = array();
      foreach ($name_translations as $lang => $value) {
        $term->{$multilingual_name_field}[$lang][0]['value'] = $value;
      }
    }
    taxonomy_term_save($term);
    $this->translate_entity('taxonomy_term', $term, array_keys($name_translations));
    return $term->tid;
  }

  public function get_terms_from_source_field($row, $field_name) {
    $data = array();
    if (!property_exists($row, $field_name)) {
      return $data;
    }
    $row->{$field_name} = !is_array($row->{$field_name}) ? array($row->{$field_name}) : $row->{$field_name};
    foreach($row->{$field_name} as $term_key => $term) {
      $term_translations = array();
      if (!empty($row->{$field_name . '_translations'})) {
        $row->{$field_name . '_translations'} = !is_array($row->{$field_name}) ? array($row->{$field_name . '_translations'}) : $row->{$field_name . '_translations'};
        $row->{$field_name . '_languages'} = !is_array($row->{$field_name}) ? array($row->{$field_name . '_languages'}) : $row->{$field_name . '_languages'};
        foreach ($row->{$field_name . '_languages'} as $lang_key => $lang) {
          $term_translations[$lang] = $row->{$field_name . '_translations'}[$lang_key][$term_key];
        }
      }
      $data[$term_key] = array(
        'name' => htmlspecialchars_decode($term),
        'translations' => $term_translations,
      );
    }
    return $data;
  }

  /**
   * Map the term names with the existing terms tids.
   * If the vocabulary doesn't contain a term with that name, it will be created.
   *
   * @param $row
   *  Current migration row.
   * @param $field_name
   *  Name of the source field.
   * @param $data
   *  An array containing the terms. Each item needs to be an associative array
   * containing:
   *  - name: original term name
   *  - translations: an array containing language => translation pairs.
   * @param $vocabulary
   *  Vocabulary machine name.
   */
  public function prepare_term_reference_field(&$row, $field_name, $vocabulary) {
    $data = $this->get_terms_from_source_field($row, $field_name);
    if (empty($data)) {
      return;
    }
    $row->{$field_name} = array();
    foreach($data as $term) {
      $tid = $this->get_taxonomy_term_tid($term['name'], $vocabulary);
      if ($tid === NULL) {
        $tid = $this->create_taxonomy_term($term['name'], $vocabulary, $term['translations']);
        if (function_exists('drush_log')) {
          drush_log(dt('Created new taxonomy term with tid = @tid', array('@tid' => $tid)), 'ok');
        }
      }
      $row->{$field_name}[] = $tid;
    }
  }

  /**
   * Map the nodes with the existing ones by title.
   * Used for `Entity Reference` fields.
   *
   * @param array $titles
   * @param $type
   * @return array
   *  An array of nids.
   */
  public function map_nodes_by_title($titles = array(), $type) {
    $op = 'IN';
    if (!is_array($titles)) {
      $op = '=';
    }
    $q = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('n.type', $type)
      ->condition('n.title', $titles, $op);
    return $q->execute()->fetchCol();
  }
}