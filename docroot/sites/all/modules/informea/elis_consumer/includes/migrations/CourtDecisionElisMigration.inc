<?php

abstract class CourtDecisionElisMigration extends AbstractElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->translatable_fields = array();
    /*
     * If mapped, all `taxonomy term reference` fields should be sent to
     * prepare_term_reference_field() method within prepareRow() method.
     *
     * E.g. $this->prepare_term_reference_field($row, 'subject', 'thesaurus_ecolex');
     */
    $this->taxonomy_term_fields = array();

    $this->source = new CourtDecisionElisMigrateSourceList(
      new CourtDecisionElisMigrateList('id'),
      new CourtDecisionElisMigrateItem($this->translatable_fields, $this->taxonomy_term_fields)
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
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