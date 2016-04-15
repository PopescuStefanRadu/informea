<?php

class LeoDefaultTaxonomyMigration extends DrupalTerm7Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
    if (!empty($arguments['translatable_name']) && $arguments['translatable_name'] == TRUE) {
      $this->addSimpleMappings(array(
        'name_field',
        'name_field:language',
      ));
    }
    if (!empty($arguments['translatable_description']) && $arguments['translatable_description'] == TRUE) {
      $this->addSimpleMappings(array(
        'description_field',
        'description_field:summary',
        'description_field:format',
        'description_field:language',
      ));
    }
  }

}
