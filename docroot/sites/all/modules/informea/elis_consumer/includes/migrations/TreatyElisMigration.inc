<?php

abstract class TreatyElisMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->source = new TreatyElisMigrateSourceList(
      new TreatyElistMigrateList(),
      new TreatyElisMigrateItem()
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