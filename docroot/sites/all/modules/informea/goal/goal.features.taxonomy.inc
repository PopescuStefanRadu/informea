<?php
/**
 * @file
 * goal.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function goal_taxonomy_default_vocabularies() {
  return array(
    'geg_theme' => array(
      'name' => 'GEG Theme',
      'machine_name' => 'geg_theme',
      'description' => 'Themes related to GEGs',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 1,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'goal_sources' => array(
      'name' => 'Goal sources',
      'machine_name' => 'goal_sources',
      'description' => 'Where this goal comes from  (MDG, Aichi, Rio +20, SDG etc.)',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 5,
      'language' => 'und',
      'i18n_mode' => 1,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'informea_themes' => array(
      'name' => 'InforMEA themes',
      'machine_name' => 'informea_themes',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 7,
      'language' => 'und',
      'i18n_mode' => 1,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'type_of_goal' => array(
      'name' => 'Type of Goal',
      'machine_name' => 'type_of_goal',
      'description' => 'Goal, Target or Indicator',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 6,
      'language' => 'und',
      'i18n_mode' => 1,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
