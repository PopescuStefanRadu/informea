<?php

class LeoGoalSourcesMigration extends DrupalTerm7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'field_binding', 'field_abbreviation', 'field_abbreviation:language',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',
    ));

    $this->addUnmigratedSources(array(
      'field_binding:language',
    ));

  }

}
