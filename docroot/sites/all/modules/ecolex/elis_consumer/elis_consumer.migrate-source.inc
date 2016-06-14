<?php

require_once 'elis_consumer.xml.inc';

abstract class AbsractElisMigrateSource extends MigrateSource {

  protected $keyField = NULL;
  protected $xmlEncoding = NULL;
  protected $data = array();
  protected $source = NULL;

  abstract function getFieldFilter($field_name);
  abstract function prepareItem($item);

  public function __construct($generic_url, $keyField, $xmlEncoding) {
    parent::__construct(array());
    $this->keyField = $keyField;
    $this->xmlEncoding = $xmlEncoding;
    $this->source = new Drupal\elis_consumer\ElisXMLConsumer($generic_url, $keyField, $xmlEncoding, '2006-01', 'STAT:C');
  }


  protected function getData() {
    if (empty($this->data)) {
      $rows = $this->source->getData();
      foreach($rows as $id => $row) {
        if (!empty($row->{$this->keyField}) && empty((string)$row->projectInformation) || strtoupper((string)$row->projectInformation) != 'WILD') {
          $this->data[$id] = $row;
        }
      }
    }
    return $this->data;
  }


  public function computeCount() {
    $data = $this->getData();
    return count($data);
  }


  /**
   * Do whatever needs to be done to start a fresh traversal of the source data.
   *
   * This is always called at the start of an import, so tasks such as opening
   * file handles, running queries, and so on should be performed here.
   */
  public function performRewind() {
    $this->data = array();
    $this->data = $this->getData();
    reset($this->data);
  }

  /**
   * Fetch the next row of data, returning it as an object.
   *
   * @return object
   *   FALSE data as stdClass, FALSE when there is no more data available.
   */
  public function getNextRow() {
    if ($doc = current($this->data)) {
      $ob = $this->getItem($doc);
      next($this->data);
      return $ob;
    }
    return NULL;
  }


  protected function getItem($data) {
    $ob = new stdClass();
    $ob->id = (string) $data->{$this->keyField};
    // $ob->original_source = $data;
    $ob->languages = array();
    $source_fields = $this->fields();
    $parties = array();
    foreach($source_fields as $field_name => $description) {
      if ($filter = $this->getFieldFilter($field_name)) {
        $this->$filter($ob, $field_name, $data);
      }
      else if (!empty($data->{$field_name})) {
        $value = $this->prepareString($data->{$field_name});
        $ob->{$field_name} = $value;
      }
    }
    $ob->parties = $parties;
    if (property_exists($ob, 'obsolete')) {
      $ob->obsolete = (bool) $ob->obsolete;
    }
    $this->prepareItem($ob);
    return $ob;
  }


  function filter_single_concatenated($ob, $field_name, $data) {
    $this->filter_multivalued($ob, $field_name, $data);
    $ob->{$field_name} = implode(PHP_EOL, $ob->{$field_name});
  }


  function filter_multivalued($ob, $field_name, $data) {
    $lower_field_name = strtolower($field_name);
    $ob->{$field_name} = array();
    foreach($data as $name => $value) {
      $name = strtolower($name);
      if ($lower_field_name === $name) {
        $ob->{$field_name}[] = $this->prepareString($value);
      }
    }
  }


  function filter_single_multilingual($ob, $field_name, $data) {
    $ret = array();
    $lower_field_name = strtolower($field_name);
    foreach($data as $name => $value) {
      $name = strtolower($name);
      $language = NULL;
      switch($name) {
        case $lower_field_name:
          $language = 'en';
          break;
        case $lower_field_name . 'fr':
        case $lower_field_name . '_fr_fr':
          $language = 'fr';
          break;
        case $lower_field_name . 'sp':
        case $lower_field_name . '_es_es':
          $language = 'es';
          break;
      }
      if ($language) {
        $ret[$language] = $this->prepareString($value);
      }
    }
    $ob->{$field_name} = array_values($ret);
    $ob->{$field_name . '_languages'} = array_keys($ret);
  }


  function filter_multivalued_multilingual($ob, $field_name, $data) {
    $lower_field_name = strtolower($field_name);
    $ob->{$field_name} = array();
    foreach($data as $name => $value) {
      $name = strtolower($name);
      // English
      if ($lower_field_name === $name) {
        $ob->{$field_name}[] = $this->prepareString($value);
      }

      // Other languages
      $language = NULL;
      switch($name) {
        case $lower_field_name . 'fr':
        case $lower_field_name . '_fr_fr':
          $language = 'fr';
          break;
        case $lower_field_name . 'sp':
        case $lower_field_name . '_es_es':
          $language = 'es';
          break;
      }
      if ($language) {
        $ob->{$field_name . '_' . $language}[] = $this->prepareString($value);
      }
    }
  }


