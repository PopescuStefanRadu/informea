<?php

class TreatyElisMigrateItem extends ElisMigrateItem {

  public function __construct($translatable_fields = array(), $taxonomy_term_fields = array()) {
    $this->item_url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=view_query_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&vq_query=';
    $this->translatable_fields = $translatable_fields;
    $this->taxonomy_term_fields = $taxonomy_term_fields;
  }

}