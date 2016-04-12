<?php

class LeoGoalMigration extends LeoDefaultNodeMigration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array_keys($this->taxonomyFields()));

    $this->addSimpleMappings(array(
      'field_official_order', 'field_official_order:language', 'field_document_url',
      'field_document_url:title', 'field_document_url:attributes', 'field_document_url:language',
      'field_goal_tools', 'field_goal_tools:format', 'title_field', 'title_field:language',
      'field_url', 'field_url:title', 'field_url:attributes', 'field_url:language',

    ));

    $this->addUnmigratedSources(array(
      'uid', 'revision', 'log', 'revision_uid',
    ));

    $this->addUnmigratedDestinations(array(
    ));
  }

  protected function taxonomyFields() {
    return [
      'field_goal_type' => 'type_of_goal',
      'field_goal_source' => 'goal_sources',
      'field_informea_tags' => 'thesaurus_informea',
      'field_geg_tags' => 'thesaurus_geg',
      'field_geg_theme' => 'geg_theme',
      'field_geographical_scope' => 'geographical_scope',
    ];
  }

  function prepareRow($row) {
    parent::prepareRow($row);
  }
}