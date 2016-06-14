<?php

/**
 * Class AbstractODataMigration is the base class for OData migrations.
 */
abstract class AbstractODataMigration extends Migration {
  /**
   * @var ODataConsumerConfig
   */
  protected $config = NULL;
  protected $odata_name = NULL;
  protected $arguments = NULL;

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->arguments   = $arguments;
    if (!empty($arguments['dependencies'])) {
      $this->dependencies = $arguments['dependencies'];
    }
    $config_klass = $arguments['config_class'];
    $this->config = new $config_klass($arguments);
    /* All OData entities should have  'updated' field to use as highwater */
    // $this->highwaterField = array('name' => 'updated', 'alias' => 'w', 'type' => 'int');
  }

  /**
   * Validate a row (e.g. has title)
   * @param stdClass $row
   * @return boolean
   *   TRUE if row is valid, FALSE
   */
  abstract function validateRow($row);

  /**
   * Basic preparations common to all migrated entities.
   *
   * @param stdClass $row
   *   Migrated row data
   *
   * @return boolean
   * Returns FALSE if the row is not to be migrated (ie. invalid)
   *
   * @throws MigrateException
   */
  function prepareRow($row) {
    if (!$this->config->isEnabled($this->getMachineName())) {
      throw new MigrateException('This migration is disabled (' . $this->getMachineName() . '). Enable from admin/config/services/odata-migrations/migrations');
    }
    migrate_instrument_start(__METHOD__);
    parent::prepareRow($row);
    if (!empty($row->updated)) {
      $row->updated = $this->fixDateValue($row->updated);
    }
    if (!empty($row->country) && $country = $this->getCountryByISO($row->country)) {
      $row->country = $country->nid;
    }
    migrate_instrument_stop(__METHOD__);
  }

  /**
   * Set translations to entity when content is available in multiple languages.
   *
   * @param $entity
   * @param $row
   */
  function prepare($entity, $row) {
    if (module_exists('uuid') && !$entity->is_new && $n = node_load($entity->nid)) {
      $entity->uuid = $n->uuid;
      $entity->vuuid = $n->vuuid;
    }
    $languages = $row->languages;
    unset($languages['en']);
    $this->setTranslation($entity, $languages);
  }

  /**
   * Transform OData Atom DateTime, measured in ticks to Drupal timestamp.
   *
   * @param string $value
   *   Value such as "/Date(1234567890123)/"
   *
   * @return int
   *   UNIX timestamp
   *
   */
  protected function fixDateValue($value) {
    if (strpos($value,'Date') == 1) {
      $ret = str_replace(array('/', 'Date', '(', ')'), '', $value);
      return intval($ret / 1000);
    }
    return $value;
  }

  /**
   * Wrapper around country module to find the country by arbitrary ISO code
   *
   * @param string $iso
   *   ISO 2-letter or 3-letter code
   *
   * @return mixed
   *   Country object or NULL
   */
  protected function getCountryByISO($iso) {
    module_load_include('inc', 'country', 'country.api');
    $node = country_load_by_iso($iso);
    if (!$node) {
      ws_consumer_odata_log(__METHOD__ . "($iso): Cannot find country by ISO code", MigrationBase::MESSAGE_WARNING);
    }
    return $node;
  }

  /**
   * Wrapper around treaty module to find the treaty by OData identifier
   *
   * @param string $identifier
   *   Identifier (ex. cbd)
   *
   * @return mixed
   *   Treaty object or NULL
   */
  protected function getTreatyByODataIdentifier($identifier) {
    module_load_include('inc', 'treaty', 'treaty.api');
    $node = treaty_load_by_odata_name($identifier);
    if (!$node) {
      ws_consumer_odata_log(__METHOD__ . "($identifier): Cannot find treaty by OData identifier code");
    }
    return $node;
  }

  function validateEnglishTitle($row) {
    if (empty($row->title_en)) {
      ws_consumer_odata_log('Skipping ' . $this->config->odata_entity . ' with source id=' . $row->id .' because no english title is present', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
    return TRUE;
  }

  function validateTreaty($row) {
    if (empty($row->treaty)) {
      ws_consumer_odata_log('Skipping ' . $this->config->odata_entity . ' with source id=' . $row->id .' because is missing treaty', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
    return TRUE;
  }

  public function setTranslation($entity, $translations = array()) {
    if (empty($translations)) {
      $translations = array();
    }
    $migration   = Migration::currentMigration();
    $languages   = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();

    $translation_handler = entity_translation_get_handler($entity_type, $entity);
    $translation_handler->setOriginalLanguage('en');
    $translation_handler->initTranslations();
    $entity->translations = $translation_handler->getTranslations();
    foreach ($languages as $language) {
      if ($language == 'en') {
        continue;
      }
      if (in_array($language, $translations)) {
        $translation_handler->setTranslation(array(
          'translate' => 0, 'status' => 1, 'uid' => 1,
          'language' => $language,
          'source' => 'en',
        ));
      }
    }
  }

  public function extractFilenameFromURL($url) {
    $ret = NULL;
    $to_remove = "download.aspx?d=";
    if (strpos($url, $to_remove)) {
      $ret = substr($url, strpos($url, $to_remove) + strlen($to_remove));
    }
    else {
      $l = parse_url($url);
      $ret = basename($l['path']);
    }
    return $ret;
  }
}
