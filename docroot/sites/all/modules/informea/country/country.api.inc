<?php

/**
 * Hook to alter country contextual menu links.
 *
 * @param array $contextual_menu
 *   Contains links
 * @param $node
 *   Node to build the menu for
 */
function hook_country_contextual_menu_alter(&$contextual_menu, $node) {
  $link = array(
    '#type' => 'link',
    '#title' => 'Sample sub-menu',
    '#href' => 'countries/',
    '#attributes' => array('class' => array('list-group-item')),
    '#options' => array( 'html' => TRUE ),
  );
  $contextual_menu[] = $link;
}

function country_map_region($region) {
  $mappings = array(
    'africa' => 'Africa',
    'alps' => 'Europe',
    'amazonia' => 'Latin America and the Caribbean',
    // 'americas' => 'Americas',
    'andean states' => 'Latin America and the Caribbean',
    // 'antarctica' => 'Antarctica',
    'aral sea' => 'Asia and the Pacific',
    // 'arctic' => 'Arctic',
    'asia' => 'Asia and the Pacific',
    'asia and the pacific' => 'Asia and the Pacific',
    'atlantic ocean islands' => 'Asia and the Pacific',
    // 'baltic and north sea' => 'Baltic and North Sea',
    'benelux' => 'Europe',
    'black sea' => 'Europe',
    'caribbean' => 'Latin America and the Caribbean',
    'caspian sea' => 'Asia and the Pacific',
    'central africa' => 'Africa',
    'central america' => 'Latin America and the Caribbean',
    'central asia' => 'Asia and the Pacific',
    'central europe' => 'Europe',
    // 'cis (com. of indep. states)' => 'CIS (Com. of Indep. States)',
    'east asian seas' => 'Asia and the Pacific',
    'east pacific' => 'Asia and the Pacific',
    'eastern africa' => 'Asia and the Pacific',
    'eastern asia' => 'Asia and the Pacific',
    'eastern europe' => 'Europe',
    // 'eurasia' => 'Eurasia',
    'europe' => 'Europe',
    'european union countries' => 'Europe',
    'global' => 'Global',
    // 'guernsey (uk)' => 'Guernsey (UK)',
    'indian ocean' => 'Asia and the Pacific',
    // 'interregional' => 'interregional',
    // 'interregional: western hemisphere' => 'Interregional: Western Hemisphere',
    // 'latin america and the caribbean' => 'Latin America and the Caribbean',
    // 'mediterranean' => 'Mediterranean',
    // 'mediterranean sea' => 'Mediterranean Sea',
    'melanesia' => 'Asia and the Pacific',
    'micronesia' =>  'Asia and the Pacific',
    'middle east' =>  'Asia and the Pacific',
    'north america' => 'North America',
    'north asia' => 'Asia and the Pacific',
    'north atlantic' => 'North America',
    'north east atlantic' => 'North America',
    'north pacific' => 'Asia and the Pacific',
    // 'north sea' => 'North Sea',
    'north-east atlantic' => 'North America',
    'north-east pacific' => 'Asia and the Pacific',
    'north-west pacific' => 'Asia and the Pacific',
    'northern africa' => 'Africa',
    'northern europe' => 'Europe',
    // 'oceania' => 'Oceania',
    'persian gulf' => 'Asia and the Pacific',
    'polynesia' => 'Asia and the Pacific',
    // 'red sea & gulf of aden' => 'Red Sea & Gulf of Aden',
    // 'regional' => 'Regional',
    'sahel' => 'Africa',
    'selected countries in africa' => 'Africa',
    'selected countries in europe' => 'Europe',
    'selected countries in latin america' => 'Latin America and the Caribbean',
    // 'south america' => 'South America',
    'south asian seas' => 'Asia and the Pacific',
    // 'south atlantic' => 'South Atlantic',
    // 'south east atlantic ocean' => 'South East Atlantic Ocean',
    'south pacific' => 'Asia and the Pacific',
    'south-eastern asia' => 'Asia and the Pacific',
    'south-eastern pacific' => 'Asia and the Pacific',
    'southeast asia' => 'Asia and the Pacific',
    'southern africa' => 'Africa',
    'southern asia' => 'Asia and the Pacific',
    'southern europe' => 'Europe',
    'west asia' => 'Asia and the Pacific',
    'western africa' => 'Africa',
    'western asia' => 'Asia and the Pacific',
    'western europe' => 'Europe',
  );
  $l_region = strtolower($region);
  if (array_key_exists($l_region, $mappings)) {
    return $mappings[$l_region];
  }
  else {
    drupal_set_message("Unable to map region: $region");
    return FALSE;
  }
}

/**
 * Retrive the list of regions associated to a list of countries
 *
 * @param array $countries
 *   Array of node IDs for country
 *
 * @return array
 *   Array of region taxonomy terms
 */
function country_get_regions_from_country($country_ids) {
  if (empty($country_ids)) {
    return array();
  }
  $ret = array();
  $load = array();
  foreach($country_ids as $nid) {
    $load[$nid] = (object)array(
      'nid' => $nid,
      'type' => 'country',
    );
  }
  $fields = field_info_instances('node', 'country');
  field_attach_load('node', $load, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_region']['field_id']));
  foreach($load as $node) {
    $w = entity_metadata_wrapper('node', $node);
    foreach($w->field_region->value() as $region) {
      $ret[$region->tid] = $region;
    };
  }
  return $ret;
}

function country_url_context($path) {
  $path = preg_replace('/([A-Za-z]{2})?\/?countries\/[A-Za-z]{2}\/?/', '', $path);
  $parts = explode('/', $path);
  return $parts[0];
}

function country_load_by_iso2($iso2) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->fieldCondition('field_country_iso2', 'value', $iso2)
    ->execute();
  if (!empty($result['node'])) {
    $nid = current($result['node'])->nid;
    $node = node_load($nid);
    return $node;
  }
  return FALSE;
}

