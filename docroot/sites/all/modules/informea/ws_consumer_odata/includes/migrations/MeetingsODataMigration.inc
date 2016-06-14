<?php

/**
 * Class ContactsODataMigration migrate OData contacts
 */
class MeetingsODataMigration extends AbstractODataMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_MEETINGS, $this->config->odata_name);
    $this->source      = new InforMEAODataMeetingsMigrateSource($arguments, $this->config);
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
      ODataConsumerConfig::$DRUPAL_TYPE_MEETINGS,
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_en');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_language');
    $this->addFieldMapping('body', 'description');
    $this->addFieldMapping('body:language', 'description_language');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_url', 'url');
    $this->addFieldMapping('event_calendar_date', 'start');
    $this->addFieldMapping('event_calendar_date:to', 'end');
    $this->addFieldMapping('event_calendar_date:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_event_repetition', 'repetition');
    $this->addFieldMapping('field_event_repetition:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_repetition:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_kind', 'kind');
    $this->addFieldMapping('field_event_kind:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_kind:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_type', 'type');
    $this->addFieldMapping('field_event_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_type:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_access', 'access');
    $this->addFieldMapping('field_event_access:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_access:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_calendar_status', 'status');
    $this->addFieldMapping('field_event_calendar_status:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_calendar_status:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_event_images', 'imageUrl');
    $this->addFieldMapping('field_event_images:file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);
    $this->addFieldMapping('field_event_images:title', 'imageCopyright');
    $this->addFieldMapping('field_event_images:alt', 'imageCopyright');
    $this->addFieldMapping('field_location', 'location');
    $this->addFieldMapping('field_city', 'city');
    $this->addFieldMapping('field_country', 'country');
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

    $this->addUnmigratedDestinations(array(
      'created', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'body:summary', 'body:format', 'path',
      'field_event_calendar_status:source_type',
      'event_calendar_date:rrule',
      'field_abbreviation', 'field_event_access:source_type',
      'event_calendar_status', 'event_calendar_status:ignore_case',
      'event_calendar_status:create_term', 'event_calendar_status:source_type',
      'field_event_images:destination_file',
      'field_event_images:destination_dir', 'field_event_images:preserve_files',
      'field_event_images:file_class', 'field_informea_tags:ignore_case',
      'field_event_images:urlencode',
      'field_event_repetition:source_type', 'field_event_kind:source_type',
      'field_event_type:source_type', 'field_informea_tags',
      'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_url:title', 'field_url:attributes', 'field_url:language',
      'field_event_images:source_dir',
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
    $titles = $consumer->loadNavigationProperty($row, 'title');
    $row->title_en = ODataMigrationUtil::prepareTitle($titles);
    list($titles, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($titles);
    foreach($languages as &$language) {
      $language = ODataMigrationUtil::fixLanguage($language);
    }
    $row->title = $titles;
    $row->title_language = $languages;
    $all_languages = array_merge($all_languages, $languages);

    $descriptions = $consumer->loadNavigationProperty($row, 'description');
    list($descriptions, $languages) = ODataMigrationUtil::getSingleValuedMultilingualField($descriptions);
    foreach($languages as &$language) {
      $language = ODataMigrationUtil::fixLanguage($language);
    }
    $row->description = $descriptions;
    $row->description_language = $languages;
    $all_languages = array_merge($all_languages, $languages);
    $row->languages = array_unique($all_languages);

    /* Do some data transformation */
    if (!empty($row->start)) {
      $row->start = $this->fixDateValue($row->start);
    }
    if (!empty($row->end)) {
      $row->end = $this->fixDateValue($row->end);
    }
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
    if (empty($row->start)) {
      ws_consumer_odata_log('Skipping Meeting with id=' . $row->id .' because no start date could be found.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
    if (empty($row->type)) {
      ws_consumer_odata_log('Meeting with id=' . $row->id .' has no type', MigrationBase::MESSAGE_WARNING);
    }
    if (empty($row->url)) {
      ws_consumer_odata_log('Meeting with id=' . $row->id .' has no URL', MigrationBase::MESSAGE_WARNING);
    }
    if (empty($row->country)) {
      ws_consumer_odata_log('Meeting with id=' . $row->id .' has no country', MigrationBase::MESSAGE_WARNING);
    }
    if (empty($row->city)) {
      ws_consumer_odata_log('Meeting with id=' . $row->id .' has no city', MigrationBase::MESSAGE_WARNING);
    }
    if (empty($row->location)) {
      ws_consumer_odata_log('Meeting with id=' . $row->id .' has no location', MigrationBase::MESSAGE_WARNING);
    }
    return TRUE;
  }
}

class InforMEAODataMeetingsMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title_en' => 'Meeting title in English',
      'title' => 'Meeting title (multilingual)',
      'title_language' => 'List of languages for the `title`',
      'description' => 'Meeting description',
      'description_language' => 'Languages of the description',
      'treaty' => 'The corresponding treaty OData name of this meeting',
      'url' => 'Meeting URL',
      'start' => 'Start date',
      'end' => 'End date',
      'repetition' => 'Period of repetition',
      'kind' => 'Kind',
      'type' => 'Type',
      'access' => 'Access',
      'status' => 'Status',
      'imageUrl' => 'Image URL',
      'imageCopyright' => 'Image copyright info',
      'location' => 'Location',
      'city' => 'City',
      'country' => 'Country',
      'latitude' => 'Latitude',
      'longitude' => 'Longitude',
      'updated' => 'Record last update date',
      'languages' => 'List of translated languages (including en)',
    );
  }
}
