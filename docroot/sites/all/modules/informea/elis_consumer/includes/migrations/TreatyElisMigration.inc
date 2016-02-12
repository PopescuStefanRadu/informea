<?php

abstract class TreatyElisMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->translatable_fields = array(
      'abstract', 'titleOfText', 'titleAbbreviation','typeOfText', 'jurisdiction', 'fieldOfApplication',
      'region', 'languageOfDocument', 'languageOfTranslation', 'depository',
      // @ToDo: fix the problem with translations of link field
      // 'linkToFullText',
      );

    $this->source = new TreatyElisMigrateSourceList(
      new TreatyElistMigrateList(),
      new TreatyElisMigrateItem($this->translatable_fields)
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