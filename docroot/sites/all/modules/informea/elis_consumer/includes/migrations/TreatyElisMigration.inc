<?php

abstract class TreatyElisMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->translatable_fields = array(
      'abstract', 'titleOfText', 'titleAbbreviation','typeOfText', 'jurisdiction', 'fieldOfApplication',
      'region', 'languageOfDocument', 'languageOfTranslation', 'depository', 'linkToFullText',
      'subject', 'keyword',
      );
    /*
     * If mapped, all `taxonomy term reference` fields should be sent to
     * prepare_term_reference_field() method within prepareRow() method.
     *
     * E.g. $this->prepare_term_reference_field($row, 'subject', 'thesaurus_ecolex');
     */
    $this->taxonomy_term_fields = array('subject', 'keyword', 'fieldOfApplication', 'jurisdiction', 'region');

    $this->source = new TreatyElisMigrateSourceList(
      new TreatyElisMigrateList('Recid'),
      new TreatyElisMigrateItem($this->translatable_fields, $this->taxonomy_term_fields)
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'Recid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Original ID from the ELIS',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

  }

}