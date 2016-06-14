<?php

// ToDo: Do we need to retrieve these tids programmatically matched by term name?
define('DRUSH_GOAL_SDG_TID', 1753);
define('DRUSH_GOAL_GOAL_TID', 1734);
define('DRUSH_GOAL_TARGET_TID', 1737);
define('DRUSH_GOAL_INDICATOR_TID', 1735);

/**
 * Implementation of hook_drush_command().
 */
function goal_drush_command() {
  $items = array();

  $items['informea-sdg-full-import'] = array(
    'drupal dependencies' => array('phpexcel'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'description' => 'SDG Full Import',
    'aliases' => array('sdg-fi'),
  );

  return $items;
}

function _goal_sdg_get_tags(array $tags, array $thesaurus_informea) {
  foreach ($tags as $key => $tag) {
    $tag = trim(preg_replace('/\s+/', ' ', $tag));
    if (empty($thesaurus_informea[$tag])) {
      if (!empty($tag)) {
        drush_log("Term \"{$tag}\" not found.", 'error');
      }
      unset($tags[$key]);
    }
    else {
      $tags[$key] = $thesaurus_informea[$tag];
    }
  }
  return $tags;
}

/**
 * @param array $info
 *  Array containing:
 *    - title_field
 *    - field_goal_source
 *    - field_goal_type
 *    - field_informea_tags
 *    - field_parent_goal
 *    - field_original_id
 */
function _goal_sdg_create_node($info) {
  $fields = [
    'field_goal_source' => [
      'lang' => LANGUAGE_NONE,
      'col' => 'tid',
    ],
    'field_parent_goal' => [
      'lang' => LANGUAGE_NONE,
      'col' => 'target_id',
    ],
    'title_field' => [
      'lang' => 'en',
      'col' => 'value',
    ],
    'field_original_id' => [
      'lang' => LANGUAGE_NONE,
      'col' => 'value',
    ],
  ];
  $fields['field_informea_tags'] = $fields['field_goal_type'] = $fields['field_goal_source'];
  $node = [
    'title' => $info['title_field'],
    'status' => '1',
    'type' => 'goal',
    'language' => 'en',
    'title_original' => $info['title_field'],
  ];

  foreach ($fields as $field => $det) {
    if (!empty($info[$field])) {
      if (is_array($info[$field])) {
        $node[$field] = [
          $det['lang'] => [],
        ];
        foreach ($info[$field] as $key => $val) {
          $node[$field][$det['lang']][$key] = [
            $det['col'] => $val,
          ];
        }
      }
      else {
        $node[$field] = [
          $det['lang'] => [
            0 => [
              $det['col'] => $info[$field],
            ],
          ],
        ];
      }
    }
  }
  $node = (object) $node;
  $node = node_submit($node);
  node_save($node);
  return $node;
}

function _goal_sdg_handle_item($item, $parent_tid = NULL) {
  $informea_tags = db_select('taxonomy_term_data', 't')
    ->fields('t', ['name', 'tid'])
    ->condition('t.vid', '14')
    ->execute()->fetchAllKeyed();
  $item['tags'] = _goal_sdg_get_tags($item['tags'], $informea_tags);
  $info = [
    'title_field' => $item['title'],
    'field_goal_source' => $item['source'],
    'field_goal_type' => $item['type'],
    'field_original_id' => $item['id'],
    'field_informea_tags' => $item['tags'],
  ];
  if (!empty($parent_tid)) {
    $info['field_parent_goal'] = $parent_tid;
  }
  $node = _goal_sdg_create_node($info);
  if (!empty($node->nid) && !empty($item['children'])) {
    foreach ($item['children'] as $child) {
      _goal_sdg_handle_item($child, $node->nid);
    }
  }
}

/**
 * Imports SDG goals, targets & indicators from SDG_datasheet.xlsx file.
 */
function drush_goal_informea_sdg_full_import() {
  $columns = [
    'goal_no' => 'SDG Goal No.',
    'goal_text' => 'SDG Goal Text',
    'goal_tags' => 'Goal LEO Terms; Existing',
    'target_no' => 'SDG Target No.',
    'target_text' => 'SDG Target Text',
    'target_tags' => 'Target LEO Terms; Existing',
    'indicator_no' => 'SDG Indicator No.',
    'indicator_text' => 'SDG Indicator Text',
    'indicator_tags' => 'Indicator LEO Terms; Existing',
  ];
  module_load_include('inc', 'phpexcel');
  $path = drupal_get_path('module', 'goal') . '/files/SDG_datasheet.xlsx';
  $data = phpexcel_import($path)[0];
  if (!is_array($data)) {
    drush_log("We could not get the data from the excel file.", 'error');
    return;
  }
  $goals = [];

  foreach ($data as $key => $row) {
    $missing = 0;
    foreach (['goal_text', 'target_text', 'indicator_text'] as $req_col) {
      if (empty($row[$columns[$req_col]])) {
        $missing ++;
      }
    }
    if ($missing > 0) {
      if ($missing < 3) {
        $rownum = $key + 2;
        drush_log("Found an empty column on row {$rownum}", 'error');
      }
      continue;
    }
    if (strlen($row[$columns['target_no']]) > 6) {
      $row[$columns['target_no']] = number_format((float)$row[$columns['target_no']],1,'.','');
      drush_log("Fixed id for target: {$row[$columns['target_no']]} {$row[$columns['target_text']]}", 'warning');
    }
    $goal = $row[$columns['goal_no']] . ' ' . $row[$columns['goal_text']];
    $target = $row[$columns['target_no']] . ' ' . $row[$columns['target_text']];
    $indicator = $row[$columns['indicator_no']] . ' ' . $row[$columns['indicator_text']];

    if (empty($goals[$goal])) {
      $goals[$goal] = [
        'title' => $goal,
        'id' => trim(str_replace(['Goal', '.'], '', $row[$columns['goal_no']])),
        'tags' => explode(',', $row[$columns['goal_tags']]),
        'source' => DRUSH_GOAL_SDG_TID,
        'type' => DRUSH_GOAL_GOAL_TID,
        'children' => [],
      ];
    }
    if (!array_key_exists($target, $goals[$goal]['children'])) {
      $goals[$goal]['children'][$target] = [
        'title' => $target,
        'id' => $row[$columns['target_no']],
        'tags' => explode(',', $row[$columns['target_tags']]),
        'source' => DRUSH_GOAL_SDG_TID,
        'type' => DRUSH_GOAL_TARGET_TID,
        'children' => [],
      ];
    }
    $goals[$goal]['children'][$target]['children'][] = [
      'title' => $indicator,
      'id' => $row[$columns['indicator_no']],
      'tags' => explode(',', $row[$columns['indicator_tags']]),
      'source' => DRUSH_GOAL_SDG_TID,
      'type' => DRUSH_GOAL_INDICATOR_TID,
      'children' => [],
    ];
  }

  foreach ($goals as $goal) {
    _goal_sdg_handle_item($goal);
  }
}
