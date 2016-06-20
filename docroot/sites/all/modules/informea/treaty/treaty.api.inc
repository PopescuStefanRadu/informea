<?php

function treaty_url_match_node($path) {
  if (arg(0, $path) == 'treaties') {
    if ($node = treaty_load_by_odata_name(arg(1, $path))) {
      return $node;
    }
  } else if(strlen(arg(0, $path)) == 2) { // Assume language prefix @todo enhance
    if (arg(1, $path) == 'treaties') {
      if ($node = treaty_load_by_odata_name(arg(2, $path))) {
        return $node;
      }
    }
  }
  return FALSE;
}

function treaty_url_context($path) {
  if (preg_match('/^node/', $path)) {
    $path = preg_replace('/node\/?[0-9]*\/?/', '', $path);
    $parts = explode('/', $path);
  }
  else {
    $path = preg_replace('/([A-Za-z]{2})?\/?treaties\/[A-Za-z\-\_]*\/?/', '', $path);
    $parts = explode('/', $path);
  }
  foreach ($parts as $part) {
    if (in_array($part, array('print', 'text', 'protocols', 'decisions', 'parties', 'national-reports', 'action-plans', 'export'))) {
      return $part;
    }
  }
  return 'summary';
}

function treaty_load_by_odata_name($odata_name) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty')
                  ->fieldCondition('field_odata_identifier', 'value', $odata_name)
                  ->execute();
  if (!empty($result['node'])) {
    return node_load(current($result['node'])->nid);
  }
  return FALSE;
}

function treaty_get_child_protocols($id_treaty) {
  return EdwCacheDomain::cache_get_array('treaty', __FUNCTION__, function($id_treaty) {
    $ret = array();
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'treaty')
      ->fieldCondition('field_parent_treaty', 'target_id', $id_treaty)
      ->execute();
    if (!empty($result['node'])) {
      $ret = node_load_multiple(array_keys($result['node']));
      $wrapper = entity_metadata_wrapper('node', $id_treaty);
      $odata_identifier = $wrapper->field_odata_identifier->value();
      if ($odata_identifier == 'cbd') {
        // Add also 3rd level - the Kuala Lumpur to CBD
        if ($nkl = treaty_load_by_odata_name('NKL')) {
          foreach ($ret as &$treaty) {
            $w = entity_metadata_wrapper('node', $treaty->nid);
            if ($w->field_odata_identifier->value() == 'cartagena') {
              $treaty->protocols = array($nkl->nid => $nkl);
            }
          }
        }
      }
    }
    return $ret;
  }, $id_treaty);
}

function treaty_count_child_protocols($id_treaty) {
  return EdwCacheDomain::cache_get_array('treaty', __FUNCTION__, function($id_treaty) {
    $query = new EntityFieldQuery();
    $ret = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'treaty')
      ->fieldCondition('field_parent_treaty', 'target_id', $id_treaty)
      ->count()
      ->execute();
    $wrapper = entity_metadata_wrapper('node', $id_treaty);
    $odata_identifier = $wrapper->field_odata_identifier->value();
    if ($odata_identifier == 'cbd') {
      if ($nkl = treaty_load_by_odata_name('NKL')) {
        $ret += 1;
      }
    }
    return $ret;
  }, $id_treaty);
}

function treaty_get_reporting_obligations($id_treaty) {
  return array();
}

function treaty_count_reporting_obligations($id_treaty) {
  return 0;
}

function treaty_get_treaties() {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty')
                  ->fieldOrderBy('title_field', 'value')
                  ->execute();
  if (!empty($result['node'])) {
    $rows = node_load_multiple(array_keys($result['node']));
    return $rows;
  }
  return array();
}

function treaty_get_treaties_as_select_options() {
  $ret = array();
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'treaty')
    ->fieldCondition('field_odata_identifier', 'value', NULL, 'IS NOT NULL')
    ->propertyCondition('status', 1)
    ->fieldOrderBy('title_field', 'value')
    ->execute();
  if (!empty($result['node'])) {
    $rows = $result['node'];
    $fields = field_info_instances('node', 'treaty');
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
    field_attach_load('node', $rows, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_odata_identifier']['field_id']));
    $menu_object = menu_get_object();
    foreach ($rows as $nid => $node) {
      $label = field_get_items('node', $node, 'title_field');
      $label = isset($label[0]['value']) ? $label[0]['value'] : $node->title;
      $path = 'treaties/' . $node->field_odata_identifier[LANGUAGE_NONE][0]['value'];
      if (isset($menu_object->context)) {
        $path .= '/' . $menu_object->context;
      }
      $ret[url($path, array('absolute' => TRUE))] = $label;
    }
  }
  return $ret;
}

function treaty_get_treaty_text($id_treaty) {
  $query = new EntityFieldQuery();
  // Retrieve treaty articles
  $articles = $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'treaty_article')
                  ->fieldCondition('field_treaty', 'target_id', $id_treaty)
                  ->fieldOrderBy('field_sorting_order', 'value')
                  ->execute();
  if (isset($articles['node'])) {
    $articles = node_load_multiple(array_keys($articles['node']));
    // Retrieve paragraphs for each article
    foreach ($articles as &$article) {
      $paragraphs = treaty_get_article_paragraphs($article->nid);
      $article->official_title = treaty_format_article_title($article);
      $article->paragraphs = $paragraphs;
    }
  }
  return $articles;
}

function treaty_get_article_paragraphs($id_article) {
  $query = new EntityFieldQuery();
  // Retrieve treaty articles
  $paragraphs = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'treaty_paragraph')
                    ->fieldCondition('field_parent_treaty_article', 'target_id', $id_article)
                    ->fieldOrderBy('field_sorting_order', 'value')
                    ->execute();
  return isset($paragraphs['node']) ? node_load_multiple(array_keys($paragraphs['node'])) : array();
}

function treaty_format_article_title($article) {
  $w = entity_metadata_wrapper('node', $article);
  $number = '';
  $order = $w->field_official_order->value();
  if (!empty($order)) {
    $number = $order;
    if(substr($number, -1) !== '.') {
      $number .= '. ';
    }
  }
  return sprintf('%s %s', $number, $w->label());
}

function treaty_format_meeting_description($meeting) {
  $w = entity_metadata_wrapper('node', $meeting);
  $description = array(
    '#theme' => 'item_list',
    '#attributes' => array('class' => array('list-inline', 'meta'))
  );
  $description['#items'][] = format_date(strtotime($w->event_calendar_date->value()['value']), 'short');
  if ($location = $w->field_location->value()) {
    $description['#items'][] = $location;
  }
  if ($city = $w->field_city->value()) {
    $description['#items'][] = $city;
  }
  if ($country = $w->field_country->value()) {
    if (!empty($country[0])) {
      $description['#items'][] = $country[0]->title;
    }
  }
  if (!empty($meeting->decisions)) {
    $description['#items'][] = format_plural(count($meeting->decisions), 'one decision', '@count decisions');
  }
  return drupal_render($description);
}
