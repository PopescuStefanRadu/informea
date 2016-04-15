<?php

class LeoLegislationMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'field_abstract', 'field_alternative_record_id', 'field_amends', 'field_avaiable_web_site',
      'field_avaiable_web_site:title', 'field_avaiable_web_site:attributes',
      'field_avaiable_web_site:language', 'field_date_of_consolidation', 'field_date_of_original_text',
      'field_ecolex_url', 'field_ecolex_url:title', 'field_ecolex_url:attributes', 'field_ecolex_url:language',
      'field_faolex_url', 'field_faolex_url:title', 'field_faolex_url:attributes', 'field_faolex_url:language',
      'field_files', 'field_files:display', 'field_files:description', 'field_files:language',
      'field_original_id', 'field_original_id:language',
    ));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid', 'field_abstract:language',
    ));
    $this->addUnmigratedDestinations(array(
      'field_date_of_original_text:timezone', 'field_date_of_original_text:rrule', 'field_date_of_original_text:to',
      'field_date_of_consolidation:timezone', 'field_date_of_consolidation:rrule', 'field_date_of_consolidation:to',
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

  function prepareRow($row) {
    parent::prepareRow($row);
    /**
     * @Todo: field_url is multilingual for LEGISLATIONS. FIX THIS
     * Error:
     * Illegal offset type
     * File modules/contrib/link/link.migrate.inc, line 112
     */
//    if (!empty($row->{'field_url:language'})) {
//      $row->{'field_url:language'} = reset($row->{'field_url:language'});
//    }
  }
}