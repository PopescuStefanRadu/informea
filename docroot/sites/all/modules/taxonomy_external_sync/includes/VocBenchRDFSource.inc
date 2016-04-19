<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

class VocBenchRDFSource implements \Drupal\taxonomy_external_sync\plugin\SourceInterface {


  function setConfiguration(array $config) {
    // TODO: Implement setConfiguration() method.
  }

  /** @inheritdoc */
  function getConfigurationForm($vocabulary, $form_state) {
    return array(
      'url' => array(
        '#title' => t('Enter RDF URL'),
        '#type' => 'textfield',
        '#size' => 100,
        '#default_value' => !empty($vocabulary->tes['plugin_config']['url']) ? $vocabulary->tes['plugin_config']['url'] : NULL,
      )
    );
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
