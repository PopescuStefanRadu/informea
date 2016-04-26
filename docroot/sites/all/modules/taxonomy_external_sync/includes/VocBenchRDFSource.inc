<?php

namespace Drupal\taxonomy_external_sync\plugin\source;

use \Drupal\taxonomy_external_sync\plugin\SourceInterface;

class VocBenchRDFSource implements SourceInterface {

  // The configuration part should be refactored because it is the same as in FaolexSource
  private $available_languages = [
    'en' => 'English',
    'fr' => 'French',
    'es' => 'Spanish',
    'ar' => 'Arabic',
    'zh' => 'Chinese',
  ];

  private $id_field = NULL;
  private $url = NULL;

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
  }

  /** @inheritdoc */
  function getConfigurationForm($vocabulary, $form_state) {
    $ret = array(
      'url' => array(
        '#title' => t('Enter RDF URL'),
        '#type' => 'textfield',
        '#size' => 100,
        '#required' => TRUE,
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

  function getIdField() {
    return $this->id_field;
  }

  function getFieldNames() {
    return array(
      'prefLabel' => 'skos:prefLabel - multilingual',
      'altLabel' => 'skos:altLabel - multilingual',
      'definition' => 'skos:definition - multilingual',
      'related' => 'skos:related',
      'status' => 'skos:status',
      'relatedMatch' => 'skos:relatedMatch - External term URI',
      'broader' => 'skos:broader',
      'uri' => 'Term URI',
    );
  }

  function getTerms() {
    $terms = $this->loadCachedRDF($this->url);
    return $terms;
  }

  private function loadCachedRDF($rdf) {
    $thesaurus = NULL;
    $data = array();
    if ($cache = cache_get(__FUNCTION__, 'cache')) {
      $data = $cache->data;
    }
    if (!empty($data[$rdf])) {
      return $data[$rdf];
    }
    else {
      $thesaurus = $this->loadRDF($rdf);
      if ($thesaurus) {
        $data[$rdf] = $thesaurus;
        cache_set(__FUNCTION__, $data, 'cache', time() + 3600);
      }
    }
    return $thesaurus;
  }

  private function loadRDF($rdf) {
    if (!easyrdf()) {
      drupal_set_message(t('EasyRdf library is not available.'), 'error');
      return FALSE;
    }
    \EasyRdf_Namespace::set('vb', 'http://art.uniroma2.it/ontologies/vocbench#');

    try {
      $graph = \EasyRdf_Graph::newAndLoad($rdf);
      $resources = $graph->resources();
    }
    catch(\Exception $e) {
      drupal_set_message("Failed to parse RDF file $rdf");
      return NULL;
    }

    $terms = array();
    /**
     * @var string $key
     * @var \EasyRdf_Resource $resource
     */
    foreach ($resources as $key => $resource) {
      if ($resource->type() == 'skos:Concept') {
        $term = new \stdClass();
        $term->broader = NULL;
        $term->uri = $key;
        $term->prefLabel = array();
        $term->altLabel = array();
        $term->status = NULL;
        $term->definition = array();
        $term->relatedMatch = array();
        $term->related = array();

        // skos:broader
        if ($uri = $resource->get('skos:broader')) {
          $term->broader = (string) $uri;
        }

        // skos:prefLabel
        if ($prefLabels = $resource->allResources('skosxl:prefLabel')) {
          foreach($prefLabels as $prefLabel) {
            /** @var EasyRdf_Literal $lit */
            $lit = $prefLabel->get('skosxl:literalForm');
            $term->prefLabel[$lit->getLang()] = $lit->getValue();
          }
        }

        if (empty($term->prefLabel['en'])) {
          watchdog('thesaurus', 'Invalid VB term without english preffered label: !uri', array('!uri' => $key), WATCHDOG_WARNING);
        }

        // skos:altLabel
        if ($altLabels = $resource->allResources('skosxl:altLabel')) {
          foreach($altLabels as $altLabel) {
            /** @var EasyRdf_Literal $lit */
            $lit = $altLabel->get('skosxl:literalForm');
            $term->altLabel[$lit->getLang()][] = $lit->getValue();
          }
        }

        // skos:definition
        if ($definitions = $resource->allResources('skos:definition')) {
          foreach($definitions as $definition) {
            if ($value = $definition->get('rdf:value')) {
              $term->definition[$value->getLang()][] = $value->getValue();
            }
            else {
              // @todo: Ignore orphaned triple (missing rdf:value)
            }
          }
        }

        // skos:relatedMatch - external thesauri
        if ($relatedMatches = $resource->allResources('skos:relatedMatch')) {
          foreach($relatedMatches as $relatedMatch) {
            $term->relatedMatch[] = $relatedMatch->getUri();
          }
        }

        // skos:related - within same thesauri
        if ($related = $resource->allResources('skos:related')) {
          foreach($related as $r) {
            $term->related[] = $r->getUri();
          }
        }

        // vb:hasStatus
        if ($status = $resource->get('vb:hasStatus')) {
          $term->status = (string) $status;
        }

        $terms[$key] = $term;
      }
    }

    // Remove invalid parents (orphaned)
    foreach ($terms as $key => &$term) {
      if (isset($term->parent) && !isset($terms[$term->parent])) {
        unset($term->parent);
      }
    }
    return $terms;
  }
}
