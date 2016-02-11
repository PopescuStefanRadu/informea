<?php

/**
 * Class TreatyElisMigrateSourceList provides fields for Treaty migration.
 */
class TreatyElisMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'Recid' => 'Remote primary key',
      'dateOfEntry' => 'Date of entry',
      'dateOfModification' => 'Date of modification',
      'titleOfText' => 'Title of text',
      'titleAbbreviation' => 'Title abbreviation',
      'typeOfText' => 'Type of text',
      'jurisdiction' => 'Jurisdiction',
      'fieldOfApplication' => 'Field of application',
      'sortFieldOfApplication' => 'sortFieldOfApplication',
      'region' => 'Region',
      'subject' => 'Subject',
      'languageOfDocument' => 'Language',
      'languageOfTranslation' => 'Original language', //???
      'placeOfAdoption' => 'Place of adoption',
      'depository' => 'Depository (country)',
      'dateOfText' => 'Date of text', //???
      'searchDate' => 'Search date', //???
      'entryIntoForceDate' => 'Entry into force that',
      'obsolete' => 'Obsolete',
      'officialPublication' => 'Official publication',
      'availableIn' => 'Available in', //???
      'linkToFullText' => 'Link to the full text',
      'relatedWebSite' => 'Related website',
      'keyword' => 'Keywords',
      'abstract' => 'Abstract',
      'amendsTreaty' => 'Amends treaty', //???
      'party' => 'Parties', //???
    );
  }
}