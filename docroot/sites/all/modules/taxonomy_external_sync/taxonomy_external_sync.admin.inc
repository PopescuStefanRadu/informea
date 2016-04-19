<?php


function taxonomy_external_sync_taxonomy_form_element($form, $form_state) {
  $ret = array();
  $ret['taxonomy_external_sync'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synchronise with external data source'),
    '#prefix' => '<div id="wrapper-taxonomy-external-sync-plugins">',
    '#suffix' => '</div>',
  );

  $ret['taxonomy_external_sync']['taxonomy_external_sync_enable'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable',
    '#ajax' => array(
      'callback' => 'taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback',
      'wrapper' => 'wrapper-taxonomy-external-sync-plugins',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  if (!empty($form_state['values']['taxonomy_external_sync_enable'])) {
    $vocabulary = $form['#vocabulary'];
    $options = array();
    $plugins = taxonomy_external_sync_source_plugins();
    /**
     * @var string $machine_name
     * @var \Drupal\taxonomy_external_sync\plugin\SourceInterface $ob
     */
    foreach ($plugins as $machine_name => $ob) {
      $options[$machine_name] = $ob->getName();
    }
    $selected = NULL;
    if (!empty($form_state['values']['taxonomy_external_sync_plugin'])) {
      $selected = $form_state['values']['taxonomy_external_sync_plugin'];
    }
    $ret['taxonomy_external_sync']['taxonomy_external_sync_plugin'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('Source'),
      '#required' => TRUE,
      '#visible' => FALSE,
      '#default_value' => $selected,
      '#ajax' => array(
        'callback' => 'taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback',
        'wrapper' => 'wrapper-taxonomy-external-sync-plugins',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
    /** @var \Drupal\taxonomy_external_sync\plugin\SourceInterface $plugin */
    if ($selected && $plugin = $plugins[$selected]) {
      $ret['taxonomy_external_sync']['plugin'] = array(
        '#type' => 'fieldset',
        '#title' => t('Configuration')
      );
      $ret['taxonomy_external_sync']['plugin']['description'] = array(
        '#type' => 'item',
        '#markup' => '<div>' . $plugin->getDescription() . '</div>',
      );
      if ($plugin_form = $plugin->getConfigurationForm()) {
        foreach ($plugin_form as $key => $element) {
          $ret['taxonomy_external_sync']['plugin'][$key] = $element;
        }
      }
      // Mappings
      $destination_fields = taxonomy_external_sync_get_taxonomy_fields($vocabulary);
      ksort($destination_fields);
      $ret['taxonomy_external_sync']['plugin']['mappings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Mappings'),
      );
      foreach ($destination_fields as $field_name => $label) {
        $options = array('' => t('-- Not mapped --'));
        if ($source_fields = $plugin->getFieldNames()) {
          $options += $source_fields;
        }
        $ret['taxonomy_external_sync']['plugin']['mappings'][$field_name] = array(
          '#type' => 'select',
          '#options' => $options,
          '#title' => $label,
          '#attributes' => array('class' => array('select2-excluded')),
        );
      }
    }
  }
  return $ret;
}

function taxonomy_external_sync_taxonomy_form_element_plugins_ajax_callback($form, $form_state) {
  return $form['taxonomy_external_sync'];
}
