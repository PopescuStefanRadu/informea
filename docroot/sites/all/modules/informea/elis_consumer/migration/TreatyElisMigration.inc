<?php

define('ELIS_ITEMS_PER_PAGE', 20);
define('DRUPAL_TYPE_TREATY', 'treaty');

/**
 * Class TreatyElisMigrateSourceList provides fields for Treaty migration.
 */
class TreatyElisMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'Recid' => 'Remote primary key',
      'dateOfEntry' => 'Date of entry',
      'dateOfModification' => 'Date of modification',
      'titleOfText' => 'Title of text',
      'titleAbbreviation' => 'Title abbreviation',
      'typeOfText' => 'Type of text',
      'jurisdiction' => 'Jurisdiction',
      'fieldOfApplication' => 'Field of application',
      'sortFieldOfApplication' => 'sortFieldOfApplication',
      'region' => 'Region',
      'subject' => 'Subject',
      'languageOfDocument' => 'Language',
      'languageOfTranslation' => 'Original language', //???
      'placeOfAdoption' => 'Place of adoption',
      'depository' => 'Depository (country)',
      'dateOfText' => 'Date of text', //???
      'searchDate' => 'Search date', //???
      'entryIntoForceDate' => 'Entry into force that', //Not the same as dateOfEntry???
      'obsolete' => 'Obsolete', //???
      'officialPublication' => 'Official publication',
      'availableIn' => 'Available in', //???
      'linkToFullText' => 'Link to the full text',
      'relatedWebSite' => 'Related website',
      'keyword' => 'Keywords',
      'abstract' => 'Abstract',
      'amendsTreaty' => 'Amends treaty', //???
      'party' => 'Parties', //???
    );
  }
}

/**
 * Class TreatyElistMigrateList. See MigrateSourceList pattern.
 *
 * @see https://www.drupal.org/node/1152152
 */
class TreatyElistMigrateList extends MigrateList {

  // Replace "SPAGE_QUERY_VALUE" and "SPAGE_FIRST_VALUE" in this string
  protected $generic_url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=page_search&table=all&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&spage_query=SPAGE_QUERY_VALUE&spage_first=SPAGE_FIRST_VALUE';
  protected $start_date = '1981-01';
  protected $spage_query_default_string = 'ES:I AND STAT:C';

  public function __construct() {
    parent::__construct();
  }

  /** {@inheritdoc} */
  public function __toString() {
    return sprintf('Extract treaties from ELIS.');
  }

  public function hexadecimally_encode_string($str) {
    return reset(unpack('H*', $str));
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
      foreach ($xml->document as $treaty) {
        $ids[] = (string) $treaty->Recid;
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

class TreatyElisMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->source = new TreatyElisMigrateSourceList(
      new TreatyElistMigrateList(),
      new TreatyElisMigrateItem()
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'Recid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the ELIS',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_TREATY);
  }

}