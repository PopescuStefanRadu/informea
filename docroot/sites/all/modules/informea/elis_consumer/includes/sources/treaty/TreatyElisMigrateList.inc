<?php

/**
 * Class TreatyElisMigrateList. See MigrateSourceList pattern.
 *
 * @see https://www.drupal.org/node/1152152
 */
class TreatyElisMigrateList extends ElisMigrateList {

  public function __construct($key_field) {
    parent::__construct();
    // Replace "SPAGE_QUERY_VALUE" and "SPAGE_FIRST_VALUE" in this string
    $this->generic_url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=page_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&spage_query=SPAGE_QUERY_VALUE&spage_first=SPAGE_FIRST_VALUE';
    $this->key_field = $key_field;
  }

  /** {@inheritdoc} */
  public function __toString() {
    return sprintf('Extract treaties from ELIS.');
  }

}
