<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

abstract class DefaultSource {

  protected $url = NULL;
  protected $id_field = NULL;
  protected $parent_field = NULL;

  public function __construct($config = array()) {
    $this->setConfiguration($config);
  }

  function setConfiguration(array $config) {
    if (!empty($config['url'])) {
      $this->url = $config['url'];
    }
    if (!empty($config['id_field'])) {
      $this->id_field = $config['id_field'];
    }
    if (!empty($config['parent_field'])) {
      $this->parent_field = $config['parent_field'];
    }
  }

  /**
   * Plugin configuration form.
   *
   * @return array
   *   Plugin configuration form
   */
  function getConfigurationForm($vocabulary, $form_state) {
    $ret = array(
      'url' => array(
        '#title' => t('Enter XML URL'),
        '#type' => 'textfield',
        '#maxlength'=> 255,
        '#size' => 100,
        '#required' => TRUE,
        '#default_value' => !empty($vocabulary->tes['plugin_config']['url']) ? $vocabulary->tes['plugin_config']['url'] : NULL,
      )
    );
    $options = array_merge(
      array('' => t('-- Please select --')),
      $this->getFieldNames()
    );
    $ret['id_field'] = array(
      '#title' => t('Source identifier field'),
      '#description' => t('Select the local field where the remote indentifier is stored to track remote subsequent updates to the terms'),
      '#type' => 'select',
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => !empty($vocabulary->tes['plugin_config']['id_field']) ? $vocabulary->tes['plugin_config']['id_field'] : NULL,
    );
    $ret['parent_field'] = array(
      '#title' => t('Parent term'),
      '#description' => t('This field should contain the source ID of parent term.'),
      '#type' => 'select',
      '#options' => $options,
      '#required' => FALSE,
      '#default_value' => !empty($vocabulary->tes['plugin_config']['parent_field']) ? $vocabulary->tes['plugin_config']['parent_field'] : NULL,
    );
    return $ret;
  }

  /**
   * Get the source identifier field.
   *
   * @return string
   */
  public function getIdField() {
    return $this->id_field;
  }

  /**
   * Get the source parent id field.
   *
   * @return string
   */
  public function getParentField() {
    return $this->parent_field;
  }

  /**
   * Get plugin human name.
   *
   * @return string
   */
  abstract function getName();

  /**
   * Plugin description - what it does.
   *
   * @return string
   */
  abstract function getDescription();

  /**
   * Array of field names as keys and description as values.
   *
   * @return array
   */
  abstract function getFieldNames();

  /**
   * Array of objects with fields defined above.
   *
   * @return array
   */
  abstract function getTerms();
}

class DummySourcePlugin extends DefaultSource {

  function getName() {
    return 'DummySourcePlugin';
  }

  function getDescription() {
    return 'Sample plugin doing nothing';
  }

  function getIdField() {
    // TODO: Implement getIdField() method.
  }

  function getParentField() {
    // TODO: Implement getParentField() method.
  }

  function getFieldNames() {
    // TODO: Implement getFieldNames() method.
  }

  function getTerms() {
    // TODO: Implement getTerms() method.
  }
}