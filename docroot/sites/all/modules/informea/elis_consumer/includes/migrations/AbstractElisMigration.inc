<?php

abstract class AbstractElisMigration extends Migration {

  protected $translatable_fields = array();

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
}