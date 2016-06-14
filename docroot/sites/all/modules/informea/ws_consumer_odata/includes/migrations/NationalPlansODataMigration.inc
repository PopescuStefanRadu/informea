<?php

/**
 * Class NationalPlansODataMigration migrate OData contacts
 */
class NationalPlansODataMigration extends AbstractODataMigration {

  /**
   * @var ODataConsumerConfig
   */
  protected $config = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = sprintf('Import %s from %s', ODataConsumerConfig::$DRUPAL_TYPE_ACTION_PLAN, $this->config->odata_name);
    $this->source      = new InforMEAODataNationalPlansMigrateSource($arguments, $this->config);
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
      ODataConsumerConfig::$DRUPAL_TYPE_ACTION_PLAN,
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'title_en');
    $this->addFieldMapping('title_field', 'title');
    $this->addFieldMapping('title_field:language', 'title_language');
    $this->addFieldMapping('field_treaty', 'treaty');
    $this->addFieldMapping('field_action_plan_type', 'type');
    $this->addFieldMapping('field_sorting_date', 'submission');
    $this->addFieldMapping('field_sorting_date:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_document_url', 'url');

    $this->addFieldMapping('field_files', 'files');
    $this->addFieldMapping('field_files:description', 'files');
    $this->addFieldMapping('field_files:language', 'files_language');
    $this->addFieldMapping('field_files:destination_dir')->defaultValue('public://reports/action_plans/' . $this->config->odata_name);
    $this->addFieldMapping('field_files:destination_file', 'filename');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);

    $this->addFieldMapping('field_action_plan_type:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_action_plan_type:ignore_case')->defaultValue(TRUE);

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
      'body', 'body:summary', 'body:format', 'path',
      'body:language', 'field_action_plan_type:source_type',
      'field_sorting_date:rrule',
      'field_sorting_date:to','field_document_url:title',
      'field_document_url:attributes', 'field_document_url:language',
      'field_files:file_class', 'field_files:preserve_files',
      'field_files:source_dir', 'field_files:urlencode', 'field_files:display',
      'field_informea_tags', 'field_informea_tags:source_type',
      'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
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
    $row->title = $titles;
    $row->title_language = $languages;
    $all_languages = array_merge($all_languages, $languages);

    $files = $consumer->loadNavigationProperty($row, 'files');
    $row->files = array();
    $row->files_language = array();
    $row->filename = array();
    foreach($files as $file) {
      if (empty($file->url)) {
        ws_consumer_odata_log('Invalid file for National Plan id=' . $row->id, MigrationBase::MESSAGE_WARNING);
        continue;
      }

      // Filename validation
      $filename = NULL;
      if (!empty($row->filename)) {
        $filename = $row->filename;
      }
      else {
        $filename = ODataMigrationUtil::filenameFromURL($file->url);
      }
      if (empty($filename)) {
        ws_consumer_odata_log('Invalid filename for National Plan id=' . $row->id . '. File URL: ' . $file->url, MigrationBase::MESSAGE_WARNING);
        continue;
      }

      // File language handling
      if (empty($file->language)) {
        ws_consumer_odata_log('Missing language for file, National Plan id=' . $row->id . '. File URL: ' . $file->url, MigrationBase::MESSAGE_WARNING);
        continue;
      }
      $language = $file->language;
      $all_languages[] = $language;

      $row->files[] = $file->url;
      $row->filename[] = $filename;
      $row->files_language[] = $language;
    }
    $row->languages = array_unique($all_languages);

    /* Do some data transformation */
    if (!empty($row->submission)) {
      $row->submission = $this->fixDateValue($row->submission);
    }
    $row->treaty = $this->getTreatyByODataIdentifier($row->treaty)->nid;
    $row->filename = array();
    foreach ($row->files as $file) {
      if (is_object($file)) {
        if ($filename = $this->extractFilenameFromURL($file->url)) {
          $row->filename[] = $filename;
        }
      }
      else {
        if ($filename = $this->extractFilenameFromURL($file)) {
          $row->filename[] = $filename;
        }
      }
    }
    return $this->validateRow($row);
  }

  public function validateRow($row) {
    if (!$this->validateEnglishTitle($row)) {
      return FALSE;
    }
    if (!$this->validateTreaty($row)) {
      return FALSE;
    }
    if (!$row->type) {
      ws_consumer_odata_log('Skipping National Plan with source id=' . $row->id .' missing type.', MigrationBase::MESSAGE_ERROR);
      return FALSE;
    }
    if (empty($row->files)) {
      ws_consumer_odata_log('National Plan with id=' . $row->id . ' has no files', MigrationBase::MESSAGE_WARNING);
    }
    return TRUE;
  }
}


class InforMEAODataNationalPlansMigrateSource extends InforMEAAbstractODataMigrateSource {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'title' => 'Translated titles',
      'title_en' => 'Report title in English',
      'title_language' => 'Title languages',
      'treaty' => 'The meeting is linked to this treaty',
      'country' => 'Country',
      'type' => 'Type',
      'url' => 'Document URL',
      'submission' => 'Submission date',
      'files' => 'Files',
      'files_language' => 'Files language',
      'filename' => 'filename',
      'updated' => 'Updated',
    );
  }
}
