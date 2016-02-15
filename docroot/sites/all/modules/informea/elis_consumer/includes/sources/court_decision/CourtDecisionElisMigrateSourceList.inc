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
    );
  }
}