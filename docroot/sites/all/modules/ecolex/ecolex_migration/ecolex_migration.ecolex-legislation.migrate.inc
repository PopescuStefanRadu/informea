<?php

class EcolexLegislationMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'legId' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Entity original ID from the Ecolex',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->source = new EcolexLegislationMigrateSource($arguments['source_url_pattern']);
    $this->destination = new MigrateDestinationNode('legislation');

    // language
    $this->addFieldMapping('field_alternative_record_id', 'id');
    $this->addFieldMapping('field_original_id', 'legId');
    $this->addFieldMapping('field_faolex_id', 'legId');

    $this->addFieldMapping('field_sorting_date', 'legYear');
    $this->addFieldMapping('field_sorting_date:timezone')->defaultValue('Europe/Zurich');

    $this->addFieldMapping('field_date_of_original_text', 'legOriginalYear');
    $this->addFieldMapping('field_date_of_original_text:timezone')->defaultValue('Europe/Zurich');

    $this->addFieldMapping('field_type_of_text', 'legType_en');
    $this->addFieldMapping('field_type_of_text:source_type')->defaultValue('tid');

    $this->addFieldMapping('title', 'legTitle');
    $this->addFieldMapping('field_title_abbreviation', 'legLongTitle');
    $this->addFieldMapping('body', 'legAbstract');
    $this->addFieldMapping('field_country', 'legCountry_iso');
    $this->addFieldMapping('field_entry_into_force_notes', 'legEntryIntoForce');

    $this->addFieldMapping('field_ecolex_region', 'legGeoArea_en');
    $this->addFieldMapping('field_ecolex_region:source_type')->defaultValue('tid');

    // $this->addFieldMapping('field_source_language', 'legLanguage_code');

    $this->addFieldMapping('field_files', 'legLinkToFullText');
    $this->addFieldMapping('field_files:file_replace')->defaultValue(FILE_EXISTS_OVERWRITE);

    $this->addFieldMapping('field_url', 'legRelatedWebSite');

    $this->addFieldMapping('field_ecolex_legislation_status', 'legStatus');
    $this->addFieldMapping('field_ecolex_legislation_status:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_ecolex_tags', 'legSubject_en');
    $this->addFieldMapping('field_ecolex_tags:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_territorial_subdivision', 'legTerritorialSubdivision');
    $this->addFieldMapping('field_territorial_subdivision:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_amends', 'legAmends');
    $this->addFieldMapping('field_implements', 'legImplement');
    $this->addFieldMapping('field_repeals', 'legRepeals');

    $this->addFieldMapping('field_ecolex_keywords', 'legKeyword_en');
    $this->addFieldMapping('field_ecolex_keywords:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_ecolex_url', 'ecolex_url');
    $this->addFieldMapping('field_faolex_url', 'faolex_url');
    // $this->addFieldMapping('field_date_of_modification', 'legModificationDate');
    // $this->addFieldMapping('field_date_of_entry', 'legEntryDate');

    $this->addFieldMapping('field_data_source')->defaultValue('ECOLEX/FAOLEX');
    $this->addFieldMapping('comment')->defaultValue(FALSE);
    $this->addFieldMapping('uid')->defaultValue(0);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote')->defaultValue(0);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(0);
    $this->addFieldMapping('language')->defaultValue('en');

    $this->addUnmigratedSources(array());
    $this->addUnmigratedDestinations(array(
      'nid', 'created', 'changed', 'log', 'tnid', 'translate', 'revision_uid', 'path',
      'is_new', 'body:summary', 'body:format', 'body:language',
      'field_sorting_date:to', 'field_sorting_date:rrule',
      'field_abstract',
      'field_date_of_original_text:rrule',
      'metatag_title', 'metatag_description', 'metatag_abstract', 'metatag_keywords',
      'metatag_robots', 'metatag_news_keywords', 'metatag_standout', 'metatag_rating',
      'metatag_referrer', 'metatag_generator', 'metatag_rights', 'metatag_image_src',
      'metatag_canonical', 'metatag_shortlink', 'metatag_publisher', 'metatag_author',
      'metatag_original-source', 'metatag_prev', 'metatag_next', 'metatag_content-language',
      'metatag_geo.position', 'metatag_geo.placename', 'metatag_geo.region',
      'metatag_icbm', 'metatag_refresh', 'metatag_revisit-after', 'metatag_pragma',
      'metatag_cache-control', 'metatag_expires',
      'field_date_of_original_text:to',
      'field_ecolex_tags:create_term', 'field_ecolex_tags:ignore_case',
      'field_type_of_text:create_term', 'field_type_of_text:ignore_case',
      'field_url:title', 'field_url:attributes', 'field_url:language',
      'field_date_of_entry', 'field_date_of_entry:timezone', 'field_date_of_entry:rrule',
      'field_date_of_entry:to',
      'field_date_of_modification', 'field_date_of_modification:timezone',
      'field_date_of_modification:rrule', 'field_date_of_modification:to',
      'field_internet_reference_url', 'field_internet_reference_url:title',
      'field_internet_reference_url:attributes', 'field_internet_reference_url:language',
      'field_notes',
      'field_reference_number',
      'field_repealed',
      'field_serial_imprint',
      'field_sub_file_code', 'field_sub_file_code:source_type', 'field_sub_file_code:create_term', 'field_sub_file_code:ignore_case',
      'field_territorial_subdivision:create_term', 'field_territorial_subdivision:ignore_case',
      'field_informea_tags', 'field_informea_tags:source_type', 'field_informea_tags:create_term', 'field_informea_tags:ignore_case',
      'field_region', 'field_region:source_type', 'field_region:create_term', 'field_region:ignore_case',
      'field_data_source:source_type', 'field_data_source:create_term', 'field_data_source:ignore_case',
      'field_files:file_class', 'field_files:language', 'field_files:preserve_files', 'field_files:destination_dir', 'field_files:destination_file',
      'field_files:source_dir', 'field_files:urlencode', 'field_files:description', 'field_files:display',
      'field_ecolex_region:create_term', 'field_ecolex_region:ignore_case',
      'field_ecolex_legislation_status:create_term', 'field_ecolex_legislation_status:ignore_case',
      'field_title_abbreviation:language',
      'field_ecolex_keywords:create_term', 'field_ecolex_keywords:ignore_case',
      'field_avaiable_web_site', 'field_avaiable_web_site:title',
      'field_avaiable_web_site:attributes', 'field_avaiable_web_site:language',
      'field_date_of_consolidation', 'field_date_of_consolidation:timezone',
      'field_date_of_consolidation:rrule', 'field_date_of_consolidation:to',
      'field_isis_number',
      'field_keywords', 'field_keywords:source_type', 'field_keywords:create_term', 'field_keywords:ignore_case',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
    // Dates
    if (!empty($row->legYear) && strlen($row->legYear) == 4) {
      $row->legYear = $row->legYear . '-01-01';
    }
    if (!empty($row->legOriginalYear) && strlen($row->legOriginalYear) == 4) {
      $row->legOriginalYear = $row->legOriginalYear . '-01-01';
    }
//    if (!empty($row->legModificationDate) && strlen($row->legModificationDate) == 4) {
//      $row->legModificationDate = $row->legModificationDate . '-01-01';
//    }
    // 'title_field',
    // 'title_field:language',


    // Taxonomies
    $this->prepare_term_reference_field_multilingual($row, 'legType', 'type_of_text');
    $this->prepare_term_reference_field_multilingual($row, 'legGeoArea', 'ecolex_region');
    $this->prepare_term_reference_field_multilingual($row, 'legSubject', 'ecolex_subjects');
    $this->prepare_term_reference_field_multilingual($row, 'legKeyword', 'thesaurus_ecolex');
    $this->prepare_term_reference_field($row, 'legStatus', 'ecolex_legislation_status');
    $this->prepare_term_reference_field($row, 'legTerritorialSubdivision', 'territorial_subdivision');

    // Entity references

    if ($country = country_load_by_iso($row->legCountry_iso)) {
      $row->legCountry_iso = $country->nid;
    }
    else {
      $row->legCountry_iso = NULL;
    }

    if (!empty($row->legAmends)) {
      $values = array();
      foreach($row->legAmends as $faolexId) {
        if ($nid = ecolex_legislation_load_nid_by_faolexid($faolexId)) {
          $values[] = $nid;
        }
      }
      $row->legAmends = $values;
    }

    if (!empty($row->legImplement)) {
      $values = array();
      foreach($row->legImplement as $faolexId) {
        if ($nid = ecolex_legislation_load_nid_by_faolexid($faolexId)) {
          $values[] = $nid;
        }
      }
      $row->legImplement = $values;
    }

    if (!empty($row->legRepeals)) {
      $values = array();
      foreach($row->legRepeals as $faolexId) {
        if ($nid = ecolex_legislation_load_nid_by_faolexid($faolexId)) {
          $values[] = $nid;
        }
      }
      $row->legRepeals = $values;
    }

    return $this->validateRow($row);
  }

  public function validateRow($row) {
    return !empty($row->legTitle);
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
          $tids[] = elis_migration_create_taxonomy_term($term_name, $vocabulary, array());
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
        $row->{$field_name} = elis_migration_create_taxonomy_term($term_name, $vocabulary, array());
      }
    }
  }


  /**
   * Map the term names with the existing terms tids.
   * If the vocabulary doesn't contain a term with that name, it will be created.
   *
   * @param $row
   *  Current migration row.
   * @param $field_name_base
   *  Name of the source field.
   *
   * @param $vocabulary
   *  Vocabulary machine name.
   */
  function prepare_term_reference_field_multilingual(&$row, $field_name_base, $vocabulary) {
    if (empty($row->{$field_name_base . '_en'})) {
      return;
    }
    else if (is_array($row->{$field_name_base . '_en'})) {
      $tids = array();
      foreach ($row->{$field_name_base . '_en'} as $delta => $term_name) {
        if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
          $tids[] = reset($term)->tid;
        }
        else {
          $translations = array();
          if (!empty($row->{$field_name_base . '_fr'}[$delta])) {
            $translations['fr'] = $row->{$field_name_base . '_fr'}[$delta];
          }
          if (!empty($row->{$field_name_base . '_es'}[$delta])) {
            $translations['es'] = $row->{$field_name_base . '_es'}[$delta];
          }
          $tids[] = elis_migration_create_taxonomy_term($term_name, $vocabulary, $translations);
        }
      }
      $row->{$field_name_base . '_en'} = $tids;
    } else {
      // Handle single-valued fields
      $term_name = $row->{$field_name_base . '_en'};
      if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
        $row->{$field_name_base . '_en'} = reset($term)->tid;
      }
      else {
        $translations = array();
        if (!empty($row->{$field_name_base . '_fr'})) {
          $translations['fr'] = $row->{$field_name_base . '_fr'};
        }
        if (!empty($row->{$field_name_base . '_es'})) {
          $translations['es'] = $row->{$field_name_base . '_es'};
        }
        $row->{$field_name_base . '_en'} = elis_migration_create_taxonomy_term($term_name, $vocabulary, $translations);
      }
    }
  }
}


