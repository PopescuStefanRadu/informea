<?php

/**
 * Class ODataConsumerConfig provides configuration framework for all migrations
 */
class ODataConsumerConfig {

  public static $ODATA_NAME_STOCKHOLM = 'stockholm';
  public static $ODATA_NAME_BASEL = 'basel';
  public static $ODATA_NAME_ROTTERDAM = 'rotterdam';
  public static $ODATA_NAME_CITES = 'cites';
  public static $ODATA_NAME_CMS = 'cms';
  public static $ODATA_NAME_AEWA = 'aewa';
  public static $ODATA_NAME_ASCOBANS = 'ascobans';
  public static $ODATA_NAME_EUROBATS = 'eurobats';
  public static $ODATA_NAME_CBD = 'cbd';
  public static $ODATA_NAME_OZONE = 'ozone';
  public static $ODATA_NAME_PLANT_TREATY = 'plant_treaty';
  public static $ODATA_NAME_WHC = 'whc';
  public static $ODATA_NAME_MONTREAL = 'montreal';
  public static $ODATA_NAME_RAMSAR = 'ramsar';
  public static $ODATA_NAME_UNFCCC = 'unfccc';

  public static $ODATA_ENTITY_CONTACTS = 'Contacts';
  public static $DRUPAL_TYPE_CONTACTS = 'contact_person';

  public static $ODATA_ENTITY_MEETINGS = 'Meetings';
  public static $DRUPAL_TYPE_MEETINGS = 'event_calendar';

  public static $ODATA_ENTITY_NATIONAL_REPORT = 'CountryReports';
  public static $DRUPAL_TYPE_NATIONAL_REPORT = 'national_report';

  public static $ODATA_ENTITY_ACTION_PLAN = 'NationalPlans';
  public static $DRUPAL_TYPE_ACTION_PLAN = 'action_plan';

  public static $ODATA_ENTITY_SITES = 'Sites';
  public static $DRUPAL_TYPE_SITES = 'geographical_site';

  public static $ODATA_ENTITY_DECISIONS = 'Decisions';
  public static $DRUPAL_TYPE_DECISIONS = 'decision';

  public static $ODATA_ENTITY_DOCUMENT = 'Documents';
  public static $DRUPAL_TYPE_DOCUMENT = 'document';

  protected static $SETTINGS_VARIABLE = 'informea_odata_consumer_config';
  public $odata_entity = NULL;
  public $odata_name = NULL;

  /**
   * Build new configuration object.
   *
   * @param array $arguments
   *   Endpoint configuration
   */
  public function __construct($arguments = array()) {
    if (isset($arguments['odata_entity'])) {
      $this->odata_entity = $arguments['odata_entity'];
    }
    if (isset($arguments['odata_name'])) {
      $this->odata_name = $arguments['odata_name'];
    }
  }

  static function getODataNames() {
    return array(
      ODataConsumerConfig::$ODATA_NAME_STOCKHOLM,
      ODataConsumerConfig::$ODATA_NAME_BASEL,
      ODataConsumerConfig::$ODATA_NAME_ROTTERDAM,
      ODataConsumerConfig::$ODATA_NAME_CITES,
      ODataConsumerConfig::$ODATA_NAME_CMS,
      ODataConsumerConfig::$ODATA_NAME_AEWA,
      ODataConsumerConfig::$ODATA_NAME_ASCOBANS,
      ODataConsumerConfig::$ODATA_NAME_EUROBATS,
      ODataConsumerConfig::$ODATA_NAME_CBD,
      ODataConsumerConfig::$ODATA_NAME_OZONE,
      ODataConsumerConfig::$ODATA_NAME_PLANT_TREATY,
      ODataConsumerConfig::$ODATA_NAME_WHC,
      ODataConsumerConfig::$ODATA_NAME_MONTREAL,
      ODataConsumerConfig::$ODATA_NAME_RAMSAR,
      ODataConsumerConfig::$ODATA_NAME_UNFCCC,
    );
  }

  static function getEntityNames() {
    return array(
      ODataConsumerConfig::$ODATA_ENTITY_CONTACTS,
      ODataConsumerConfig::$ODATA_ENTITY_MEETINGS,
      ODataConsumerConfig::$ODATA_ENTITY_NATIONAL_REPORT,
      ODataConsumerConfig::$ODATA_ENTITY_ACTION_PLAN,
      ODataConsumerConfig::$ODATA_ENTITY_SITES,
      ODataConsumerConfig::$ODATA_ENTITY_DECISIONS,
      ODataConsumerConfig::$ODATA_ENTITY_DOCUMENT,
    );
  }

