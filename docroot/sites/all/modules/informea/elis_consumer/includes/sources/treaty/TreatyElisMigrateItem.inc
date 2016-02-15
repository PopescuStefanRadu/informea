<?php

class TreatyElisMigrateItem extends ElisMigrateItem {

  protected $item_url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=view_query_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&vq_query=';

  public function __construct($translatable_fields = array(), $taxonomy_term_fields = array()) {
    $this->translatable_fields = $translatable_fields;
    $this->taxonomy_term_fields = $taxonomy_term_fields;
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