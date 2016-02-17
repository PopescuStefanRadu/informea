<?php

class CourtDecisionElisMigrateSource extends ElisMigrateSource {

  public function __construct($key_field, $translatable_fields = array(), $taxonomy_term_fields = array()) {
    $generic_url = 'http://www.ecolex.org/elis_isis3w.php?database=cou&search_type=page_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&spage_query=SPAGE_QUERY_VALUE&spage_first=SPAGE_FIRST_VALUE';
    parent::__construct($generic_url, $key_field, $translatable_fields, $taxonomy_term_fields);
  }

  public function __toString() {
    return sprintf('Extract court decisions from ELIS.');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return CourtDecisionElisMigrateSourceList::fields();
  }
}