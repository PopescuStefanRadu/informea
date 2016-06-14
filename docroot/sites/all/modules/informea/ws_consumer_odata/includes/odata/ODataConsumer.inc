<?php

/**
 * Class ODataConsumer talks to OData endpoints and gets data from the service.
 *
 * Supports OData v1
 */
abstract class ODataConsumer {

  /** @var ODataConsumerConfig */
  protected $config = NULL;
  /** @var bool Use /Entity(guid'XXX-XXX-XX') in request URLs */
  protected $useGUIDInURL = FALSE;

  public function __construct($config) {
    $this->config = $config;
  }

  /**
   * Does an OData remote entity count, this call is not cached.
   *
   * @return int
   *   Number of entities or zero
   */
  public function countTotal($entity) {
    $ret = 0;
    $base_url = $this->config->getEndpointURL();
    $url = $base_url . '/' . $entity . '/$count';
    ws_consumer_odata_log(get_class($this) . ': Remote counting entities: ' . $url);
    $response = ODataMigrationUtil::http_request($url);
    if (!empty($response)) {
      $ret = intval($response);
    }
    else {
      $url = $base_url . '/' . $entity . '?$inlinecount=allpages';
      $response = ODataMigrationUtil::http_request($url);
      $element_name = 'm:count';
      $found = preg_match(
        '#<'.$element_name.'(?:\s+[^>]+)?>(.*?)'.'</'.$element_name.'>#s',
        $response,
        $matches
      );
      if ($found) {
        $ret = intval($matches[1]);
      }
      else {
        ws_consumer_odata_log('FAIL: ' . get_class($this) . ': Remote counting entities: ' . $url, MigrationBase::MESSAGE_WARNING);
      }
    }
    return $ret;
  }

  /**
   * Retrieve a single entity from the service, given its type and id.
   *
   * @param string string $entity
   *   Type of data (ie. Contacts)
   * @param string $id
   *   Unique identifier in the target service
   * @param string $odata_extra_params
   *   Extra query to pass to OData service (ex. &$expand=treaties to get inline data)
   *
   * @return stdClass
   *   Object build from the JSON parsed data
   */
  public function getItem($entity, $id, $odata_extra_params = '') {
    $ret = NULL;
    $base_url = $this->config->getEndpointURL();
    $url = $base_url . '/' . $entity . "('" . $id . "')?" . $odata_extra_params;
    ws_consumer_odata_log(__METHOD__ . "($entity, $id): Retrieving data from : $url", MigrationBase::MESSAGE_NOTICE);
    $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
    if (empty($response)) {
      if ($this->useGUIDInURL) {
        $url = $base_url . '/' . $entity . "(guid'" . $id . "')?" . $odata_extra_params;
      }
      else {
        $url = $base_url . '/' . $entity . "('" . $id . "')?" . $odata_extra_params;
      }
      $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
      if (empty($response)) {
        ws_consumer_odata_log(__METHOD__ . "($entity, $id): HTTP request failure ({$response->code}) for URL: $url", MigrationBase::MESSAGE_ERROR);
        return $ret;
      }
    }
    if ($json = json_decode($response)) {
      $ret = $json->d;
    }
    else {
      ws_consumer_odata_log(__METHOD__ . "($entity, $id): Failed to unpack JSON data from $url", MigrationBase::MESSAGE_ERROR);
    }
    return $ret;
  }

