<?php

class EcolexTreatyMigrateWiki extends Migration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->dependencies = array('Treaties');
    $this->arguments   = $arguments;
    $this->description = 'Import ECOLEX treaties from XML web service (files)';
    $data_dir          = $arguments['data_dir'];
    $this->source      = new EcolexTreatyMigrateSource($data_dir, array());
    $this->map         = new MigrateSQLMap($this->machineName,
      array(
        'Recid' => array(
          'type'        => 'varchar',
          'length'      => 255,
          'not null'    => TRUE,
          'description' => 'RecId field remote primary key',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->destination = new MigrateDestinationNode('treaty');

    $this->addFieldMapping('field_original_id', 'Recid');
    $this->addFieldMapping('field_date_of_entry', 'dateOfEntry');
    $this->addFieldMapping('field_date_of_modification', 'dateOfModification');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('title_field', 'titleOfText');

    $this->addFieldMapping('field_data_source')->defaultValue('Ecolex');
    $this->addFieldMapping('field_data_source:create_term')->defaultValue(TRUE);

    $this->addFieldMapping('field_type_of_text', 'typeOfText');
    $this->addFieldMapping('field_type_of_text:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_type_of_text:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_jurisdiction', 'jurisdiction');
    $this->addFieldMapping('field_jurisdiction:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_jurisdiction:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_field_of_application', 'fieldOfApplication');
    $this->addFieldMapping('field_field_of_application:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_field_of_application:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_ecolex_tags', 'subject');
    $this->addFieldMapping('field_ecolex_tags:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_ecolex_tags:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_keywords', 'keyword');
    $this->addFieldMapping('field_keywords:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_keywords:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_informea_tags', 'mapped_informea_keywords');
    $this->addFieldMapping('field_informea_tags:create_term')->defaultValue(FALSE);
    $this->addFieldMapping('field_informea_tags:source_type')->defaultValue('tid');

    // $this->addFieldMapping('', 'languageOfDocument');
    $this->addFieldMapping('field_place_of_adoption', 'placeOfAdoption');
    $this->addFieldMapping('field_depositary', 'depository');
    $this->addFieldMapping('field_sorting_date', 'dateOfText');
    // $this->addFieldMapping('', 'searchDate');
    $this->addFieldMapping('field_entry_into_force', 'entryIntoForceDate');
    $this->addFieldMapping('field_obsolete', 'obsolete');
    $this->addFieldMapping('field_official_publication', 'officialPublication');
    $this->addFieldMapping('field_available_in', 'availableIn');
    $this->addFieldMapping('field_treaty_text_url', 'linkToFullText');
    $this->addFieldMapping('field_treaty_website_url', 'internetReference');
    $this->addFieldMapping('body', 'abstract');
    // $this->addFieldMapping('field_amends_treaty', 'amendsTreaty');
    $this->addFieldMapping('field_related_url', 'relatedWebSite');
    // $this->addFieldMapping('field_cited_treaties', 'citesTreaty');

    $this->addFieldMapping('field_region', 'region');
    $this->addFieldMapping('field_region:create_term')->defaultValue(TRUE);
    $this->addFieldMapping('field_region:ignore_case')->defaultValue(TRUE);

    $this->addFieldMapping('field_ecolex_url', 'ecolex_url');
  }

  /**
   * {@inheritdoc}
   */
  protected function generateMachineName() {
    return 'EcolexTreaties';
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    // Map Ecolex subjects/keywords to InforMEA vocabulary
    $row->mapped_informea_keywords = array();
    $ecolex_terms = array();
    if (!empty($row->keyword)) {
      $ecolex_terms = array_merge($ecolex_terms, $row->keyword);
    }
    if (!empty($row->subject)) {
      $ecolex_terms = array_merge($ecolex_terms, $row->subject);
    }
    if (!empty($ecolex_terms)) {
      module_load_include('inc', 'informea', 'informea.api');
      $row->mapped_informea_keywords = array_keys(informea_map_ecolex_terms($ecolex_terms));
    }
    // Map regions to UNEP regions
    if (!empty($row->region)) {
      if (is_string($row->region)) {
        $row->region = country_map_region($row->region);
      }
      else if (is_array($row->region)) {
        foreach ($row->region as &$region) {
          $region = country_map_region($region);
        }
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

    $row->field_ecolex_url['en'][0]['url'] = 'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=treaties&id=' . $row->Recid;

    $translation_handler  = entity_translation_get_handler($entity_type, $entity);
    $entity->translations = $translation_handler->getTranslations();
    $entity->language     = 'en';
    foreach ($languages as $language) {
      $has_translation = FALSE;

      if ( ! empty( $row->abstract[$language] )) {
        $entity->body[$language][0]['value']  = $row->abstract[$language];
        $entity->body[$language][0]['format'] = 'full_html';
        $has_translation                      = TRUE;
      }
      if ( ! empty( $row->titleOfText[$language] )) {
        $entity->title_field[$language][0]['value'] = $row->titleOfText[$language];
        $has_translation                            = TRUE;
      }
      if ($has_translation) {
        MigrationUtil::setTranslation($translation_handler, $entity, $row, $language);
      }
    }
  }
}


class EcolexTreatyMigrateSource extends MigrateSource {

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
      'Recid'               => 'ECOLEX unique ID',
      'dateOfEntry'         => '@todo: dateOfEntry',
      'dateOfModification'  => '@todo: dateOfModification',
      'titleOfText'         => 'Page title multilingual',
      'typeOfText'          => '@todo: typeOfText',
      'jurisdiction'        => '@todo: jurisdiction',
      'fieldOfApplication'  => '@todo: fieldOfApplication',
      'subject'             => '@todo: subject',
      'languageOfDocument'  => '@todo: languageOfDocument',
      'placeOfAdoption'     => '@todo: placeOfAdoption',
      'depository'          => '@todo: depository',
      'dateOfText'          => '@todo: dateOfText',
      'searchDate'          => '@todo: searchDate',
      'entryIntoForceDate'  => '@todo: entryIntoForceDate',
      'obsolete'            => '@todo: obsolete',
      'officialPublication' => '@todo: officialPublication',
      'availableIn'         => '@todo: availableIn',
      'linkToFullText'      => '@todo: linkToFullText',
      'internetReference'   => '@todo: internetReference',
      'amendsTreaty'        => '@todo: amendsTreaty',
      'relatedWebSite'      => '@todo: relatedWebSite',
      'abstract'            => '@todo: abstract',
      'citesTreaty'         => '@todo: citesTreaty',
      'keyword'             => '@todo: keyword',
      'region'              => '@todo: region',
      'ecolex_url'          => 'Web page on ECOLEX website',
      'mapped_informea_keywords'  => 'Mapped terms computed during import from subject & keyword fields',
    );
  }

  /**
   * Return the number of available source records.
   */
  public function computeCount() {
    if (empty( $this->data )) {
      $this->readData();
    }

    return count($this->data);
  }

  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    reset($this->data);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    if (empty( $this->data )) {
      $this->readData();
    }
    $item = NULL;
    if (count($this->data)) {
      $item = current($this->data);
      next($this->data);
    }

    return $item;
  }

  /**
   * Query the remote source and pull the data.
   */
  protected function readData() {
    if ( ! $this->parsed) {
      $this->data   = array();
      $this->parsed = TRUE;
      $files        = file_scan_directory($this->data_dir, '/.*/');
      foreach ($files as $file) {
        $docs = simplexml_load_file($file->uri);
        foreach ($docs as $doc) {
          $id = (string) $doc->Recid;

          $ob           = new stdClass();
          $ob->language = 'en';
          // Copy all attributes
          $ob->Recid              = $id;
          $ob->dateOfEntry        = (string) $doc->dateOfEntry;
          $ob->dateOfModification = (string) $doc->dateOfModification;

          $ob->titleOfText['en'] = (string) $doc->titleOfText;
          $ob->titleOfText['fr'] = (string) $doc->titleOfTextFr;
          $ob->titleOfText['es'] = (string) $doc->titleOfTextSp;
          $ob->titleOfText['de'] = (string) $doc->titleOfTextOther;
          foreach ($ob->titleOfText as $title) {
            if ( ! empty( $title )) {
              $ob->title = $title;
              break;
            }
          }

          $ob->typeOfText         = (string) $doc->typeOfText;
          $ob->jurisdiction       = (string) $doc->jurisdiction;
          $ob->fieldOfApplication = (string) $doc->fieldOfApplication;

          foreach ($doc->subject as $s) {
            $ob->subject[] = MigrationUtil::decodeHTMLText((string) $s);
          }
          foreach ($doc->languageOfDocument as $s) {
            $ob->languageOfDocument[] = (string) $s;
          }

          $ob->placeOfAdoption = (string) $doc->placeOfAdoption;
          $ob->depository      = (string) $doc->depository;
          $ob->dateOfText      = (string) $doc->dateOfText;
          $ob->dateOfText      = ( $ob->dateOfText == '0000-00-00' ) ? NULL : $ob->dateOfText;

          $ob->searchDate = (string) $doc->searchDate;
          $ob->searchDate = ( $ob->searchDate == '0000-00-00' ) ? NULL : $ob->searchDate;

          $ob->entryIntoForceDate = (string) $doc->entryIntoForceDate;
          $ob->entryIntoForceDate = ( $ob->entryIntoForceDate == '0000-00-00' ) ? NULL : $ob->entryIntoForceDate;

          $ob->obsolete            = ((string) $doc->obsolete == 'true' ) ? 1 : 0;
          $ob->officialPublication = (string) $doc->officialPublication;
          $ob->availableIn         = (string) $doc->availableIn;
          $ob->linkToFullText      = (string) $doc->linkToFullText;
          $ob->internetReference   = (string) $doc->internetReference;
          $ob->amendsTreaty        = (string) $doc->amendsTreaty;
          $ob->relatedWebSite      = (string) $doc->relatedWebSite;

          $ob->abstract['en'] = (string) $doc->abstract;
          $ob->abstract['fr'] = (string) $doc->abstractFr;
          $ob->abstract['es'] = (string) $doc->abstractSp;

          foreach ($doc->citesTreaty as $s) {
            $ob->citesTreaty[] = (string) $s;
          }
          foreach ($doc->keyword as $s) {
            $ob->keyword[] = (string) $s;
          }
          foreach ($doc->region as $s) {
            $ob->region[] = (string) $s;
          }

          $ob->ecolex_url = 'http://www.ecolex.org/ecolex/ledge/view/RecordDetails?index=treaties&id=' . $id;

          if (empty( $ob->title )) {
            $this->setMessage('Skipping record with empty title:' . $ob->Recid);
            continue;
          }
          $this->staticFieldFixes($ob);
          $this->data[$id] = $ob;
        }
      }
    }
  }

  protected function staticFieldFixes(&$ob) {
    if ($ob->entryIntoForceDate == '2003-14-05') {
      $ob->entryIntoForceDate = '2003-05-14';
    }
    if ($ob->entryIntoForceDate == '2103-20-04') {
      $ob->entryIntoForceDate = '2013-04-20';
    }
  }

  /**
   * Add messages during data retrieval for debugging.
   *
   * @param string $msg
   *   Message string
   * @param int $severity
   *   Migration message level
   */
  protected function setMessage(
    $msg, $severity = MigrationBase::MESSAGE_WARNING
  ) {
    if (function_exists('drush_log')) {
      drush_log($msg, 'warning');
    }
    drupal_set_message($msg);
    $this->activeMigration->queueMessage($msg, $severity);
  }
}
