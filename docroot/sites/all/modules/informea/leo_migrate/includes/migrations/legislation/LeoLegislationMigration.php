<?php

class LeoLegislationMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'field_abstract', 'field_alternative_record_id', 'field_avaiable_web_site',
      'field_avaiable_web_site:title', 'field_avaiable_web_site:attributes',
      'field_avaiable_web_site:language', 'field_date_of_consolidation', 'field_date_of_original_text',
      'field_ecolex_url', 'field_ecolex_url:title', 'field_ecolex_url:attributes', 'field_ecolex_url:language',
      'field_faolex_url', 'field_faolex_url:title', 'field_faolex_url:attributes', 'field_faolex_url:language',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',
      'field_files', 'field_files:display', 'field_files:description', 'field_files:language',
      'field_original_id', 'title_field', 'title_field:language', 'field_date_of_modification',
      'field_date_of_entry', 'field_entry_into_force_notes', 'field_faolex_id',
      'field_internet_reference_url', 'field_internet_reference_url:title', 'field_internet_reference_url:attributes', 'field_internet_reference_url:language',
      'field_isis_number', 'field_notes', 'field_reference_number', 'field_repealed',
      'field_serial_imprint', 'field_source_language', 'field_sorting_date',
      'field_country',
    ));
    $this->addFieldMapping('field_files:preserve_files')->defaultValue(FALSE);
    $this->addFieldMapping('field_files', 'field_files')->sourceMigration('legislation_files');
    $this->addFieldMapping('field_files:source_dir')->defaultValue('/legislation');
    $this->addFieldMapping('field_files:file_class')->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_amends', 'field_amends')->sourceMigration(array('legislation'));
    $this->addFieldMapping('field_implements', 'field_implements')->sourceMigration(array('legislation'));
    $this->addFieldMapping('field_repeals', 'field_repeals')->sourceMigration(array('legislation'));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid', 'field_abstract:language', 'field_original_id:language',
      'field_date_of_entry:language', 'field_date_of_modification:language', 'field_date_of_original_text:language',
      'field_entry_into_force_notes:language', 'field_faolex_id:language', 'field_territorial_subdivision:language',
      'field_notes:language', 'field_isis_number:language', 'field_reference_number:language',
      'field_serial_imprint:language', 'field_repealed:language', 'field_sorting_date:language',
      'field_source_language:language', 'body:language', 'field_alternative_record_id:language',
      'field_data_source:language', 'field_ecolex_tags:language', 'field_type_of_text:language',
      'field_country:language', 'field_informea_tags:language', 'field_region:language', 'field_date_of_consolidation:language',
      'field_keywords:language',
    ));
    $this->addUnmigratedDestinations(array(
      'field_date_of_original_text:timezone', 'field_date_of_original_text:rrule', 'field_date_of_original_text:to',
      'field_date_of_consolidation:timezone', 'field_date_of_consolidation:rrule', 'field_date_of_consolidation:to',
      'field_date_of_entry:timezone', 'field_date_of_entry:rrule', 'field_date_of_entry:to',
      'field_date_of_modification:timezone', 'field_date_of_modification:rrule', 'field_date_of_modification:to',
      'field_sorting_date:timezone', 'field_sorting_date:rrule', 'field_sorting_date:to',
    ));
  }

  protected function taxonomyFields() {
    return [
      'field_region' => 'geographical_region',
      'field_territorial_subdivision' => 'territorial_subdivision',
      'field_type_of_text' => 'type_of_text',
      'field_sub_file_code' => 'legislation_sub_file_code',
      'field_keywords' => 'keywords',
      'field_ecolex_tags' => 'thesaurus_ecolex',
      'field_informea_tags' => 'thesaurus_informea',
      'field_data_source' => 'data_source',
    ];
  }
}