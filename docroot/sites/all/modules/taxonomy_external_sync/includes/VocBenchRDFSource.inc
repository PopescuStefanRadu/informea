<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

use \Drupal\taxonomy_external_sync\plugin\SourceInterface;

class VocBenchRDFSource implements SourceInterface {

  function setConfiguration(array $config) {
    // TODO: Implement setConfiguration() method.
  }

  /** @inheritdoc */
  function getConfigurationForm($vocabulary, $form_state) {
    $ret = array(
      'url' => array(
        '#title' => t('Enter RDF URL'),
        '#type' => 'textfield',
        '#size' => 100,
        '#default_value' => !empty($vocabulary->tes['plugin_config']['url']) ? $vocabulary->tes['plugin_config']['url'] : NULL,
      )
    );
    $destination_fields = taxonomy_external_sync_get_taxonomy_fields($vocabulary->machine_name);
    $options = array('' => t('-- Please select --'));
    foreach($destination_fields as $field_name => $label) {
      $options[$field_name] = $label;
    }
    $ret['id_field'] = array(
      '#title' => t('Identifier field'),
      '#description' => t('Select the local field where the remote indentifier is stored to track remote subsequent updates to the terms'),
      '#type' => 'select',
      '#options' => $options,
      '#required' => TRUE,
      '#default_value' => !empty($vocabulary->tes['plugin_config']['id_field']) ? $vocabulary->tes['plugin_config']['id_field'] : NULL,
    );
    return $ret;
  }

  function getName() {
    return 'VocBench RDF';
  }

  function getDescription() {
    return t('Imports terms from XML RDF containing reified labels');
  }

  function getFieldNames() {
    return array(
      'prefLabel' => 'skos:prefLabel - multilingual',
      'altLabel' => 'skos:altLabel - multilingual',
      'definition' => 'skos:definition - multilingual',
      'related' => 'skos:related',
      'status' => 'skos:status',
      'relatedMatch' => 'skos:relatedMatch - External term URI'
    );
  }

  function getTerms() {
    // TODO: Implement getTerms() method.
  }
}
