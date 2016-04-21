<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

use \Drupal\taxonomy_external_sync\plugin\SourceInterface;

class FaolexSource implements SourceInterface {

  function setConfiguration(array $config) {
    // TODO: Implement setConfiguration() method.
  }

  function getConfigurationForm($vocabulary, $form_state) {
    // TODO: Implement getConfigurationForm() method.
  }

  function getName() {
    return 'FAOLEX web-service consumer';
  }

  function getDescription() {
    return t('Imports terms from the XML provided by FAOLEX.');
  }

  function getFieldNames() {
    // TODO: Implement getFieldNames() method.
  }

  function getTerms() {
    // TODO: Implement getTerms() method.
  }
}