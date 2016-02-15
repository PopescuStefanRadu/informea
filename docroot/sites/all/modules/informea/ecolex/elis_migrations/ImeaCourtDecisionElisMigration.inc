<?php

define('DRUPAL_TYPE_COURT_DECISION', 'court_decisions');

class ImeaCourtDecisionElisMigration extends CourtDecisionElisMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->destination = new MigrateDestinationNode(DRUPAL_TYPE_COURT_DECISION);
  }

}