function country_load_by_iso3($iso3) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->fieldCondition('field_country_iso3', 'value', $iso3)
    ->execute();
  if (!empty($result['node'])) {
    $nid = current($result['node'])->nid;
    $node = node_load($nid);
    return $node;
  }
  return FALSE;
}

function country_load_by_iso($iso) {
  if (!empty($iso)) {
    if(strlen($iso) == 2) {
      return country_load_by_iso2($iso);
    }
    if (strlen($iso) == 3) {
      return country_load_by_iso3($iso);
    }
  }
  return NULL;
}

function country_get_by_name($name) {
  $name = strtolower($name);
  $countries = &drupal_static(__FUNCTION__);
  if(empty($countries)) {
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'country')
      ->execute();
    if (isset($result['node'])) {
      $rows = node_load_multiple(array_keys($result['node']));
      foreach ($rows as $row) {
        $wrapper = entity_metadata_wrapper('node', $row);
        $countries[strtolower($wrapper->label())] = $row;
        $official = $wrapper->field_country_official_name->value();
        if (!empty($official)) {
          $countries[strtolower($official)] = $row;
        }
      }
    }
  }
  if(array_key_exists($name, $countries)) {
    return $countries[$name];
  } else {
    if (array_key_exists($name, $countries)) {
      return $countries[$name];
    }
  }
  return FALSE;
}


function country_get_view_country_related_content($nid, $display) {
  $args = array($nid);
  $view = views_get_view('country_related_content');
  $view->set_display($display);
  $view->set_arguments($args);
  $view->get_total_rows = TRUE;
  $view->pre_execute();
  $view->execute();
  return $view;
}

function country_get_view_country_related_content_count($nid, $display) {
  $view = country_get_view_country_related_content($nid, $display);
  return $view->total_rows;
}

function country_get_sites($id_country) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'geographical_site')
    ->fieldCondition('field_country', 'target_id', $id_country)
    ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_get_countries() {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldOrderBy('title_field', 'value')
    ->execute();
  if (isset($result['node'])) {
    return entity_load('node', array_keys($result['node']));
  }
  return array();
}

function country_get_countries_select_options() {
  $ret = array();
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'country')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldOrderBy('title_field', 'value')
    ->execute();
  if (isset($result['node'])) {
    $rows = $result['node'];
    $fields = field_info_instances('node', 'country');
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_country_iso2']['field_id']));
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
    $menu_object = menu_get_object();
    foreach ($rows as $nid => $node) {
      $label = field_get_items('node', $node, 'title_field');
      $label = isset($label[0]['value']) ? $label[0]['value'] : $node->title;
      $path = 'countries/' . $node->field_country_iso2[LANGUAGE_NONE][0]['value'];
      if (isset($menu_object->context)) {
        $path .= '/' . $menu_object->context;
      }
      $ret[url($path, array('absolute' => TRUE))] = $label;
    }
  }
  return $ret;
}

function country_get_legislation_statistics($id_country = NULL, $type = 'legislation') {
  $query = db_select('node', 'n')
    ->fields('td', array('tid'))
    ->condition('n.status', 1)
    ->condition('n.type', $type)
    ->groupBy('td.tid');

  $query->addExpression('COUNT(td.vid)', 'term_count');
  $query->join('field_data_field_type_of_text', 'tt', 'n.nid = tt.entity_id');
  $query->join('taxonomy_term_data', 'td', 'tt.field_type_of_text_tid = td.tid');
  if ($id_country) {
    $query->join('field_data_field_country', 'c', 'n.nid = c.entity_id');
    $query->condition('c.field_country_target_id', $id_country);
  }
  $results = $query->execute()->fetchAllKeyed();

  arsort($results);
  $ret = array();
  foreach($results as $tid => $count) {
    $term = taxonomy_term_load($tid);
    $term->count = $count;
    $ret[] = $term;
  }
  return $ret;
}


function country_get_court_decisions_statistics($id_country = NULL) {
  return country_get_legislation_statistics($id_country, 'court_decisions');
}

function country_get_court_literature_statistics($id_country = NULL) {
  $query = db_select('node', 'n')
    ->fields('td', array('tid'))
    ->condition('n.status', 1)
    ->condition('n.type', 'literature')
    ->groupBy('td.tid');

  $query->addExpression('COUNT(td.vid)', 'term_count');
  $query->join('field_data_field_literature_type', 'tt', 'n.nid = tt.entity_id');
  $query->join('taxonomy_term_data', 'td', 'tt.field_literature_type_tid = td.tid');
  if ($id_country) {
    $query->join('field_data_field_country', 'c', 'n.nid = c.entity_id');
    $query->condition('c.field_country_target_id', $id_country);
  }
  $results = $query->execute()->fetchAllKeyed();

  arsort($results);
  $ret = array();
  foreach($results as $tid => $count) {
    $term = taxonomy_term_load($tid);
    $term->count = $count;
    $ret[] = $term;
  }
  return $ret;
}

function country_data_get_member_party_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'member_party')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_action_plan_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'action_plan')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_national_report_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'national_report')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_legislation_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'legislation')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_literature_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'literature')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_court_decision_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'court_decisions')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}

function country_get_site_count($id_country) {
  return db_select('field_data_field_country')
    ->condition('bundle', 'geographical_site')
    ->condition('field_country_target_id', $id_country)
    ->countQuery()->execute()->fetchField();
}
