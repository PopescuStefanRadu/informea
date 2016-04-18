<?php

class LeoDeclarationSectionMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'title_field', 'title_field:language', 'field_hidden',
    ));

    $this->addFieldMapping('field_parent_declaration', 'field_parent_declaration')->sourceMigration(array('declaration'));
    $this->addFieldMapping('field_declaration_parent_section', 'field_declaration_parent_section')->sourceMigration(array('declaration_section'));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
    ));
  }

  protected function taxonomyFields() {
    return array(
      'field_informea_tags' => 'thesaurus_informea',
    );
  }
}