  /**
   * Provide name of the OData consumer class to use, depending on the service.
   *
   * @return string
   *   Class name
   */
  public function getODataConsumerClass() {
    switch($this->odata_name) {
      case ODataConsumerConfig::$ODATA_NAME_CBD:
        $ret = 'ODataConsumerV3';
        break;
      default:
        $ret = 'ODataConsumerV1';
    }
    return $ret;
  }

  /**
   * Retrieve OData endpoint URL for the configured source.
   *
   * @return string
   *   URL to the service SVC
   */
  public function getEndpointURL() {
    $ret = NULL;
    $config = static::getConfiguration();
    if (!empty($config['endpoints'][$this->odata_name][$this->odata_entity])) {
      $ret = $config['endpoints'][$this->odata_name][$this->odata_entity];
    } else if (!empty($config['endpoints'][$this->odata_name]['default'])) {
      $ret = $config['endpoints'][$this->odata_name]['default'];
    }
    return $ret;
  }

  /**
   * Static mapping of the OData entities to Drupal content types.
   *
   * @return string
   *   Name of the drupal content type where data is stored
   */
  public function getTargetContentType() {
    $mappings = array(
      self::$ODATA_ENTITY_CONTACTS => self::$DRUPAL_TYPE_CONTACTS,
      self::$ODATA_ENTITY_MEETINGS => self::$DRUPAL_TYPE_MEETINGS,
      self::$ODATA_ENTITY_NATIONAL_REPORT => self::$DRUPAL_TYPE_NATIONAL_REPORT,
      self::$ODATA_ENTITY_ACTION_PLAN => self::$DRUPAL_TYPE_ACTION_PLAN,
      self::$ODATA_ENTITY_SITES => self::$DRUPAL_TYPE_SITES,
      self::$ODATA_ENTITY_DECISIONS => self::$DRUPAL_TYPE_DECISIONS,
      self::$ODATA_ENTITY_DOCUMENT => self::$DRUPAL_TYPE_DOCUMENT,
    );
    return $mappings[$this->odata_entity];
  }

  public function getDecisionMeetingMappingTable() {
    return 'migrate_map_odata_' . $this->odata_name . '_meetings';
  }

  static function getConfiguration() {
    $serialized = variable_get(self::$SETTINGS_VARIABLE, NULL);
    $config = static::getConfigurationDefault();
    if (!empty($serialized) && $deserialized = json_decode($serialized, TRUE)) {
      $config = $deserialized;
    }
    return $config;
  }

