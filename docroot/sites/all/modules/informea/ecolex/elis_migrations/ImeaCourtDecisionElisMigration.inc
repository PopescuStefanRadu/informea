<?php

define('DRUPAL_TYPE_COURT_DECISION', 'court_decisions');

class ImeaCourtDecisionElisMigration extends CourtDecisionElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_COURT_DECISION);

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('title', 'titleOfText_original');
    $this->addFieldMapping('title_field', 'titleOfText');
    $this->addFieldMapping('title_field:language', 'titleOfText_languages');
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_court_decision_id_number', 'id');
    $this->addFieldMapping('field_alternative_record_id', 'id2');
    $this->addFieldMapping('field_court_name', 'courtName');
    $this->addFieldMapping('field_number_of_pages', 'numberOfPages');
    $this->addFieldMapping('field_abstract', 'abstract');
    // @ToDo: Map country by name
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_reference_number', 'referenceNumber');
    $this->addFieldMapping('field_source_language', 'languageOfDocument');
    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_url', 'linkToFullText');
    $this->addFieldMapping('field_url:language', 'linkToFullText_languages');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('field_isis_number', 'isisMfn');
    // @ToDo: Map legislation by source id
    $this->addFieldMapping('field_reference_to_legislation', 'referenceToNationalLegislation');

    $this->addUnmigratedSources(array(
      'titleOfTextShort', 'dateOfText', 'availableIn', 'abstract_languages',
    ));

    $this->addUnmigratedDestinations(array(
      'created', 'changed', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'field_ecolex_tags:create_term', 'field_ecolex_tags:ignore_case',
      'field_keywords:create_term', 'field_keywords:ignore_case',
      'field_files', 'field_files:file_class', 'field_files:language', 'field_files:preserve_files',
      'field_files:destination_dir', 'field_files:destination_file', 'field_files:file_replace',
      'field_files:display', 'field_files:description', 'field_files:urlencode',
      'field_files:source_dir', 'field_justices', 'field_jurisdiction:ignore_case',
      'field_jurisdiction:create_term', 'field_jurisdiction:source_type', 'field_jurisdiction',
      'field_informea_tags:ignore_case', 'field_informea_tags:create_term',
      'field_informea_tags:source_type', 'field_informea_tags', 'field_abstract:format',
      'field_city:language', 'field_city', 'field_territorial_subdivision:ignore_case',
      'field_territorial_subdivision:create_term', 'field_territorial_subdivision:source_type',
      'field_type_of_text:create_term', 'field_type_of_text:ignore_case',
      'field_territorial_subdivision', 'field_url:title', 'field_url:attributes',
      'field_court_decision_subdivision', 'field_ecolex_decision_status:source_type',
      'field_ecolex_decision_status', 'field_date_of_modification:to',
      'field_date_of_modification:rrule', 'field_date_of_modification:timezone',
      'field_date_of_entry:to', 'field_date_of_entry:rrule', 'field_date_of_entry:timezone',
      'field_ecolex_decision_status:create_term', 'field_ecolex_decision_status:ignore_case',
      'field_faolex_url:language', 'field_faolex_url:attributes', 'field_faolex_url:title',
      'field_faolex_url', 'field_ecolex_url:language', 'field_ecolex_url:attributes',
      'field_ecolex_url:title', 'field_ecolex_url', 'field_internet_reference_url',
      'field_internet_reference_url:title', 'field_internet_reference_url:attributes',
      'field_internet_reference_url:language', 'field_related_url',
      'field_sorting_date:to', 'field_sorting_date:rrule', 'field_sorting_date:timezone',
      'field_sorting_date', 'field_related_url:language', 'field_related_url:attributes',
      'field_related_url:title', 'field_region', 'field_region:source_type',
      'field_region:create_term', 'field_region:ignore_case', 'path',
    ));
  }

}