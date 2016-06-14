<?php

function ws_consumer_odata_admin_config_form() {
  $form = array('#tree' => TRUE);
  /** @var ODataConsumerConfig $config */
  $config = ODataConsumerConfig::getConfiguration();
  $form['title'] = array(
    '#type' => 'item',
    '#markup' => '<h1>Configure data providers</h1>' .
      '<p>Use this form to configure URL endpoints to the OData services</p>'
  );

  $form['odata_page_size'] = array(
    '#type' => 'textfield',
    '#size' => 20,
    '#title' => t('Results per page'),
    '#default_value' => !empty($config['odata_page_size']) ? $config['odata_page_size'] : 100,
    '#description' => t('How many results to pull from service during a page request'),
    '#weight' => -10,
  );
  $meas = ODataConsumerConfig::getODataNames();
  $entities = ODataConsumerConfig::getEntityNames();
  asort($meas);
  foreach($meas as $mea) {
    $form['endpoints'][$mea] = array(
      '#type' => 'fieldset',
      '#title' => $mea . ' configuration',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['endpoints'][$mea]['default'] = array(
      '#type' => 'textfield',
      '#title' => t('Default/Common endpoint'),
      '#description' => t('Enter the endpoint common to all entities, if applicable'),
      '#default_value' => !empty($config['endpoints'][$mea]['default']) ? $config['endpoints'][$mea]['default'] : '',
    );
    foreach($entities as $entity) {
      $form['endpoints'][$mea][$entity] = array(
        '#type' => 'textfield',
        '#title' => t('Endpoint for ' . $entity),
        '#description' => t('Enter custom endpoint, leave empty to use default above'),
        '#default_value' => !empty($config['endpoints'][$mea][$entity]) ? $config['endpoints'][$mea][$entity] : '',
      );
    }
  }
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}


function ws_consumer_odata_admin_config_form_validate($form, &$form_state) {
  //@todo: validate endpoints using cURL?
}

function ws_consumer_odata_admin_config_form_submit($form, $form_state) {
  $current = ODataConsumerConfig::getConfiguration();
  $meas = ODataConsumerConfig::getODataNames();
  $entities = ODataConsumerConfig::getEntityNames();
  array_unshift($entities, 'default');
  asort($meas);
  $values = $form_state['values'];
  foreach($meas as $mea) {
    foreach($entities as $entity) {
      $current['endpoints'][$mea][$entity] = $values['endpoints'][$mea][$entity];
    }
  }
  $current['odata_page_size'] = $values['odata_page_size'];
  ODataConsumerConfig::saveConfiguration($current);
  drupal_set_message('Configuration successfully saved');
}


function ws_consumer_odata_admin_config_migrations_form() {
  $form = array('#tree' => FALSE);
  $form['title'] = array(
    '#type' => 'item',
    '#markup' => '<h1>Data import configuration</h1>' .
      '<p>Uncheck the items you wish to disable, then save configuration.</p>'
  );

  module_load_include('inc', 'ws_consumer_odata', 'ws_consumer_odata.migrate');
  $migrations = ws_consumer_odata_migrate_api();
  $groups = $migrations['groups'];
  ksort($groups);

  foreach($groups as $name => $data) {
    $form[$name] = array(
      '#type' => 'fieldset',
      '#title' => $data['title'],
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
  }

  foreach($migrations['migrations'] as $name => $config) {
    $group = $config['group_name'];
    $form[$group][$name] = array(
      '#type' => 'checkbox',
      '#title' => $config['odata_entity'] . ' (' . $name . ')',
      '#default_value' => ODataConsumerConfig::isEnabled($name),
    );
  }

  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

function ws_consumer_odata_admin_config_migrations_form_validate($form, &$form_state) {

}

function ws_consumer_odata_admin_config_migrations_form_submit($form, &$form_state) {
  $disabled = array();
  module_load_include('inc', 'ws_consumer_odata', 'ws_consumer_odata.migrate');
  $migrations = ws_consumer_odata_migrate_api();
  foreach($migrations['migrations'] as $name => $config) {
    if (empty($form_state['values'][$name])) {
      $disabled[$name] = 1;
    }
  }
  $config = ODataConsumerConfig::getConfiguration();
  $config['disabled'] = $disabled;
  ODataConsumerConfig::saveConfiguration($config);
  drupal_set_message('Configuration successfully saved');
}

function ws_consumer_odata_node_migrate_report($node) {
  $ret = array();
  $w = entity_metadata_wrapper('node', $node);
  $odata_name = $w->field_odata_identifier->value();
  module_load_include('inc', 'ws_consumer_odata', 'ws_consumer_odata.migrate');
  if (!module_load_include('inc', 'migrate_ui', 'migrate_ui.pages')) {
    drupal_set_message('Cannot find migrate_ui module!', 'error');
    return $ret;
  }

  $migrations = ws_consumer_odata_migrate_api();
  $links = array();
  foreach($migrations['migrations'] as $name => $config) {
    if(preg_match('/' . $odata_name . '/', $name) == 1) {
      $links[] = l($name, 'node/' . $node->nid . '/migrate', array('query' => array('id' => $name)));
    }
  }
  $machine_name = $_GET['id'];
  if (array_key_exists($machine_name, $migrations['migrations'])) {
    $migration = Migration::getInstance($machine_name);
    $ret['lastimport'] = array('#weight' => -10, '#type' => 'markup', '#markup' => 'Last import on: ' . check_plain($migration->getLastImported()));
    $messages = migrate_ui_messages(NULL, $machine_name);
    $messages['weight'] = 0;
    $ret['title'] = array('#weight' => -5, '#type' => 'markup', '#markup' => '<h2>' . $machine_name . '</h2>');
    $ret['messages'] = $messages;
  }
  $ret['links'] = array('#weight' => -20, '#theme' => 'item_list', '#items' => $links, '#title' => t('Select migration'));
  return $ret;
}
