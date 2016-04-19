<?php

namespace Drupal\taxonomy_external_sync\plugin;


interface SourceInterface {

  function setConfiguration(array $config);

  /**
   * Plugin configuration form.
   *
   * @return array
   *   Plugin configuration form
   */
  function getConfigurationForm();

  /**
   * Get plugin human name.
   *
   * @return string
   */
  function getName();

  /**
   * Plugin description - what it does.
   *
   * @return string
   */
  function getDescription();

  /**
   * Array of field names as keys and description as values.
   *
   * @return array
   */
  function getFieldNames();

  /**
   * Array of objects with fields defined above.
   *
   * @return array
   */
  function getTerms();
}

class DummySourcePlugin implements SourceInterface {

  function setConfiguration(array $config) {
    // TODO: Implement setConfiguration() method.
  }

  function getConfigurationForm() {
    // TODO: Implement getConfigurationForm() method.
  }

  function getName() {
    return 'DummySourcePlugin';
  }

  function getDescription() {
    return 'Sample plugin doing nothing';
  }

  function getFieldNames() {
    // TODO: Implement getFieldNames() method.
  }

  function getTerms() {
    // TODO: Implement getTerms() method.
  }
}