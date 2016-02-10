<?php

/**
 * Class TreatyElisMigrateSourceList provides fields for Treaty migration.
 */
class TreatyElisMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
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

  // @todo: change "spage_first" parameter
  protected $url = 'http://www.ecolex.org/elis_isis3w.php?database=tre&search_type=page_search&table=all&spage_query=45533a4920414e4420535441543a4320414e44202844453a323031323031204f5220444d3a32303132303129&format_name=@xmlexp&lang=xmlf&page_header=@xmlh&spage_first=11&free_text=(v120^d[1]%3E%2720120101%27)%20or%20(v130^d[nocc(v130)]%3E%2720120101%27)';

  public function __construct() {
    parent::__construct();
  }

  /** {@inheritdoc} */
  public function __toString() {
    return sprintf('Extract treaties from ELIS.');
  }

  public function get_xml_data_from_url($url = NULL) {
    if ($url === NULL) {
      $url = $this->url;
    }
    $response = drupal_http_request($url, array('headers' => array('Accept' => 'application/xml')));
    if ($response->code != 200) {
      if (function_exists('drush_log')) {
        drush_log('Could not retrieve treaties data from ELIS.', 'error');
      }
      return NULL;
    }
    $data = trim(utf8_encode($response->data));
    $xml = simplexml_load_string($data);
    return $xml;
  }

  /** {@inheritdoc} */
  public function getIDList() {
    $ids = array();
    $xml = $this->get_xml_data_from_url();
    foreach ($xml->document as $treaty) {
      $ids[] = (string) $treaty->Recid;
    }
    return $ids;
  }

  /** {@inheritdoc} */
  public function computeCount() {
    $xml = $this->get_xml_data_from_url();
    if (empty($xml)) {
      return 0;
    }
    return intval($xml->attributes()['numberResultsFound']);
  }

}

class TreatyElisMigrateItem extends MigrateItem {

  public function __construct() {

  }

  public function getItem($id) {
    // TODO: Implement getItem() method.
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
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the ELIS',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
  }

}