<?php

define('DRUPAL_TYPE_TREATY', 'treaty');

class ElisTreatyMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->source = new TreatyElisMigrateSource($arguments['source_url_pattern'], $arguments['xml_encoding']);
    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_TREATY);

    $this->addFieldMapping('field_original_id', 'Recid');
    $this->addFieldMapping('title', 'title_english');
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
    $this->addFieldMapping('field_field_of_application', 'fieldOfApplication');
    $this->addFieldMapping('field_entry_into_force:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_field_of_application:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_obsolete', 'obsolete');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_entry:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_sorting_date', 'dateOfText');
    $this->addFieldMapping('field_sorting_date:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('field_date_of_modification:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_title_abbreviation', 'titleAbbreviation');
    $this->addFieldMapping('field_title_abbreviation:language', 'titleAbbreviation_languages');
    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
    $this->addFieldMapping('field_jurisdiction:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ecolex_region', 'region');
    $this->addFieldMapping('field_ecolex_region:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_place_of_adoption', 'placeOfAdoption');
    $this->addFieldMapping('field_depositary', 'depository');
    $this->addFieldMapping('field_official_publication', 'officialPublication');
    $this->addFieldMapping('field_ecolex_keywords', 'keyword');
    $this->addFieldMapping('field_ecolex_keywords:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_keywords:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_related_website', 'relatedWebSite');
    $this->addFieldMapping('field_treaty_text_url', 'linkToFullText');
    $this->addFieldMapping('field_treaty_text_url:language', 'linkToFullText_languages');
    $this->addFieldMapping('field_amends_treaty', 'amendsTreaty');
    $this->addFieldMapping('field_amends_treaty_t', 'amendsTreatyText');
    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_abstract', 'abstract');
    $this->addFieldMapping('field_abstract:language', 'abstract_languages');

    $this->addUnmigratedSources(array(
      'sortFieldOfApplication', 'languageOfDocument',
      'languageOfTranslation', 'dateOfText', 'searchDate', 'parties',
      'linkToFullText_languages',
    ));

    $this->addUnmigratedDestinations(array(
      'created', 'changed', 'log', 'tnid', 'translate', 'revision_uid', 'is_new',
      'field_data_source', 'field_data_source:source_type', 'field_data_source:create_term',
      'field_data_source:ignore_case',
      'field_ecolex_url:title', 'field_ecolex_url:attributes',
      'field_date_of_entry:rrule', 'field_date_of_entry:to',
      'field_entry_into_force:rrule', 'field_entry_into_force:to',
      'field_date_of_modification:rrule', 'field_date_of_modification:to',
      'body:summary', 'body:format',
      'field_alternative_record_id', 'field_cited_treaties', 'field_ecolex_url',
      'field_ecolex_url:language', 'field_faolex_url', 'field_faolex_url:title',
      'field_faolex_url:attributes', 'field_faolex_url:language',
      'field_internet_reference',
      'field_internet_reference:language', 'field_is_protocol',
      'field_jurisdiction:create_term', 'field_jurisdiction:ignore_case', 'field_logo', 'field_logo:file_class',
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
      'field_treaty_parties_url:language', 'field_treaty_text_url:title', 'field_treaty_text_url:attributes', 'body', 'body:language',
      'field_treaty_website_url', 'field_treaty_website_url:title', 'field_treaty_website_url:attributes',
      'field_treaty_website_url:language', 'field_field_of_application:create_term', 'field_field_of_application:ignore_case',
      'field_informea_tags', 'field_informea_tags:source_type', 'field_informea_tags:create_term',
      'field_informea_tags:ignore_case', 'field_keywords:create_term', 'field_keywords:ignore_case',
      'field_region:create_term', 'field_region:ignore_case',
      'field_sorting_order', 'field_related_url', 'field_related_url:title', 'field_related_url:attributes',
      'field_related_url:language', 'field_treaty_article', 'field_treaty_article_paragraph',
      'field_online_course_link', 'field_online_course_link:title', 'field_online_course_link:attributes',
      'field_online_course_link:language', 'field_mea_topic', 'field_mea_topic:source_type',
      'field_mea_topic:create_term', 'field_mea_topic:ignore_case', 'field_un_treaty_database_link',
      'field_un_treaty_database_link:title', 'field_un_treaty_database_link:attributes',
      'field_un_treaty_database_link:language', 'field_has_api_action_plans',
      'field_has_api_decisions', 'field_has_api_national_reports', 'field_treaty_has_parties_from_un',
      'field_user_owners',
      'field_sorting_date:rrule', 'field_sorting_date:to', 'field_treaty_decisions_url',
      'field_treaty_decisions_url:title', 'field_treaty_decisions_url:attributes',
      'field_treaty_decisions_url:language', 'field_treaty_plans_url', 'field_treaty_plans_url:title',
      'field_treaty_plans_url:attributes', 'field_treaty_plans_url:language',
      'field_treaty_protocols_url', 'field_treaty_protocols_url:title', 'field_treaty_protocols_url:attributes',
      'field_treaty_protocols_url:language', 'field_treaty_reports_url', 'field_treaty_reports_url:title',
      'field_treaty_reports_url:attributes', 'field_treaty_reports_url:language', 'path',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    if (property_exists($row, 'depository')) {
      /** @var stdClass $country */
      if ($country = country_get_by_name($row->coutry)) {
        $row->country = $country->nid;
      }
      else {
        //@todo: error
        $row->country = NULL;
      }
    }
    if (!empty($row->amendsTreaty)) {
      // Migration needs to run twice so this could work for all nodes.
      $op = is_array($row->amendsTreaty) ? 'IN' : '=';
      $q = db_select('migrate_map_elis_treaties', 'm')
        ->fields('m', array('destid1'))
        ->condition('m.sourceid1', $row->amendsTreaty, $op);
      $row->amendsTreaty = $q->execute()->fetchCol();
    }
    return $this->validateRow($row);
  }

  public function validateRow($row) {
    return !empty($row->title_english);
  }
}