  /**
   * Check the item exists in the remote source
   *
   * @param string $entity
   *   OData entity
   * @param $id
   *   OData entity ID
   *
   * @return boolean
   *   TRUE if the record exists
   */
  public function itemExists($entity, $id) {
    $base_url = $this->config->getEndpointURL();
    $url = $base_url . '/' . $entity . "('" . $id . "')";
    $ch = curl_init($url);
    curl_setopt ($ch, CURLOPT_TIMEOUT, 30);
    curl_setopt ($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($ch,CURLOPT_MAXREDIRS, 3);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($ch, CURLOPT_NOBODY, FALSE);
    curl_exec($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    if ($code != 200 && $code != 301) {
      return FALSE;
    }
    return TRUE;
  }


  /**
   * Return a single page of results
   *
   * @param Migration $migration
   *
   * @return array
   *   Array of stdClass objects
   */
  public function getPaginatedData($entity, $limit, $migration) {
    $ret = array();
    $pageSize = ODataConsumerConfig::getODataPageSize();
    $page = 0;
    $base_url = $this->config->getEndpointURL();
    $base_url = $base_url . '/' . $entity;
    $url = sprintf($base_url . '?$top=%d&$skip=%d', $pageSize, $page);
    $odata_filter = $this->config->getListingQueryString();
    if ($odata_filter) {
      $url .= $odata_filter;
    }
    $previous = NULL;
    $total = 0;
    $migration->getOption('update');
    while ($rows = $this->parseJSONRemoteListPage($url)) {
      // Detect infinite loop when the service does not recognise pagination
      if (json_encode($rows) === json_encode($previous)) {
        break;
      };
      if (!empty($rows)) {
        foreach ($rows as $id => $row) {
          $total++;
          if (array_key_exists($id, $ret)) {
            ws_consumer_odata_log(__METHOD__ . ": Ignoring duplicate row, id:" . $row->id . " feed: " . $url, MigrationBase::MESSAGE_WARNING);
            continue;
          }
          else {
            $ret[$id] = $row;
            if ($limit && count($ret) >= $limit) {
              break;
            }
          }
        }
      }
      $page += $pageSize;
      $url = sprintf($base_url . '?$top=%d&$skip=%d', $pageSize, $page);
      $url .= $odata_filter;
      $previous = $rows;
    }
    $msg = sprintf(__METHOD__ . '(%s): Remote service had %d, returned %d results', $this->config->odata_entity, $total, count($ret));
    ws_consumer_odata_log($msg);
    return $ret;
  }


  /**
   * Return a single page of results
   *
   * @param Migration $migration
   *
   * @return array
   *   Array of stdClass objects
   */
  public function getPage($entity, $start, $migration) {
    $ret = array();
    $pageSize = ODataConsumerConfig::getODataPageSize();
    $base_url = $this->config->getEndpointURL() . '/' . $entity;
    $url = sprintf($base_url . '?$top=%d&$skip=%d', $pageSize, $start);
    $odata_filter = $this->config->getListingQueryString();
    if ($odata_filter) {
      $url .= $odata_filter;
    }
    $previous = NULL;
    $migration->getOption('update');
    if ($rows = $this->parseJSONRemoteListPage($url)) {
      foreach ($rows as $id => $row) {
        $ret[$id] = $row;
      }
    }
    $msg = sprintf(__METHOD__ . '(%s): Remote service returned %d results', $this->config->odata_entity, count($ret), count($ret));
    ws_consumer_odata_log($msg);
    return $ret;
  }


  /**
   * Parse the JSON OData feed.
   *
   * @param string $url
   *   The URL to download the data
   *
   * @return array
   *   Array of stdClass
   */
  protected function parseJSONRemoteListPage($url) {
    $ret = array();
    if ($remote = $this->loadRemoteData($url)) {
      $results = gettype($remote) == 'object' ? $remote->results : $remote;
      foreach ($results as $row) {
        $ret[$row->id] = $row;
      }
    }
    return $ret;
  }

  public function loadRemoteData($url) {
    $ret = NULL;
    ws_consumer_odata_log(__METHOD__ . ": Retrieving OData result from: " . $url, MigrationBase::MESSAGE_NOTICE);
    $response = ODataMigrationUtil::http_request($url, array('Accept: application/json'));
    if (!empty($response) && $json = json_decode($response)) {
      $ret = $json->d;
    }
    return $ret;
  }

  public function loadNavigationProperty($ob, $property_name) {
    // OData v1, property expanded using $expand=property_name
    // No need for an additional HTTP request, data already there
    $results = array();
    if (!empty($ob->{$property_name})) {
      if (gettype($ob->{$property_name}) == 'object') {
        if (property_exists($ob->{$property_name}, 'results')) {
          return $ob->{$property_name}->results;
        }
      }
      else {
        $results = $ob->{$property_name};
      }
    }
    if (!empty($ob->{$property_name}) && !empty($results)) {
      return $results;
    }
    // OData v1, without $expand.
    if (!empty($ob->{$property_name}->__deferred->uri)) {
      /** @var stdClass $result */
      if ($result = $this->loadRemoteData($ob->{$property_name}->__deferred->uri)) {
        if ($property_name == 'files') {
          if (is_object($result) && property_exists($result, 'results')) {
            return $result->results;
          }
          else {
            return $result;
          }
        }
        return $result->results;
      }
    }
    return NULL;
  }

  /**
   * @abstract
   *
   * @return array
   *   Array keyed by treaty, with roles as strings.
   */
  public function loadContactRolesProperty($ob) { return array(); }
}
