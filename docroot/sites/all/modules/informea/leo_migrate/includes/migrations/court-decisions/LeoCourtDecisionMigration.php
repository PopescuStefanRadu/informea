<?php


class LeoCourtDecisionMigration extends DrupalNode7Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->addSimpleMappings(array(
      'field_original_id',
      'title_field', 'title_field:language',
      'field_isis_number',
      'field_alternative_record_id',
      'field_date_of_entry',
      'field_date_of_modification',
      'field_country',
      'field_court_name',
      'field_court_decision_subdivision',
      'field_city',
      'field_justices',
      'field_reference_number',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',
      'field_number_of_pages',
      'field_abstract', 'field_abstract:language',
      'field_related_url',
      'field_internet_reference_url', 'field_internet_reference_url:title', 'field_internet_reference_url:attributes', 'field_internet_reference_url:language',
      'field_sorting_date',
      'field_title_of_text_short',
      'field_title_of_text_other',
      'field_title_of_text_short_other',
      'field_available_in',
      'field_ecolex_treaty_raw',
      'field_court_decision_raw',
      'field_instance',
      'field_official_publication',
      'field_source_language',
      'field_files', 'field_files:display', 'field_files:description', 'field_files:language',
      'field_notes',
      'uid',
    ));
    $this->addSimpleMappings(array_keys($this->taxonomyFields()));
    foreach ($this->taxonomyFields() as $f => $voc) {
      $this->addFieldMapping($f . ':source_type')->defaultValue('tid');
    }
    $this->addFieldMapping('field_ref_to_eu_legislation_raw', 'field_legislation_eu_reference');
    $this->addFieldMapping('field_ref_to_nat_legislation_raw', 'field_legislation_national_ref');
    $this->addFieldMapping('field_faolex_reference_raw', 'field_faolex_reference_raw');
    $this->addFieldMapping('field_data_source')->defaultValue('InforMEA');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(MigrateFile::FILE_EXISTS_REUSE);
    $this->addFieldMapping('field_abstract:format')->defaultValue('full_html');

    $this->addFieldMapping('field_date_of_entry:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_date_of_modification:timezone')->defaultValue('Europe/Zurich');
    $this->addFieldMapping('field_sorting_date:timezone')->defaultValue('Europe/Zurich');
  }

  protected function query() {
    $query = parent::query();
    $query->condition('n.uid', 0, '<>');
    return $query;
  }

  protected function taxonomyFields() {
    return [
      'field_territorial_subdivision' => 'territorial_subdivision',
      'field_type_of_text' => 'type_of_text',
      'field_jurisdiction' => 'jurisdiction',
      'field_ecolex_tags' => 'ecolex_subjects',
      'field_ecolex_keywords' => 'thesaurus_ecolex',
      'field_informea_tags' => 'thesaurus_informea',
      'field_ecolex_decision_status' => 'ecolex_decision_status',
      'field_region' => 'geographical_region',
      'field_ecolex_region' => 'ecolex_region',
    ];
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    $files = [];
    if (!empty($row->field_files)) {
      foreach($row->field_files as &$sfid) {
        $q = Database::getConnection('default', 'leo_informea')->query('SELECT a.filename, a.uri, b.language, b.field_files_display 
        FROM file_managed a INNER JOIN field_data_field_files b ON a.fid = b.field_files_fid WHERE a.fid = ' . $sfid);
        $q->execute();
        $file = $q->fetchAssoc();
        $files[] = str_replace('public://', 'http://leo.informea.org/sites/default/files/', $file['uri']);
      }
    }
    $row->field_files = $files;

    // Country
    if (!empty($row->field_country)) {
      $q = Database::getConnection('default', 'leo_informea')->query('SELECT title FROM node WHERE nid = ' . $row->field_country[0]);
      $q->execute();
      $row->field_country = array(db_select('node')->fields(NULL, array('nid'))->condition('title', $q->fetchField())->execute()->fetchField());
    }

    foreach ($this->taxonomyFields() as $f => $voc) {
      if (!empty($row->$f)) {
        $q = Database::getConnection('default', 'leo_informea')->query("SELECT vid FROM taxonomy_vocabulary WHERE machine_name = '" . $voc. "'");
        $q->execute();
        $vid = $q->fetchField();

        $terms = [];
        foreach ($row->$f as $stid) {
          if ($name = $this->get_legacy_term_name($stid, $vid)) {
            $terms[] = $name;
          }
        }
        $row->$f = $terms;
        $this->prepare_term_reference_field($row, $f, $voc);
      }
    }
    // anni
    if ($row->uid == 2) {
      $row->uid = 242;
    }
    // alexandra
    if ($row->uid == 144) {
      $row->uid = 243;
    }
  }

  private function get_legacy_term_name($stid, $vid) {
    $q = Database::getConnection('default', 'leo_informea')->query("SELECT name FROM taxonomy_term_data WHERE vid = $vid AND tid = $stid");
    $q->execute();
    return $q->fetchField();
  }


  /**
   * Map the term names with the existing terms tids.
   * If the vocabulary doesn't contain a term with that name, it will be created.
   *
   * @param $row
   *  Current migration row.
   * @param $field_name
   *  Name of the source field.
   * @param $data
   *  An array containing the terms. Each item needs to be an associative array
   * containing:
   *  - name: original term name
   *  - translations: an array containing language => translation pairs.
   * @param $vocabulary
   *  Vocabulary machine name.
   */
  public function prepare_term_reference_field(&$row, $field_name, $vocabulary) {
    if (empty($row->{$field_name})) {
      return;
    }
    else if (is_array($row->{$field_name})) {
      $tids = array();
      foreach ($row->{$field_name} as $delta => $term_name) {
        if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
          $tids[] = reset($term)->tid;
        }
        else {
          drush_log('WARNING missing term:' . $term_name);
          // $tids[] = elis_migration_create_taxonomy_term($term_name, $vocabulary, array());
        }
      }
      $row->{$field_name} = $tids;
    } else {
      // Handle single-valued fields
      $term_name = $row->{$field_name};
      if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
        $row->{$field_name} = reset($term)->tid;
      }
      else {
        drush_log('WARNING missing term:' . $term_name);
        // $row->{$field_name} = elis_migration_create_taxonomy_term($term_name, $vocabulary, array());
      }
    }
  }
}
