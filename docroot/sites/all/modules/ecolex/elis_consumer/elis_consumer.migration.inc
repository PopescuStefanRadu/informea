<?php

abstract class AbstractElisMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Entity original ID from the ELIS',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
  }

  abstract function validateRow($row);

  function prepare($entity, $row) {
    elis_migration_translate_entity('node', $entity, $row->languages);
  }


  /**
   * Map the term names with the existing terms tids.
   * If the vocabulary doesn't contain a term with that name, it will be created.
   *
   * @param $row
   *  Current migration row.
   * @param $field_name
   *  Name of the source field.
   * @param $data
   *  An array containing the terms. Each item needs to be an associative array
   * containing:
   *  - name: original term name
   *  - translations: an array containing language => translation pairs.
   * @param $vocabulary
   *  Vocabulary machine name.
   */
  public function prepare_term_reference_field(&$row, $field_name, $vocabulary) {
    if (empty($row->{$field_name})) {
      return;
    }
    else if (is_array($row->{$field_name})) {
      $tids = array();
      foreach ($row->{$field_name} as $delta => $term_name) {
        if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
          $tids[] = reset($term)->tid;
        }
        else {
          $translations = array();
          if (!empty($row->{$field_name . '_fr'}[$delta])) {
            $translations['fr'] = $row->{$field_name . '_fr'}[$delta];
          }
          if (!empty($row->{$field_name . '_es'}[$delta])) {
            $translations['es'] = $row->{$field_name . '_es'}[$delta];
          }
          $tids[] = elis_migration_create_taxonomy_term($term_name, $vocabulary, $translations);
        }
      }
      $row->{$field_name} = $tids;
    } else {
      // Handle single-valued fields
      $term_name = $row->{$field_name};
      if ($term = taxonomy_get_term_by_name($term_name, $vocabulary)) {
        $row->{$field_name} = reset($term)->tid;
      }
      else {
        $translations = array();
        if (!empty($row->{$field_name . '_fr'})) {
          $translations['fr'] = $row->{$field_name . '_fr'};
        }
        if (!empty($row->{$field_name . '_es'})) {
          $translations['es'] = $row->{$field_name . '_es'};
        }
        $row->{$field_name} = elis_migration_create_taxonomy_term($term_name, $vocabulary, $translations);
      }
    }
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    /**
     * @var string $field_name
     * @var MigrateFieldMapping $config
     */
    foreach ($this->getFieldMappings() as $field_name => $config) {
      if ($info = field_info_field($field_name)) {
        if ($info['type'] == 'taxonomy_term_reference' && $source_field = $config->getSourceField()) {
          if (!empty($row->{$source_field})) {
            $this->prepare_term_reference_field($row, $source_field, $info['settings']['allowed_values'][0]['vocabulary']);
          }
        }
      }
    }
  }
}
