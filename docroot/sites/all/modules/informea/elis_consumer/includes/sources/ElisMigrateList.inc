<?php

define('ELIS_ITEMS_PER_PAGE', 20);

/**
 * Class ElisMigrateList. See MigrateSourceList pattern.
 *
 * @see https://www.drupal.org/node/1152152
 */
abstract class ElisMigrateList extends MigrateList {

  // Replace "SPAGE_QUERY_VALUE" and "SPAGE_FIRST_VALUE" in this string
  protected $generic_url;
  protected $start_date = '1981-01';
  protected $spage_query_default_string = 'ES:I AND STAT:C';
  protected $key_field;

  public function hexadecimally_encode_string($str) {
    $unpack = unpack('H*', $str);
    return reset($unpack);
  }

  public function get_date_period() {
    $return = array();
    $begin = new DateTime($this->start_date);
    $end = new DateTime();

    $interval = DateInterval::createFromDateString('1 month');
    $period = new DatePeriod($begin, $interval, $end);

    foreach ($period as $p) {
      $return[] = $p->format('Ym');
    }

    return $return;
  }

  /** {@inheritdoc} */
  public function getIDList() {
    $ids = array();
    $spage_query = $this->hexadecimally_encode_string($this->spage_query_default_string);
    $spage_first = 0;
    $url = str_replace(
      array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
      array($spage_query,$spage_first),
      $this->generic_url
    );
    $xml = elis_consumer_get_xml_data_from_url($url);
    while ($xml != NULL && intval($xml->attributes()['numberResultsFound']) > $spage_first) {
      foreach ($xml->document as $item) {
        $ids[] = (string) $item->{$this->key_field};
      }
      $spage_first += ELIS_ITEMS_PER_PAGE;
      $url = str_replace(
        array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
        array($spage_query,$spage_first),
        $this->generic_url
      );
      $xml = elis_consumer_get_xml_data_from_url($url);
    }
    return array_unique($ids);
  }

  /** {@inheritdoc} */
  public function computeCount() {
    $url = str_replace(
      array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
      array($this->hexadecimally_encode_string($this->spage_query_default_string),0),
      $this->generic_url
    );
    $xml = elis_consumer_get_xml_data_from_url($url);
    return intval($xml->attributes()['numberResultsFound']);
  }

}
