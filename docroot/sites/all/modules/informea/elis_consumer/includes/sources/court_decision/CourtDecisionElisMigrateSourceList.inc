<?php

/**
 * Class CourtDecisionElisMigrateSourceList provides fields for Court decisions migration.
 */
class CourtDecisionElisMigrateSourceList extends MigrateSourceList {

  /**
   * The list of available fields to map from the source, keyed by field name.
   */
  public function fields() {
    return array(
      'id' => 'Remote primary key',
      'dateOfEntry' => 'Date of entry',
      'dateOfModification' => 'Date of modification',
      'titleOfText' => 'Title of text',
      'titleOfTextShort' => 'Title of text short',
      'titleOfText_original' => 'Title of text in english',
      'titleOfText_languages' => 'Languages of titleOfText field',
      'country' => 'Country',
      'subject' => 'Subject',
      'languageOfDocument' => 'Language',
      'courtName' => 'Court name',
      'dateOfText' => 'Date of text',
      'referenceNumber' => 'Reference number',
      'numberOfPages' => 'Number of pages',
      'availableIn' => 'Available in',
      'linkToFullText' => 'Link to the full text',
      'linkToFullText_languages' => 'Languages of linkToFullText field',
      'keyword' => 'Keywords',
      'abstract' => 'Abstract',
      'abstract_languages' => 'Languages of abstract field',
      'referenceToNationalLegislation' => 'Reference to legislation',
    );
  }
}