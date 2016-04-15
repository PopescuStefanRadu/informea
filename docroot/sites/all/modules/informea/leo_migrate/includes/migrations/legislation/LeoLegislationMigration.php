<?php

class LeoLegislationMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
    ));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
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