class EcolexLegislationMigrateSource extends MigrateSource {

  private $url_pattern = NULL;

  public $totalCount = 0;
  public $currentCount = 0;
  public $currentPage = 0;
  public $pagination = 100;
  protected $data = array();

  public function __construct($source_url_pattern) {
    parent::__construct(array());
    $this->url_pattern = $source_url_pattern;
    $this->computeCount();
  }

  public function __toString() {
    return sprintf('Extract legislation from ECOLEX Solr');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id'                       => 'Primary Key',
      'legId'                    => 'FAOLEX Identifier',
      'legYear'                  => 'Date of text',
      'legOriginalYear'          => 'Consolidation date',
      'legType_en'               => 'Type of document (Legisation, Regulation, Miscellaneous)',
      'legTitle'                 => 'Short title',
      'legLongTitle'             => 'Full title',
      'legAbstract'              => 'Abstract',
      'legCountry_iso'           => 'Country ISO code',
      'legEntryIntoForce'        => 'Notes about enter into force',
      'legGeoArea_en'            => 'Geographical area, multivalued',
      // 'legBasin_en'              => 'Basin geographical area',
      // 'legLanguage_code'           => 'Document language',
      'legLinkToFullText'        => 'Link to document file',
      // 'legModificationDate'      => 'Modification date',
      'legRelatedWebSite'        => 'Related website',
      'legSource'                => 'Source of the data input (ie. scanned copy)',
      'legStatus'                => 'Status (i.e. in force)',
      'legSubject_en'            => 'ECOLEX subject',
      'legTerritorialSubdivision' => 'Territorial subdivision',
      'legAmends'                => 'IDs of the amended legislation',
      'legImplement'             => 'IDs of the implemented legislation',
      'legRepeals'               => 'IDs of the repealed legislation',
      'legKeyword_en'            => 'Tagging keywords',
      'ecolex_url'                  => 'Link to ECOLEX',
      'faolex_url'                  => 'Link to FAOLEX',
      // 'legEntryDate'             => 'Date when record entered into the system',
      // 'legTypeCode'              => 'Codification for type of document',
      // 'legSearchDate'            => '',
    );
  }


  /**
   * Return the number of available source records.
   */
  public function computeCount() {
    if ($str = elis_consumer_http_request($this->url_pattern . '&rows=0', array('Accept' => 'application/json'))) {
      if ($json = json_decode($str)) {
        $this->totalCount = $json->response->numFound;
      }
    }
    return $this->totalCount;
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    $this->data = array();
    $this->currentPage = 0;
    $this->currentCount = 0;
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    $next_call_count = $this->currentPage * $this->pagination;
    if ($this->currentCount == $this->totalCount) {
      return NULL;
    }
    if ($this->currentCount == $next_call_count && $next_call_count < $this->totalCount) {
      $start = $this->currentPage * $this->pagination;
      if ($str = elis_consumer_http_request($this->url_pattern . '&rows=' . $this->pagination . '&start=' . $start, array('Accept' => 'application/json'))) {
        if ($json = json_decode($str)) {
          $this->data = $json->response->docs;
          $this->currentPage++;
        }
      }
    }
    // TODO Messages in case of empty data / failed call etc.
    $item = NULL;
    if (count($this->data)) {
      $item = current($this->data);
      next($this->data);
      $this->currentCount++;
    }
    return $item;
  }
}
