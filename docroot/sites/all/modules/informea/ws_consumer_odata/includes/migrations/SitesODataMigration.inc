<?php

/**
 * Class SitesODataMigration migrate OData contacts
 */
class SitesODataMigration extends AbstractODataMigration {

  /**
   * @var ODataConsumerConfig
   */
  protected $config = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_SITES, $this->config->odata_name);
    $this->source      = new InforMEAODataSitesMigrateSource($arguments, $this->config);
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the MEA website',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode(
      ODataConsumerConfig::$DRUPAL_TYPE_SITES,
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_en');
    $this->addFieldMapping('title_field', 'names');
    $this->addFieldMapping('title_field:language', 'names_language');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('field_latitude', 'latitude');
    $this->addFieldMapping('field_longitude', 'longitude');

    $this->addFieldMapping('field_last_update', 'updated');
    $this->addFieldMapping('field_last_update:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('changed', 'updated');

    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body', 'body:summary', 'body:format', 'path',
      'body:language', 'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
      'field_url:language', 'field_url:attributes', 'field_url:title',
      'field_last_update:rrule', 'field_last_update:to',
    ));
  }

  /**
   * Add some Contacts specific preparations.
   *
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);

    /* Fill with remote-data */
    $consumer = $this->source->getConsumer();
    $all_languages = array('en');
    $names = $consumer->loadNavigationProperty($row, 'name');
    $row->title_en = ODataMigrationUtil::prepareTitle($names);
    list($names, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($names);
    $row->names = $names;
    $row->names_language = $languages;
    $all_languages = array_merge($all_languages, $languages);
    $row->languages = array_unique($all_languages);

    /* Do some data transformation */
    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;
    return $this->validateRow($row);
  }

  public function validateRow($row) {
    if (!$this->validateEnglishTitle($row)) {
      return FALSE;
    }
    if (!$this->validateTreaty($row)) {
      return FALSE;
    }
    return TRUE;
  }
}


class InforMEAODataSitesMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title_en' => 'Site name in English',
      'names' => 'Site name translations',
      'names_language' => 'Site name languages',
      'treaty' => 'Site treaty',
      'country' => 'Country',
      'url' => 'Site URL on MEA website',
      'latitude' => 'Geographical latitude',
      'longitude' => 'Geographical longitude',
      'updated' => 'Date of last update',
    );
  }
}
