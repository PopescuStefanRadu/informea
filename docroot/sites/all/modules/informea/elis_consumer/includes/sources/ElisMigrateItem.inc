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

  public function getItem($id) {
    $ob = new stdClass();
    $vq_query = sprintf('ID:"%s"', $id);
    $xml = elis_consumer_get_xml_data_from_url($this->item_url . $vq_query);
    $parties = array();
    foreach ($xml->document[0] as $field_name => $value) {
      if ($field_name == 'party') {
        $parties[] = $value;
        continue;
      }
      elseif (property_exists($ob, $field_name)) {
        if (is_array($ob->{$field_name})) {
          $ob->{$field_name}[] = (string)$value;
        }
        else {
          $ob->{$field_name} = array($ob->{$field_name}, (string) $value);
        }
      }
      else {
        if ($field_name == 'titleOfText') {
          $ob->titleOfText_original = (string) $value;
        }
        $ob->{$field_name} = (string) $value;
      }
    }
    $ob->parties = $parties;
    if (property_exists($ob, 'obsolete')) {
      $ob->obsolete = (int) $ob->obsolete;
    }
    foreach ($this->translatable_fields as $field_name) {
      $this->translateField($ob, $field_name);
    }
    foreach ($this->taxonomy_term_fields as $field_name) {
      if (!empty($ob->{$field_name})) {
        $ob->{$field_name . '_translations'} = $ob->{$field_name};
        $ob->{$field_name} = reset($ob->{$field_name});
      }
    }
    return $ob;
  }
}