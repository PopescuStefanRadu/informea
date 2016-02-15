<?php

define('DRUPAL_TYPE_TREATY', 'treaty');

class ImeaTreatyElisMigration extends TreatyElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_TREATY);

    $this->addFieldMapping('field_original_id', 'Recid');
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
    $this->addFieldMapping('field_available_in', 'availableIn');
    $this->addFieldMapping('field_entry_into_force', 'entryIntoForceDate');
    // @ToDo: create terms programmatically or map them with the existing ones
    $this->addFieldMapping('field_field_of_application', 'fieldOfApplication');
    $this->addFieldMapping('field_field_of_application:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_obsolete', 'obsolete');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('field_title_abbreviation', 'titleAbbreviation');
    $this->addFieldMapping('field_title_abbreviation:language', 'titleAbbreviation_languages');
    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:source_type')->defaultValue('tid');
//    $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
//    $this->addFieldMapping('field_jurisdiction:create_term')->defaultValue(FALSE);
//    $this->addFieldMapping('field_jurisdiction:ignore_case')->defaultValue(TRUE);
//    $this->addFieldMapping('field_region', 'region');
//    $this->addFieldMapping('field_region:create_term')->defaultValue(FALSE);
//    $this->addFieldMapping('field_region:ignore_case')->defaultValue(TRUE);
    $this->addFieldMapping('field_place_of_adoption', 'placeOfAdoption');
    // @ToDo: map countries by name
    $this->addFieldMapping('field_country', 'depository');
    $this->addFieldMapping('field_official_publication', 'officialPublication');
    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_related_website', 'relatedWebSite');
    $this->addFieldMapping('field_treaty_text_url', 'linkToFullText');
    // @ToDo: map treaties by RecID
    $this->addFieldMapping('field_amends_treaty', 'amendsTreaty');
    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:source_type')->defaultValue('tid');
    $this->addUnmigratedSources(array(
      'sortFieldOfApplication', 'languageOfDocument',
      'languageOfTranslation', 'dateOfText', 'searchDate', 'parties', 'abstract'
    ));

    $this->addUnmigratedDestinations(array(
      'created', 'changed', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'field_data_source', 'field_data_source:source_type', 'field_data_source:create_term',
      'field_data_source:ignore_case', 'field_depositary',
      'field_ecolex_url:title', 'field_ecolex_url:attributes',
      'field_date_of_entry:timezone', 'field_date_of_entry:rrule', 'field_date_of_entry:to',
      'field_entry_into_force:timezone', 'field_entry_into_force:rrule', 'field_entry_into_force:to',
      'field_date_of_modification:timezone', 'field_date_of_modification:rrule',
      'field_date_of_modification:to', 'body:summary', 'body:format', 'field_abstract',
      'field_alternative_record_id', 'field_cited_treaties', 'field_ecolex_url',
      'field_ecolex_url:language', 'field_faolex_url', 'field_faolex_url:title',
      'field_faolex_url:attributes', 'field_faolex_url:language',
      'field_internet_reference',
      'field_internet_reference:language', 'field_is_protocol',
      'field_jurisdiction:source_type', 'field_logo', 'field_logo:file_class',
      'field_logo:language', 'field_logo:preserve_files', 'field_logo:destination_dir',
      'field_logo:destination_file', 'field_logo:file_replace', 'field_logo:source_dir',
      'field_logo:urlencode', 'field_logo:alt', 'field_logo:title', 'field_number_of_pages',
      'field_odata_identifier', 'field_official_name', 'field_official_name:language',
      'field_parent_treaty', 'field_primary', 'field_primary_topic', 'field_primary_topic:source_type',
      'field_primary_topic:create_term', 'field_primary_topic:ignore_case', 'field_ratification_xml_url',
      'field_ratification_xml_url:title', 'field_ratification_xml_url:attributes',
      'field_ratification_xml_url:language', 'field_secondary_topic', 'field_secondary_topic:source_type',
      'field_secondary_topic:create_term', 'field_secondary_topic:ignore_case', 'field_ecolex_tags:create_term', 'field_ecolex_tags:ignore_case',
      'field_type_of_text:create_term', 'field_type_of_text:ignore_case',
      'field_treaty_parties_url', 'field_treaty_parties_url:title', 'field_treaty_parties_url:attributes',
      'field_treaty_parties_url:language', 'field_treaty_text_url:title', 'field_treaty_text_url:attributes',
      'field_treaty_text_url:language', 'body', 'body:language',
      'field_treaty_website_url', 'field_treaty_website_url:title', 'field_treaty_website_url:attributes',
      'field_treaty_website_url:language', 'field_field_of_application:create_term', 'field_field_of_application:ignore_case',
      'field_informea_tags', 'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_informea_tags:ignore_case', 'field_keywords:create_term', 'field_keywords:ignore_case', 'field_region:source_type',
      'field_sorting_order', 'field_related_url', 'field_related_url:title', 'field_related_url:attributes',
      'field_related_url:language', 'field_treaty_article', 'field_treaty_article_paragraph',
      'field_online_course_link', 'field_online_course_link:title', 'field_online_course_link:attributes',
      'field_online_course_link:language', 'field_mea_topic', 'field_mea_topic:source_type',
      'field_mea_topic:create_term', 'field_mea_topic:ignore_case', 'field_un_treaty_database_link',
      'field_un_treaty_database_link:title', 'field_un_treaty_database_link:attributes',
      'field_un_treaty_database_link:language', 'field_has_api_action_plans',
      'field_has_api_decisions', 'field_has_api_national_reports', 'field_treaty_has_parties_from_un',
      'field_user_owners', 'field_sorting_date', 'field_sorting_date:timezone',
      'field_sorting_date:rrule', 'field_sorting_date:to', 'field_treaty_decisions_url',
      'field_treaty_decisions_url:title', 'field_treaty_decisions_url:attributes',
      'field_treaty_decisions_url:language', 'field_treaty_plans_url', 'field_treaty_plans_url:title',
      'field_treaty_plans_url:attributes', 'field_treaty_plans_url:language',
      'field_treaty_protocols_url', 'field_treaty_protocols_url:title', 'field_treaty_protocols_url:attributes',
      'field_treaty_protocols_url:language', 'field_treaty_reports_url', 'field_treaty_reports_url:title',
      'field_treaty_reports_url:attributes', 'field_treaty_reports_url:language', 'path',
    ));
  }

  public function prepare($entity, $row) {
    parent::prepare($entity, $row);
    if (!empty($row->linkToFullText)) {
      $this->fix_link_field_multilingual_data($entity, 'field_treaty_text_url', $row->linkToFullText, $row->linkToFullText_languages, 'url');
    }
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    $this->prepare_term_reference_field($row, 'keyword', 'keywords');
    $this->prepare_term_reference_field($row, 'subject', 'thesaurus_ecolex');
    $this->prepare_term_reference_field($row, 'typeOfText', 'type_of_text');
    $this->prepare_term_reference_field($row, 'fieldOfApplication', 'field_of_application');
  }

}