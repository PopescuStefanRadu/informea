<?php

class EcolexLegislationMigrate extends Migration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->arguments   = $arguments;
    $this->description = 'Import ECOLEX legislation from XML web service (files)';
    $data_dir          = $arguments['data_dir'];
    $this->source      = new EcolexLegislationMigrateSource($data_dir, array(// 'skip_count' => TRUE,
      )
    );
    $this->map         = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'RecId field remote primary key',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode(
      'legislation',
      array('language' => 'en', 'text_format' => 'full_html')
    );

    $this->addFieldMapping('field_original_id', 'id');
    $this->addFieldMapping('field_isis_number', 'ISIS_MFN');
    $this->addFieldMapping('field_faolex_id', 'FaolexId');
    $this->addFieldMapping('field_date_of_entry', 'Date_of_Entry');
    $this->addFieldMapping('field_date_of_modification', 'Date_of_Modification');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('field_region', 'region');
    $this->addFieldMapping('field_territorial_subdivision', 'Territorial_Subdivision');
    // $this->addFieldMapping('', 'basin');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'Title_of_Text');

    $this->addFieldMapping('field_sorting_date', 'Date_of_Text');
    $this->addFieldMapping('field_date_of_original_text', 'Date_of_original_Text');
    $this->addFieldMapping('field_date_of_consolidation', 'Date_of_Consolidation');
    $this->addFieldMapping('field_entry_into_force_notes', 'Entry_into_Force');
    // $this->addFieldMapping('', 'searchDate');
    $this->addFieldMapping('field_avaiable_web_site', 'Related_Web_Site');
    $this->addFieldMapping('field_internet_reference_url', 'Internet_Reference');
    $this->addFieldMapping('field_url', 'link_to_full_text');

    $this->addFieldMapping('field_type_of_text', 'Type_of_Text');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_type_of_text:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_abstract', 'Abstract');
    $this->addFieldMapping('field_notes', 'Comment');
    $this->addFieldMapping('field_sub_file_code', 'Sub_file_code');

    // @todo: Integers instead of real terms.
    // $this->addFieldMapping('field_keywords', 'keyword');
    // $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);

    // $this->addFieldMapping('', 'International_Organizations');
    $this->addFieldMapping('field_source_language', 'Doc_Language');
    $this->addFieldMapping('field_repealed', 'Repealed');

    // $this->addFieldMapping('', 'Record_Language');
    $this->addFieldMapping('field_serial_imprint', 'Serial_Imprint');
    $this->addFieldMapping('field_reference_number', 'Publication_reference');
  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return 'EcolexLegislation';
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    // Map also regions from countries
    if (!empty($row->country)) {
      if (empty($row->region)) {
        $row->region = array();
      }
      $countries = $row->country;
      if (!is_array($row->country)) {
        $countries = array($row->country);
      }
      $regions = country_get_regions_from_country($countries);
      foreach ($regions as $region) {
        $row->region[] = $region->name;
      }
    }

    return TRUE;
  }

  /**
   * Called by destination right before saving.
   *
   * @param object $entity
   *   Entity to save
   * @param object $row
   *   Source row
   */
  public function prepare($entity, $row) {
    $migration   = Migration::currentMigration();
    $languages   = array_keys(language_list());
    $entity_type = $migration->getDestination()->getEntityType();

    $entity->field_ecolex_url['en'][0]['url'] = 'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=documents&id=' . $row->id;
    $entity->field_faolex_url['en'][0]['url'] = 'http://faolex.fao.org/cgi-bin/faolex.exe?database=faolex&search_type=link&table=result&lang=eng&format_name=@ERALL&rec_id=' . $row->ISIS_MFN;

    if (!empty($row->Doc_Language)) {
      $entity->field_source_language[LANGUAGE_NONE][0]['value'] = $row->Doc_Language;
    }

    $translation_handler  = entity_translation_get_handler($entity_type, $entity);
    $entity->translations = $translation_handler->getTranslations();
    $entity->language     = 'en';
    foreach ($languages as $language) {
      $has_translation = FALSE;

      if ($has_translation) {
        MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
      }
    }
  }
}


class EcolexLegislationMigrateSource extends EcolexMigrateSource {

  protected $data_dir;
  protected $parsed = FALSE;
  protected $data = array();
  protected $newestItemDate = NULL;

