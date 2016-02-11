<?php

class TreatyElisMigrateItem extends MigrateItem {

  protected $item_url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=view_query_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&vq_query=';

  public function getItem($id) {
    $vq_query = sprintf('ID:"%s"', $id);
    $xml = elis_consumer_get_xml_data_from_url($this->item_url . $vq_query);
    $json = json_encode($xml->document[0]);
    $ob = json_decode($json);
    return $ob;
  }
}