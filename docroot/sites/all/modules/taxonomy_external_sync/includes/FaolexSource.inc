<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

use \Drupal\taxonomy_external_sync\plugin\SourceInterface;

class FaolexSource implements SourceInterface {

  private $available_languages = [
    'en' => 'English',
    'fr' => 'French',
    'es' => 'Spanish',
    'ar' => 'Arabic',
    'zh' => 'Chinese',
  ];

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
      'Scope_Note' => 'Scope note',
      'Exclude_from_External_Faolex' => 'Exclude from External Faolex',
      'Country_ISO_Code' => 'Country ISO Code',
      'Country_ISO2_Code' => 'Country ISO2 Code',
      'Country_ISO3_Code' => 'Country ISO3 Code',
      'Region' => 'Region',
      'Region_Countries' => 'Region Countries',
      'Exclude_from_Ecolex' => 'Exclude from Ecolex',
      'Language_ISO_Code' => 'Language ISO Code',
    );
  }

  function parseTerm($dictionary_term) {
    $term = new \stdClass();
    foreach ($dictionary_term as $field => $value) {
      if (preg_match('/Name\_(..)\_../', $field, $matches) && array_key_exists($lang = $matches[1], $this->available_languages)) {
        if (isset($term->Name)) {
          $term->Name[$lang] = (string) $value;
        }
        else {
          $term->Name = [$lang => (string) $value];
        }
      }
      elseif (preg_match('/Region\_(..)\_../', $field, $matches) && array_key_exists($lang = $matches[1], $this->available_languages)) {
        if (isset($term->Region)) {
          $term->Region[$lang] = (string) $value;
        }
        else {
          $term->Region = [$lang => (string) $value];
        }
      }
      elseif (preg_match('/(.*)\_Variants/', $field, $matches) && in_array($matches[1], $this->available_languages)) {
        $lang = array_search($matches[1], $this->available_languages);
        if (isset($term->Variants)) {
          $term->Variants[$lang] = (string) $value;
        }
        else {
          $term->Variants = [$lang => (string) $value];
        }
      }
      elseif (preg_match('/(.*)\_Scope\_Note/', $field, $matches) && in_array($matches[1], $this->available_languages)) {
        $lang = array_search($matches[1], $this->available_languages);
        if (isset($term->Scope_Note)) {
          $term->Scope_Note[$lang] = (string) $value;
        }
        else {
          $term->Scope_Note = [$lang => (string) $value];
        }
      }
      elseif (is_array($value)) {
        // TODO: check why 'Code' property is not an array
        $term->{$field} = $value;
      }
      else {
        $term->{$field} = (string) $value;
      }
    }
    return $term;
  }

  function getTerms() {
    $terms = array();
    // TODO: Get URL from configuration
    $url = 'http://faolex.fao.org/cgi-bin/xml.exe?database=valid&search_type=query&table=all&query=T:des&format_name=@VALXML&lang=xmlf&page_header=@EXMLH&page_footer=@EXMLF&sort_name=@SNAME';
    try {
      $xml = simplexml_load_file($url);
      foreach ($xml->dictionary_term as $dictionary_term) {
        $terms[] = $this->parseTerm($dictionary_term);
      }
    }
    catch (\Exception $e) {
      watchdog_exception('taxonomy_external_sync', $e);
    }
    return $terms;
  }
}