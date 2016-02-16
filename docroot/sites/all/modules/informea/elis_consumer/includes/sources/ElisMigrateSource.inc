<?php

abstract class ElisMigrateSource extends MigrateSource {

  // Replace "SPAGE_QUERY_VALUE" and "SPAGE_FIRST_VALUE" in this string
  protected $generic_url;
  protected $start_date = '1981-01';
  protected $date_period = array();
  protected $spage_query_default_string = 'ES:I AND STAT:C';
  protected $key_field;
  protected $data = array();
  protected $allowed_languages = array(
    'en' => 'EN',
    'fr' => 'FR',
    'es' => 'ES',
    'sp' => 'SP',
  );
  protected $translatable_fields = array();
  protected $taxonomy_term_fields = array();

  public function __construct($generic_url, $key_field, $translatable_fields = array(), $taxonomy_term_fields = array()) {
    $this->generic_url = $generic_url;
    $this->key_field = $key_field;
    $this->translatable_fields = $translatable_fields;
    $this->taxonomy_term_fields = $taxonomy_term_fields;
    $this->date_period = $this->get_date_period();
  }

  public function hexadecimally_encode_string($str) {
    $unpack = unpack('H*', $str);
    return reset($unpack);
  }

  public function get_date_period($format = 'Y', $interval = '1 year') {
    $return = array();
    $begin = new DateTime($this->start_date);
    $end = new DateTime();

    $interval = DateInterval::createFromDateString($interval);
    $period = new DatePeriod($begin, $interval, $end);

    foreach ($period as $p) {
      $return[] = $p->format($format);
    }

    return $return;
  }

  public function computeCount() {
    $url = str_replace(
      array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
      array(
        $this->hexadecimally_encode_string($this->spage_query_default_string),
        0
      ),
      $this->generic_url
    );
    $xml = elis_consumer_get_xml_data_from_url($url);
    return intval($xml->attributes()['numberResultsFound']);
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    reset($this->data);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    $item = current($this->data);
    while ($item === FALSE && key($this->date_period) !== NULL) {
      $this->pullRemoteData();
      $item = reset($this->data);
    }
    next($this->data);
    return $item;
  }

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

  protected function getItem($data) {
    $ob = new stdClass();
    $parties = array();
    $abstract = '';
    foreach ($data as $field_name => $value) {
      if ($field_name == 'abstract') {
        $abstract .= (string) $value . PHP_EOL;
        continue;
      }
      elseif ($field_name == 'party') {
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
    $ob->abstract = $abstract;
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

  /**
   * Query the remote source and pull the data.
   */
  protected function pullRemoteData($period_type = 'year', $clear_data = TRUE) {
    if ($clear_data) {
      $this->data = array();
    }
    $months = array('*');
    if ($period_type != 'year') {
      $months = array('01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12');
    }
    foreach ($months as $month) {
      $query = $this->spage_query_default_string . ' AND DM:' . current($this->date_period) . $month;
      $spage_query = $this->hexadecimally_encode_string($query);
      $spage_first = 0;
      $url = str_replace(
        array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
        array($spage_query,$spage_first),
        $this->generic_url
      );
      $xml = elis_consumer_get_xml_data_from_url($url);
      while ($xml != NULL && ($numberResultsFound = intval($xml->attributes()['numberResultsFound'])) > $spage_first) {
        if ($numberResultsFound > 300 && $period_type == 'year') {
          $this->pullRemoteData('month', FALSE);
          break;
        }
        else {
          foreach ($xml->document as $doc) {
            $this->data[(string) $doc->{$this->key_field}] = $this->getItem($doc);
          }
          $spage_first += ELIS_ITEMS_PER_PAGE;
          if ($spage_first < $numberResultsFound) {
            $url = str_replace(
              array('SPAGE_QUERY_VALUE', 'SPAGE_FIRST_VALUE'),
              array($spage_query,$spage_first),
              $this->generic_url
            );
            $xml = elis_consumer_get_xml_data_from_url($url);
          }
        }
      }
    }
    next($this->date_period);
  }
}