<?php

class LeoLegislationFilesMigration extends DrupalFile7Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->removeFieldMapping('preserve_files');
    $this->addFieldMapping('preserve_files')->defaultValue(FALSE);
  }

  protected function query() {
    $query = parent::query();
    $query->condition('uri', 'public://legislation/%', 'LIKE');
    return $query;
  }
}