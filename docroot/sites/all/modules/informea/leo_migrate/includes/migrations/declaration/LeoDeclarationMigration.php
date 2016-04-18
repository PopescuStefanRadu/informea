<?php

class LeoDeclarationMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));
    $this->addSimpleMappings(array(
      'title_field', 'title_field:language',
      'field_abbreviation',
    ));
    $this->addFieldMapping('field_abbreviation:language')->defaultValue('en');

    $this->removeFieldMapping('body:language');
    $this->addFieldMapping('body:language')->defaultValue('en');

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
    ));
  }
}