  function filter_multivalued_multilingual_concatenated($ob, $field_name, $data) {
    $lower_field_name = strtolower($field_name);
    $concatenated = array();
    foreach($data as $name => $value) {
      $name = strtolower($name);
      // Other languages
      switch($name) {
        case $lower_field_name:
          $concatenated['en'][] = $this->prepareString($value);
          break;
        case $lower_field_name . 'fr':
        case $lower_field_name . '_fr_fr':
          $concatenated['fr'][] = $this->prepareString($value);
          break;
        case $lower_field_name . 'sp':
        case $lower_field_name . '_es_es':
          $concatenated['es'][] = $this->prepareString($value);
          break;
      }
    }
    $ob->{$field_name} = array();
    $ob->{$field_name . '_languages'} = array();
    foreach($concatenated as $language => $parts) {
      foreach($parts as &$part) {
        $part = str_replace(PHP_EOL, '', $part);
      }
      $ob->{$field_name}[] = implode(PHP_EOL, $parts);
      $ob->{$field_name . '_languages'}[] = $language;
    }
  }

  protected function prepareString($str) {
    if (strtolower($this->xmlEncoding) == 'utf-8') {
      $ret = (string) $str;
    }
    else {
      // $ret = utf8_decode((string) $str);
      $ret = (string) $str;
    }
    return trim($ret);
  }
}


class CourtDecisionElisMigrateSource extends AbsractElisMigrateSource {

  public function __construct($source_url_pattern, $xml_encoding) {
    parent::__construct($source_url_pattern, 'id', $xml_encoding);
    $this->source = new Drupal\elis_consumer\ElisXMLRowConsumer($source_url_pattern, 'id', $xml_encoding);
  }

  public function __toString() {
    return sprintf('Extract court decisions from ELIS.');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'id2' => 'ID2',
      'isisMfn' => 'Isis number',
      'dateOfEntry' => 'Date of entry',
      'dateOfModification' => 'Date of modification',
      'title_english' => 'Title of text in english',
      'titleOfText' => 'Title of text',
      'titleOfText_languages' => 'Available languages',
      'titleOfTextShort' => 'Title of text short',
      'titleOfTextShort_languages' => 'Available languages',
      'titleOfTextOther' => 'Other title of text (single value)',
      'titleOfTextShortOther' => 'Other short title of text (single value)',
      'country' => 'Country',
      'subject' => 'Subject (Also has properties subject_fr, subject_es)',
      'languageOfDocument' => 'Language',
      'courtName' => 'Court name',
      'dateOfText' => 'Date of text',
      'referenceNumber' => 'Reference number',
      'numberOfPages' => 'Number of pages',
      'availableIn' => 'Available in',
      'linkToFullText' => 'Link to the full text',
      'linkToFullText_languages' => 'Languages of linkToFullText field',
      'linkToFullTextOther' => 'Link to the full text in unknown language',
      'internetReference' => 'Internet reference of the document',
      'relatedWebSite' => 'Internet related website of the document',
      'keyword' => 'Keywords',
      'keyword_fr' => 'Keywords in French',
      'keyword_es' => 'Keywords in Spanish',
      'abstract' => 'Abstract',
      'abstract_language' => 'Available languages',
      'typeOfText' => 'Type of text',
      'referenceToNationalLegislation' => 'Reference to legislation',
      'referenceToTreaties' => 'Reference to legislation',
      'languages' => 'All languages to translate into',
      'referenceToCourtDecision' => 'Reference to other court decisions',
      'subdivision' => 'Subdivision',
      'justices' => 'List of justices (judges)',
      'territorialSubdivision' => 'Territorial subdivision',
      'linkToAbstract' => 'URL to abstract',
      'statusOfDecision' => 'Status of the court decision',
      'referenceToEULegislation' => 'Reference to legislation',
      'seatOfCourt' => 'Seat of court',
      'courtJurisdiction' => 'Court jurisdiction',
      'instance' => 'Instance',
      'officialPublication' => 'Place of publication',
      'region' => 'Geographical region',
      'referenceToFaolex' => 'Reference to FAO legislation',
      // languageOfTranslation ??? @todo: I don't understand this field
    );
  }

  function getFieldFilter($field_name) {
    $filters = array(
      'titleOfText' => 'filter_single_multilingual',
      'titleOfTextShort' => 'filter_single_multilingual',
      'country' => 'filter_multivalued',
      'abstract' => 'filter_multivalued_multilingual_concatenated',
      'subject' => 'filter_multivalued_multilingual',
      'keyword' => 'filter_multivalued_multilingual',
      'typeOfText' => 'filter_multivalued_multilingual',
      'referenceToNationalLegislation' => 'filter_multivalued',
      'referenceToEULegislation' => 'filter_multivalued',
      'referenceToCourtDecision' => 'filter_multivalued',
      'referenceToTreaties' => 'filter_multivalued',
      'justices' => 'filter_multivalued',
      'territorialSubdivision' => 'filter_multivalued_multilingual',
      'region' => 'filter_multivalued_multilingual',
      'referenceToFaolex' => 'filter_multivalued',
    );
    return !empty($filters[$field_name]) ? $filters[$field_name] : NULL;
  }

  function prepareItem($item) {
    $item->title_english = !empty($item->titleOfText[0]) ? $item->titleOfText[0] : NULL;
    if (empty($item->title_english) && !empty($item->titleOfTextOther[0])) {
      $item->title_english = $item->titleOfTextOther[0];
    }
    $languages = array();
    $item->languages = array_unique($languages);
  }
}



