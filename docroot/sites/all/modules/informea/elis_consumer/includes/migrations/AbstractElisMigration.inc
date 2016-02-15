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

  public function setTranslation($entity, $translations = array()) {
    $migration   = Migration::currentMigration();
    $languages   = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();

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
}