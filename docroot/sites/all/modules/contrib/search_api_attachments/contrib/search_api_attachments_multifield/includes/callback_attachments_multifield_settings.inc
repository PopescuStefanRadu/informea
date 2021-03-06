<?php

/**
 * @file
 * Search API data alteration callback.
 */

class SearchApiAttachmentsMultifieldAlterSettings extends SearchApiAttachmentsAlterSettings {

  /**
   * {@inheritdoc}
   */
  public function alterItems(array &$items) {

    // Extension restriction.
    $exclude = array();
    foreach (explode(' ', $this->options['excluded_extensions']) as $ext) {
      $exclude[$ext] = file_get_mimetype('dummy.' . $ext);
    }

    // File size restriction.
    $max_file_size = parse_size($this->options['max_file_size']);

    // Get the multifield bundles.
    $multifields_instances = field_info_instances('multifield');
    $multifields = array_keys($multifields_instances);
    if (!empty($multifields_instances)) {
      foreach ($items as $id => &$item) {
        // Case of multifield fields.
        foreach ($multifields as $multifield) {
          if (isset($item->{$multifield})) {
            // Get the file fields of the multifield item.
            $file_fields = array();
            foreach (array_keys($multifields_instances[$multifield]) as $field_name) {
              $field_info = field_info_field($field_name);
              // Only if the field is file and should be indexed.
              if ($field_info['type'] == 'file') {
                $file_fields[] = $field_name;
              }
            }
            if (empty($file_fields)) {
              return;
            }
            $multifield_items = field_get_items($this->index->getEntityType(), $item, $multifield);
            if ($multifield_items) {
              // Index the files content.
              foreach ($file_fields as $file_field) {
                foreach ($multifield_items as $multifield_item) {
                  if (isset($multifield_item[$file_field]) && !empty($multifield_item[$file_field])) {
                    $files = array();
                    // Get the entity wrapper that have multifield with file fields.
                    $item_wrapper = entity_metadata_wrapper($this->index->getEntityType(), $item);
                    if (is_array($item_wrapper->{$multifield}->value())) {
                      foreach ($item_wrapper->{$multifield} as $delta => $multifield_wrapper) {
                        $files[] = $multifield_wrapper->{$file_field}->value();
                      }
                    }
                    else {
                      $files = array($item_wrapper->{$multifield}->{$file_field}->value());
                    }
                    if (!empty($files)) {
                      // Limit to the max number of value per field.
                      if (isset($this->options['number_indexed']) && $this->options['number_indexed'] != '0' && count($files) > $this->options['number_indexed']) {
                        $files = array_slice($files, 0, $this->options['number_indexed']);
                      }
                      foreach ($files as $file) {
                        // Private file restriction.
                        if (!$this->is_temporary($file) && !($this->options['excluded_private'] && $this->is_private($file))) {
                          // Extension restriction.
                          if (!in_array($file['filemime'], $exclude)) {
                            // File size restriction.
                            $file_size_errors = file_validate_size((object) $file, $max_file_size);
                            if (empty($file_size_errors)) {
                              $attachments = 'attachments_' . $file_field;
                              if (isset($item->{$attachments})) {
                                $item->{$attachments} .= ' ' . $this->getFileContent($file);
                              }
                              else {
                                $item->{$attachments} = $this->getFileContent($file);
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function propertyInfo() {
    $ret = array();
    if ($this->index->getEntityType() == 'file') {
      $ret['attachments_content'] = array(
        'label' => 'File content',
        'description' => 'File content',
        'type' => 'text',
      );
    }
    else {
      $fields = $this->getFileFields();
      foreach ($fields as $name => $field) {
        $ret['attachments_' . $name] = array(
          'label' => 'Attachment content: ' . $name,
          'description' => $name,
          'type' => 'text',
        );
      }
    }
    return $ret;
  }

  /**
   * {@inheritdoc}
   */
  protected function getFileFields() {
    $ret = array();
    foreach (field_info_fields() as $name => $field) {
      if ($field['type'] == 'file') {
        $ret[$name] = $field;
      }
    }
    return $ret;
  }
}
