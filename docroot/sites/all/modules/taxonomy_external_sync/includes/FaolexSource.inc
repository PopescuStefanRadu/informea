<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

use \Drupal\taxonomy_external_sync\plugin\SourceInterface;

class FaolexSource implements SourceInterface {

  function setConfiguration(array $config) {
    // TODO: Implement setConfiguration() method.
  }

  function getConfigurationForm($vocabulary, $form_state) {
    $ret = array(
      'url' => array(
        '#title' => t('Enter XML URL'),
        '#type' => 'textfield',
        '#size' => 300,
        '#required' => TRUE,
        '#default_value' => !empty($vocabulary->tes['plugin_config']['url']) ? $vocabulary->tes['plugin_config']['url'] : NULL,
      )
    );
    return $ret;
  }

  function getName() {
    return 'FAOLEX web-service consumer';
  }

  function getDescription() {
    return t('Imports terms from the XML provided by FAOLEX.');
  }

  function getFieldNames() {
    return array(
      'ValID' => 'Source ID',
      'Classification_Sec_Area' => 'Classification Sec Area',
      'Code' => 'Code',
      'Name' => 'Name',
      'Variants' => 'Synonyms',
    );
  }

  function getTerms() {
    // TODO: Implement getTerms() method.
  }
}