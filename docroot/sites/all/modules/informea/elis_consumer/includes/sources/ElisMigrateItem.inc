<?php

abstract class ElisMigrateItem extends MigrateItem {

  protected $item_url;
  private $allowed_languages = array(
    'en' => 'EN',
    'fr' => 'FR',
    'es' => 'ES',
    'sp' => 'SP',
  );
  protected $translatable_fields = array();
  protected $taxonomy_term_fields = array();

  protected function translateField(&$item, $field_name) {
    if (!property_exists($item, $field_name)) {
      return;
    }
    $item->{$field_name} = array($item->{$field_name});
    $item->{$field_name . '_languages'} = array('en');
    foreach ($this->allowed_languages as $lang => $LANG) {
      if (in_array($field_name, array('titleOfText', 'linkToFullText'))) {
        $property = $field_name . ucfirst($lang);
      }
      else {
        $property = sprintf('%s_%s_%s', $field_name, $lang, $LANG);
      }
      if (property_exists($item, $property)) {
        if ($lang == 'sp') {
          $lang = 'es';
        }
        $item->{$field_name}[] = $item->{$property};
        $item->{$field_name . '_languages'}[] = $lang;
      }
    }
  }
}