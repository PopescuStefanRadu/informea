<?php

/**
 * Class NationalPlansODataMigrateItem handles NationalPlans specific properties.
 */
class NationalPlansODataMigrateItem extends ODataMigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($id) {
    $ob = parent::getItem($id, '$expand=title');
    $title_langs = array();
    $titles = array();
    $title_orig = NULL;
    $values = $this->getComplexProperty($ob, 'title');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        if (!empty($value->value)) {
          $title_langs[] = $value->language;
          $titles[] = $value->value;
          if ($value->language == 'en') {
            $title_orig = $value->value;
          }
        }
      }
    }
    $ob->title_langs = $title_langs;
    $ob->title = $titles;
    if ($title_orig) {
      $ob->title_orig = $title_orig;
    }
    else {
      $ob->title_orig = empty($titles) ? '' : $titles[0];
    }
    if (!property_exists($ob,'submission')) {
      $ob->submission = '';
    }
    if (!property_exists($ob,'updated')) {
      $ob->updated = '';
    }

    $new_files = array();
    $files_language = array();
    $values = $this->getComplexProperty($ob, 'files');
    if (!empty($values) && is_array($values)) {
      foreach ($values as $value) {
        $new_files[] = $value->url;
        $files_language[] = property_exists($value, 'language') ? $value->language : 'en';
      }
    }
    $ob->files = $new_files;
    $ob->files_language = $files_language;
    return $ob;
  }
}