class TreatyElisMigrateSource extends AbsractElisMigrateSource {

  public function __construct($source_url_pattern, $xml_encoding) {
    parent::__construct($source_url_pattern, 'Recid', $xml_encoding);
  }

  public function __toString() {
    return sprintf('Extract treaties from ELIS');
  }

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'Recid' => 'Remote primary key',
      'dateOfEntry' => 'Date of entry',
      'dateOfModification' => 'Date of modification',
      'titleOfText' => 'Title of text',
      'title_english' => 'Title of text in english',
      'titleOfText_languages' => 'Languages of titleOfText field',
      'titleAbbreviation' => 'Title abbreviation',
      'titleAbbreviation_languages' => 'Languages of titleAbbreviation field',
      'typeOfText' => 'Type of text',
      'jurisdiction' => 'Jurisdiction',
      'fieldOfApplication' => 'Field of application',
      'sortFieldOfApplication' => 'sortFieldOfApplication',
      'region' => 'Region',
      'subject' => 'Subject',
      'subject_fr' => 'Subject in French',
      'subject_es' => 'Subject in Spanish',
      'languageOfDocument' => 'Language',
      'languageOfTranslation' => 'Original language',
      'placeOfAdoption' => 'Place of adoption',
      'depository' => 'Depository (country)',
      'depository_languages' => 'Available languages',
      'dateOfText' => 'Date of text',
      'searchDate' => 'Search date',
      'entryIntoForceDate' => 'Entry into force that',
      'obsolete' => 'Obsolete',
      'officialPublication' => 'Official publication',
      'availableIn' => 'Available in',
      'linkToFullText' => 'Link to the full text',
      'linkToFullText_languages' => 'Languages of linkToFullText field',
      'relatedWebSite' => 'Related website',
      'keyword' => 'Keywords',
      'abstract' => 'Abstract',
      'amendsTreaty' => 'Amends treaty',
      'amendsTreatyText' => 'Amends treaty',
      'party' => 'Party members to the treaty',
      'languages' => 'All languages to translate into',
    );
  }

  function getFieldFilter($field_name) {
    $filters = array(
      'titleOfText' => 'filter_single_multilingual',
      'titleAbbreviation' => 'filter_single_multilingual',
      'typeOfText' => 'filter_multivalued_multilingual',
      'jurisdiction' => 'filter_multivalued_multilingual',
      'fieldOfApplication' => 'filter_multivalued_multilingual',
      'region' => 'filter_multivalued',
      'subject' => 'filter_multivalued_multilingual',
      'languageOfDocument' => 'filter_single_multilingual',
      'languageOfTranslation' => 'filter_multivalued_multilingual',
      'depository' => 'filter_single_multilingual',
      'linkToFullText' => 'filter_single_multilingual',
      'relatedWebSite' => 'filter_multivalued',
      'keyword' => 'filter_multivalued_multilingual',
      'abstract' => 'filter_multivalued_multilingual_concatenated',
      'amendsTreaty' => 'filter_multivalued',
      'party' => 'filter_party_objects',
    );
    return !empty($filters[$field_name]) ? $filters[$field_name] : NULL;
  }

  function filter_party_objects($ob, $field_name, $data) {
    $ob->{$field_name} = array();
    if (empty($data->{$field_name})) {
      return;
    }
    foreach($data->{$field_name} as $row) {
      $party = new stdClass();
      $party->potentialParty = $this->prepareString($row->potentialParty);
      $party->potentialParty = strtolower($party->potentialParty) === 'yes';
      $party->dateOfAccessionApprobation = $this->prepareString($row->dateOfAccessionApprobation);
      $party->entryIntoForce = $this->prepareString($row->entryIntoForce);
      $this->filter_single_multilingual($party, 'country', $row);
      $ob->{$field_name}[] = $party;
    }
  }


  function prepareItem($item) {
    $item->title_english = !empty($item->titleOfText[0]) ? $item->titleOfText[0] : NULL;
    $languages = array();
    if (!empty($item->titleOfText_languages)) {
      $languages += $item->titleOfText_languages;
    }
    if (!empty($item->titleAbbreviation_languages)) {
      $languages += $item->titleAbbreviation_languages;
    }
    if (!empty($item->depository_languages)) {
      $languages += $item->depository_languages;
    }
    if (!empty($item->linkToFullText_languages)) {
      $languages += $item->linkToFullText_languages;
    }
    $item->amendsTreatyText = $item->amendsTreaty;
    $item->languages = array_unique($languages);
  }

}