  /**
   * {@inheritdoc}
   */
  public function __construct($data_dir, array $options = array()) {
    parent::__construct($options);
    $this->data_dir = $data_dir;
    //$this->newestItemDate = $this->getNewestItemDate();
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() {
    return "Extract treaties from ECOLEX XML in {$this->data_dir}";
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id'                          => 'Primary Key',
      'ISIS_MFN'                    => 'ISIS number',
      'FaolexId'                    => 'FAOLEX Identifier',
      'Date_of_Entry'               => 'Date of entry into the system',
      'Date_of_Modification'        => 'Date of last modification',
      'country'                     => 'Related country',
      'Territorial_Subdivision'     => 'Territory',
      'basin'                       => '@todo',
      'Title_of_Text'               => 'Title',
      'title'                       => 'Title in english',
      'Date_of_Text'                => 'Date of text',
      'Date_of_original_Text'       => 'Date of original text',
      'Date_of_Consolidation'       => 'Date of consolidation',
      'Entry_into_Force'            => 'Entry into force notes',
      'searchDate'                  => '@todo',
      'Related_Web_Site'            => 'Related web site',
      'Internet_Reference'          => 'Link to record',
      'link_to_full_text'           => 'Link to document',
      'Type_of_Text'                => 'Type of legislation text',
      'Abstract'                    => 'Abstract text',
      'Comment'                     => 'Comments / Notes',
      'Sub_file_code'               => 'Sub-file code (?)',
      'keyword'                     => '@todo - now are integers in XML',
      'International_Organizations' => '@todo',
      'Record_Language'             => '@todo',
      'Doc_Language'                => 'Document language',
      'Repealed'                    => 'Repealed (Y/N)',
      'Serial_Imprint'              => 'Serial imprint number',
      'Publication_reference'       => 'Reference to publication page/no.',
      'region'                      => 'Automatically computed from country',
    );
  }

  /**
   * Query the remote source and pull the data.
   */
  protected function readData() {
    if ( ! $this->parsed) {
      $this->data   = array();
      $this->parsed = TRUE;
      $files        = file_scan_directory($this->data_dir, '/.*/');
      $processed    = 0;
      foreach ($files as $i => $file) {
        try {
          $docs = @simplexml_load_file($file->uri);
          if ( ! $docs) {
            continue;
          }
          foreach ($docs as $doc) {
            $processed++;
            if ($processed % 5000 == 0) {
              $this->setMessage("Processed $processed records");
            }
            $id = (string) $doc->id;

            $ob = new stdClass();
            // Copy all attributes
            $ob->id                   = $id;
            $ob->ISIS_MFN             = (string) $doc->ISIS_MFN;
            $ob->FaolexId             = (string) $doc->FaolexId;
            $ob->Date_of_Entry        = (string) $doc->Date_of_Entry;
            $ob->Date_of_Modification = (string) $doc->Date_of_Modification;

            $iso3 = (string) $doc->country;
            if ( ! empty( $iso3 )) {
              if ($country_id = wp_migration_get_country_id($iso3)) {
                $ob->country = $country_id;
              }
              else {
                $this->setMessage("Cannot match ISO code: " . $iso3);
              }
            }

            $ob->Territorial_Subdivision = (string) $doc->Territorial_Subdivision;
            $ob->basin                   = (string) $doc->basin;

            $ob->Title_of_Text = (string) $doc->Title_of_Text;
            $ob->title         = (string) $doc->Title_of_Text;

            $ob->Date_of_Text          = (string) $doc->Date_of_Text;
            $ob->Date_of_original_Text = (string) $doc->Date_of_original_Text;
            $ob->Date_of_Consolidation = (string) $doc->Date_of_Consolidation;
            $ob->Entry_into_Force      = (string) $doc->Entry_into_Force;
            $ob->searchDate            = (string) $doc->searchDate;
            $ob->Related_Web_Site      = (string) $doc->Related_Web_Site;
            $ob->Internet_Reference    = (string) $doc->Internet_Reference;

            $filename = (string) $doc->link_to_full_text;
            if (strpos($filename, '.pdf')) {
              $ob->link_to_full_text = 'http://faolex.fao.org/docs/pdf/' . $filename;
            }
            else if (strpos($filename, '.doc')) {
              $ob->link_to_full_text = 'http://faolex.fao.org/docs/texts/' . $filename;
            }
            else if (strpos($filename, '.htm')) {
              $ob->link_to_full_text = 'http://faolex.fao.org/docs/html/' . $filename;
            }
            else if (strpos($filename, '.html')) {
              $ob->link_to_full_text = 'http://faolex.fao.org/docs/html/' . $filename;
            }
            else {
              $ob->link_to_full_text = $filename;
            }

            $ob->Type_of_Text  = (string) $doc->Type_of_Text;
            $ob->Abstract      = (string) $doc->Abstract;
            $ob->Comment       = (string) $doc->Comment;

            foreach ($doc->Sub_file_code as $s) {
              $ob->Sub_file_code[] = (string) $s;
            }

            foreach ($doc->keyword as $s) {
              $ob->keyword[] = (string) $s;
            }

            $ob->International_Organizations = (string) $doc->International_Organizations;
            $ob->Record_Language             = (string) $doc->Record_Language;
            $ob->Doc_Language = $this->languageCode((string) $doc->Doc_Language);
            $ob->Repealed                    = (((string) $doc->Repealed) == 'Y') ? 1 : 0;
            $ob->Serial_Imprint              = (string) $doc->Serial_Imprint;
            $ob->Publication_reference       = (string) $doc->Publication_reference;

            if (empty( $ob->title )) {
              $this->setMessage('Skipping record with empty title:' . $ob->Recid);
              continue;
            }
            $this->data[$id] = $ob;
          }
        }
        catch ( Exception $e ) {
          $this->setMessage('Error parsing ' . $e->getMessage());
        }
      }
    }
  }
}
