<?php

class CourtDecisionElisMigrateItem extends ElisMigrateItem {

  public function __construct($translatable_fields = array(), $taxonomy_term_fields = array()) {
    $this->item_url = 'http://www.ecolex.org/elis_isis3w.php?database=cou&search_type=view_query_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&vq_query=';
    $this->translatable_fields = $translatable_fields;
    $this->taxonomy_term_fields = $taxonomy_term_fields;
  }

  public function getItem($id) {
    $ob = new stdClass();
    $vq_query = sprintf('ID:"%s"', $id);
    $xml = elis_consumer_get_xml_data_from_url($this->item_url . $vq_query);
    return $ob;
  }
}