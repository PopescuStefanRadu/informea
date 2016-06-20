<?php

/**
 * Decisions count for treaty.
 *
 * @param $id_treaty
 *
 * @return integer
 *   Number of decisions or -1 if n/a
 */
function decision_count_treaty_decisions($id_treaty) {
  if (treaty_can_have_decisions($id_treaty)) {
    $decisions = 0;
    $meetings = decision_get_treaty_decisions_group_by_meeting($id_treaty);
    foreach ($meetings as $meeting) {
      $decisions += count($meeting->decisions);
    }
    return $decisions;
  }
  return 0;
}

function decision_get_treaty_decisions($id_treaty) {
  $query  = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'decision')
    ->fieldCondition('field_treaty', 'target_id', $id_treaty)
    ->execute();
  return isset($result['node']) ? node_load_multiple(array_keys($result['node'])) : array();
}

function decision_get_treaty_decisions_group_by_meeting2($id_treaty) {
  $ret = array();
  $fields = field_info_instances('node', 'decision');

  $allowed_status = array(840 /* active */, 846 /* adopted */, 845 /* amended */);
  $query = db_select('node', 'a')->fields('a', array('nid', 'title'))->fields('m', array('field_meeting_target_id'));
  $query->join('field_data_field_treaty', 'b', 'b.entity_id = a.nid');
  $query->leftJoin('field_data_field_sorting_order', 'c', 'c.entity_id = a.nid');
  $query->leftJoin('field_data_field_decision_status', 'd', 'd.entity_id = a.nid');
  $query->innerJoin('field_data_field_meeting', 'm', 'm.entity_id = a.nid');
  $query->innerJoin('field_data_event_calendar_date', 'md', 'm.field_meeting_target_id = md.entity_id');
  $query->condition('a.type', 'decision');
  $query->condition('b.field_treaty_target_id', $id_treaty);
  $query->condition('d.field_decision_status_tid', $allowed_status, 'IN');
  // Keep only COP meetings for CBD, Cartagena and Nagoya
  if (in_array($id_treaty, array(255 /* CBD *//* , 262 Cartagena *//* , 263 Nagoya */))) {
    $cop_term = taxonomy_get_term_by_name('cop', 'event_type');
    $cop_term = reset($cop_term);
    $query->innerJoin('field_data_field_event_type', 'et', 'm.field_meeting_target_id = et.entity_id');
    $query->condition('et.field_event_type_tid', $cop_term->tid);
  }
  $query->groupBy('a.nid');
  $query->orderBy('md.event_calendar_date_value', 'DESC');
  $query->orderBy('c.field_sorting_order_value', 'ASC');

  $decisions = $query->execute()->fetchAllAssoc('nid');
//  dpm((string)$query, $id_treaty);
  foreach($decisions as $nid => $row) {
    if (!array_key_exists($row->field_meeting_target_id, $ret)) {
      $meeting = node_load($row->field_meeting_target_id);
      $meeting->decisions = array();
      $ret[$row->field_meeting_target_id] = $meeting;
    }
    else {
      $meeting = $ret[$row->field_meeting_target_id];
    }
    $decision = (object)array('nid' => $nid, 'vid' => NULL, 'type' => 'decision', 'title' => $row->title);
    $meeting->decisions[$nid] = $decision;
  }

  foreach ($ret as $meeting) {
    field_attach_load('node', $meeting->decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
    field_attach_load('node', $meeting->decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
    field_attach_load('node', $meeting->decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_type']['field_id']));
    field_attach_load('node', $meeting->decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
  }
  return $ret;
}


function decision_get_treaty_decisions_group_by_meeting($id_treaty) {

  return decision_get_treaty_decisions_group_by_meeting2($id_treaty);

  $ret = array();
  $CBD_nids = array(255 /* CBD */, 262 /* Cartagena */, 263 /* Nagoya */);
  $cop_term = taxonomy_get_term_by_name('cop', 'event_type');
  $cop_term = reset($cop_term);
  $recommendation_term = taxonomy_get_term_by_name('recommendation', 'decision_type');
  $recommendation_term = reset($recommendation_term);

  // Get all the meetings with decisions
  $q = db_select('field_data_field_treaty', 'a')->fields('a', array('entity_id'));
  $q->innerJoin('field_data_field_meeting', 'b', 'a.entity_id = b.field_meeting_target_id');
  $q->innerJoin('field_data_field_treaty', 'c', 'a.field_treaty_target_id = c.field_treaty_target_id');
  $q->innerJoin('field_data_event_calendar_date', 'd', 'a.entity_id = d.entity_id ');
  $q->condition('a.field_treaty_target_id', $id_treaty);
  $q->condition('a.bundle', 'event_calendar');
  $q->condition('c.bundle', 'decision');
  $q->groupBy('a.entity_id');
  $q->orderBy('d.event_calendar_date_value', 'DESC');
  $meetings = $q->execute()->fetchCol();
  $meetings = node_load_multiple($meetings);

  $allowed_status = array(840 /* active */, 846 /* adopted */, 845 /* amended */);
  $fields = field_info_instances('node', 'decision');
  foreach ($meetings as $meeting) {
    if (in_array($id_treaty, $CBD_nids)) {
      // Keep only COP meetings for CBD, Cartagena and Nagoya
      if (empty($meeting->field_event_type) || $meeting->field_event_type[LANGUAGE_NONE][0]['tid'] != $cop_term->tid) {
        continue;
      }
    }
    // Get the decisions for each meeting, ordered by draggable views.
    $q = db_select('field_data_field_meeting', 'a')->fields('a', array('entity_id'))->fields('n', array('title'));
    $q->join('node', 'n', "a.entity_id = n.nid AND n.type = 'decision'");
    $q->leftJoin('field_data_field_sorting_order', 'b', 'b.entity_id = a.entity_id');
    $q->condition('a.bundle', 'decision');
    $q->condition('a.field_meeting_target_id', $meeting->nid);
    $q->orderBy('b.field_sorting_order_value', 'ASC');
    $dids = $q->execute()->fetchAllKeyed();
    $decisions = array();
    foreach($dids as $key => $ob) {
      $decisions[$key] = (object)array('nid' => $key, 'vid' => NULL, 'type' => 'decision');
    }
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_number']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_status']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_decision_type']['field_id']));
    field_attach_load('node', $decisions, FIELD_LOAD_CURRENT, array('field_id' => $fields['title_field']['field_id']));
    // Remove non-active decisions
    $decisions = array_filter($decisions, function ($d) use ($allowed_status) {
      $status = !empty($d->field_decision_status[LANGUAGE_NONE][0]['tid']) ? $d->field_decision_status[LANGUAGE_NONE][0]['tid'] : '';
      return in_array($status, $allowed_status);
    });

    if (in_array($id_treaty, $CBD_nids)) {
      // Remove recommendations
      $decisions = array_filter($decisions, function ($d) use ($recommendation_term) {
        return $d->field_decision_type[LANGUAGE_NONE][0]['tid'] != $recommendation_term->tid;
      });
    }
    foreach ($decisions as $decision) {
      $decision->title = $dids[$decision->nid];
    }
    if (!empty($decisions)) {
      $meeting->decisions = $decisions;
      $ret[$meeting->nid] = $meeting;
    }
  }
  return $ret;
}
