<?php

define('DRUPAL_TYPE_TREATY', 'treaty');

class ImeaTreatyElisMigration extends TreatyElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_TREATY);

    $this->addFieldMapping('title', 'titleOfText');
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('body', 'abstract');
    $this->addFieldMapping('field_available_in', 'availableIn');
    $this->addFieldMapping('field_entry_into_force', 'entryIntoForceDate');
    $this->addFieldMapping('field_field_of_application', 'fieldOfApplication');
    // @ToDo: create terms programmatically or map them with the existing ones
    $this->addFieldMapping('field_field_of_application:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_field_of_application:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_obsolete', 'obsolete');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('field_title_abbreviation', 'titleAbbreviation');
    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_type_of_text:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
    $this->addFieldMapping('field_jurisdiction:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_jurisdiction:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_region', 'region');
    $this->addFieldMapping('field_region:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_region:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_place_of_adoption', 'placeOfAdoption');
    // @ToDo: map countries by name
    $this->addFieldMapping('field_country', 'depository');
    $this->addFieldMapping('field_official_publication', 'officialPublication');
    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_keywords:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_related_website', 'relatedWebSite');
    $this->addFieldMapping('field_treaty_text_url', 'linkToFullText');
    // @ToDo: map treaties by RecID
    $this->addFieldMapping('field_amends_treaty', 'amendsTreaty');
    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_ecolex_tags:ignore_case')->defaultValue(TRUE);
    $this->addUnmigratedSources(array(
      'sortFieldOfApplication', 'languageOfDocument',
      'languageOfTranslation', 'dateOfText', 'searchDate', 'party',
    ));

    $this->addUnmigratedDestinations(array(
      'created', 'changed', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'field_data_source', 'field_data_source:source_type', 'field_data_source:create_term',
      'field_data_source:ignore_case', 'field_depositary',
      'field_ecolex_tags:source_type', 'field_ecolex_url:title', 'field_ecolex_url:attributes',
      'field_date_of_entry:timezone', 'field_date_of_entry:rrule', 'field_date_of_entry:to',
      'field_entry_into_force:timezone', 'field_entry_into_force:rrule', 'field_entry_into_force:to',
      'field_date_of_modification:timezone', 'field_date_of_modification:rrule',
      'field_date_of_modification:to',

    ));
  }

}