  static function getConfigurationDefault() {
    return array(
      'odata_page_size' => 100,
      'endpoints' => array(
        self::$ODATA_NAME_STOCKHOLM => array(
          'Contacts' => 'http://informea.pops.int/Contacts2/scContacts.svc',
          'Meetings' => 'http://informea.pops.int/Meetings/scMeetings.svc',
          'NationalPlans' => 'http://informea.pops.int/NationalPlans/scNationalPlans.svc',
          'Decisions' => 'http://informea.pops.int/Documents/sc/Decisions.svc',
        ),
        self::$ODATA_NAME_ROTTERDAM => array(
          'Contacts' => 'http://informea.pops.int/Contacts2/rcContacts.svc',
          'Meetings' => 'http://informea.pops.int/Meetings/rcMeetings.svc',
          'Decisions' => 'http://informea.pops.int/Documents/rc/Decisions.svc',
        ),
        self::$ODATA_NAME_BASEL => array(
          'Contacts' => 'http://informea.pops.int/Contacts2/BcContacts.svc',
          'Meetings' => 'http://informea.pops.int/Meetings/bcMeetings.svc',
          'Decisions' => 'http://informea.pops.int/Documents/bc/Decisions.svc',
        ),
        self::$ODATA_NAME_CITES => array(
          'default' => 'http://odata.cites.org/informea.svc'
        ),
        self::$ODATA_NAME_CMS => array(
          'default' => 'http://odata.cms.eaudeweb.ro/cms/informea.svc',
          'Documents' => 'http://localhost:8180/informea.svc'
        ),
        self::$ODATA_NAME_AEWA => array(
          'default' => 'http://odata.cms.eaudeweb.ro/aewa/informea.svc'
        ),
        self::$ODATA_NAME_ASCOBANS => array(
          'default' => 'http://odata.cms.eaudeweb.ro/ascobans/informea.svc'
        ),
        self::$ODATA_NAME_EUROBATS=> array(
          'default' => 'http://odata.cms.eaudeweb.ro/eurobats/services/odata.svc'
        ),
        self::$ODATA_NAME_CBD => array(
          'default' => 'https://api.cbd.int/informea.svc'
        ),
        self::$ODATA_NAME_OZONE => array(
          'default' => 'http://ozone.unep.org:8080/informea/services/odata.svc'
        ),
        self::$ODATA_NAME_PLANT_TREATY => array(
          'default' => 'http://odata.informea.org/odata-fao/services/odata.svc'
        ),
        self::$ODATA_NAME_WHC => array(
          'default' => 'http://whc.unesco.org/informea/informea.svc'
        ),
        self::$ODATA_NAME_MONTREAL => array(
          'default' => 'http://41.191.194.28:8080/informea/services/odata.svc'
        ),
        self::$ODATA_NAME_RAMSAR => array(
          'default' => 'http://cray.edw.lan:34382/informea.svc'
        ),
      ),
      'websites' => array(
        self::$ODATA_NAME_STOCKHOLM => 'http://chm.pops.int',
        self::$ODATA_NAME_ROTTERDAM => 'http://www.pic.int',
        self::$ODATA_NAME_BASEL => 'http://www.basel.int',
        self::$ODATA_NAME_CITES => 'http://www.cites.org',
        self::$ODATA_NAME_CMS => 'http://www.cms.int',
        self::$ODATA_NAME_AEWA => 'http://www.unep-aewa.org',
        self::$ODATA_NAME_ASCOBANS => 'http://www.ascobans.org',
        self::$ODATA_NAME_EUROBATS=> 'http://www.eurobats.org',
        self::$ODATA_NAME_CBD => 'http://www.cbd.int',
        self::$ODATA_NAME_OZONE => 'http://ozone.unep.org',
        self::$ODATA_NAME_PLANT_TREATY => 'http://www.planttreaty.org',
        self::$ODATA_NAME_WHC => 'http://whc.unesco.org',
        self::$ODATA_NAME_MONTREAL => 'http://ozone.unep.org',
        self::$ODATA_NAME_RAMSAR => 'http://www.ramsar.org',
      ),
      'disabled' => array()
    );
  }

  static function getMEAWebsites() {
    return self::getConfigurationDefault()['websites'];
  }

  static function saveConfiguration($config) {
    variable_set(self::$SETTINGS_VARIABLE, json_encode($config));
  }

  static function isEnabled($migration_name) {
    $config = static::getConfiguration();
    return empty($config['disabled'][$migration_name]);
  }

  function getListingQueryString() {
    switch ($this->odata_entity) {

      case self::$ODATA_ENTITY_CONTACTS:
        if (in_array($this->odata_name, array(
          self::$ODATA_NAME_CBD
        ))) {
          return '&$expand=treaties,roles&$orderby=updated%20desc,id';
        }
        return '&$expand=treaties&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_NATIONAL_REPORT:
        return '&$expand=title,files&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_DECISIONS:
        if (in_array($this->odata_name, array(
          self::$ODATA_NAME_STOCKHOLM,
          self::$ODATA_NAME_ROTTERDAM,
          self::$ODATA_NAME_BASEL
        ))) {
          return '&$expand=title,files,summary&$orderby=updated%20desc,id';
        }
        return '&$expand=title,files,content,summary&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_MEETINGS:
        return '&$expand=title,description&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_ACTION_PLAN:
        return '&$expand=title,files&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_SITES:
        return '&$expand=name&$orderby=updated%20desc,id';

      case self::$ODATA_ENTITY_DOCUMENT:
        return '&$expand=authors,descriptions,files,identifier,keywords,referenceToEntities,tag,titles,types&$orderby=updated%20desc,id';
    }
    return '';
  }

  static function getODataPageSize() {
    $config = static::getConfiguration();
    $size = 100;
    if (!empty($config['odata_page_size'])) {
      $size = $config['odata_page_size'];
    }
    return $size;
  }
}
