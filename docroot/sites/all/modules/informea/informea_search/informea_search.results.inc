<?php

class InforMEASearchResultsGrouping {

  public function getResults($rows) {
    $results = array();
    foreach ($rows as $row) {
      if (empty($row->_entity_properties['type'])) {
        drupal_set_message('Unknown entity', 'warning');
        continue;
      }
      $nid = $row->entity;
      $bundle = $row->_entity_properties['type'];
      $node = node_load($nid);
      $node->original_result = $row;
      $wrapper = entity_metadata_wrapper('node', $node);

      $node->relevance = 0;
      $node->excerpt = NULL;
      if (!empty($row->_entity_properties['search_api_excerpt'])) {
        $node->excerpt = $row->_entity_properties['search_api_excerpt'];
      }
      if (!empty($row->_entity_properties['search_api_relevance'])) {
        $node->relevance = $row->_entity_properties['search_api_relevance'];
      }
      switch ($bundle) {
        case 'treaty':
          if (!array_key_exists($nid, $results)) {
            $node->articles = array();
            $node->national_reports = array();
            $node->action_plans = array();
            $results[$nid] = $node;
          }
          break;
        case 'treaty_article':
          if ($treaty = $wrapper->field_treaty->value()) {
            $treaty = $treaty[0];
            if (array_key_exists($treaty->nid, $results)) {
              $treaty = $results[$treaty->nid];
            }
            if (!isset($treaty->articles) || !array_key_exists($nid, $treaty->articles)) {
              $treaty->articles[$node->nid] = $node;
            }
            $results[$treaty->nid] = $treaty;
          }
        break;
        case 'treaty_paragraph':
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $results)) {
            $treaty = $results[$treaty->nid];
          }
          $article = $wrapper->field_parent_treaty_article->value();
          if (isset($treaty->articles) && array_key_exists($article->nid, $treaty->articles)) {
            $article = $treaty->articles[$article->nid];
          }
          if (!isset($article->paragraphs) || !array_key_exists($node->nid, $article->paragraphs)) {
            $article->paragraphs[$node->nid] = $node;
          }
          $treaty->articles[$article->nid] = $article;
          $results[$treaty->nid] = $treaty;
        break;
        case 'decision':
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          if ($treaty = current($treaty)) {
            if (array_key_exists($treaty->nid, $results)) {
              $treaty = $results[$treaty->nid];
            }
            if (!isset($treaty->decisions) || !array_key_exists($node->nid, $treaty->decisions)) {
              $treaty->decisions[$node->nid] = $node;
            }
            $results[$treaty->nid] = $treaty;
          }
          break;
        case 'decision_paragraph':
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $results)) {
            $treaty = $results[$treaty->nid];
          }
          if ($decision = $wrapper->field_parent_decision->value()) {
            if (isset($treaty->decisions) && array_key_exists($decision->nid, $treaty->decisions)) {
              $decision = $treaty->decisions[$decision->nid];
            }
            if (!isset($decision->paragraphs) || !array_key_exists($node->nid, $decision->paragraphs)) {
              $decision->paragraphs[$node->nid] = $node;
            }
            $treaty->decisions[$decision->nid] = $decision;
            $results[$treaty->nid] = $treaty;
          }
          break;
        case 'national_report':
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $results)) {
            $treaty = $results[$treaty->nid];
          }
          if (!isset($treaty->national_reports) || !array_key_exists($node->nid, $treaty->national_reports)) {
            $treaty->national_reports[$node->nid] = $node;
          }
          $results[$treaty->nid] = $treaty;
          break;
        case 'action_plan':
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $results)) {
            $treaty = $results[$treaty->nid];
          }
          if (!isset($treaty->action_plans) || !array_key_exists($node->nid, $treaty->action_plans)) {
            $treaty->action_plans[$node->nid] = $node;
          }
          $results[$treaty->nid] = $treaty;
          break;
        default:
          //drupal_set_message('[informea_search] Content bundle not handled: ' . $bundle, 'warning');
      }
    }
    return $results;
  }

  public static function view($row) {
    $aw = entity_metadata_wrapper('node', $row);
    $tags = $aw->field_informea_tags->value();

    $ret = array();
    // Articles
    $content = self::view_articles($row);
    if (!empty($content)) {
      array_unshift($content, array(
        '#type' => 'item',
        '#markup' => '<h3>' . t('Treaty articles') . '</h3>',
      ));
    }
    // Decisions
    $decisions = self::view_decisions($row);
    if (!empty($decisions)) {
      array_unshift($decisions, array(
        '#type' => 'item',
        '#markup' => '<h3>' . t('Decisions') . '</h3>',
      ));
      $content = array_merge($content, $decisions);
    }

    // National reports
    $national_reports = self::view_national_reports($row);
    if (!empty($national_reports)) {
      array_unshift($national_reports, array(
        '#type' => 'item',
        '#markup' => '<h3>' . t('National reports') . '</h3>',
      ));
      $content = array_merge($content, $national_reports);
    }

    // Action plans
    $action_plans = self::view_action_plans($row);
    if (!empty($action_plans)) {
      array_unshift($action_plans, array(
        '#type' => 'item',
        '#markup' => '<h3>' . t('Action plans') . '</h3>',
      ));
      $content = array_merge($content, $action_plans);
    }

    $elements = array(
      'header' =>
        treaty_url_logo($row)
        . $row->title
        . l(
          '[View]',
          treaty_url_text($row->nid),
          array(
            'html' => TRUE,
            'attributes' => array(
              'class' => array('permalink pull-right'),
            ),
          )
        ),
      'tags' => theme('treaty_text_tags', array('tags' => $tags)),
      '#children' => $content
    );

    if (empty($content)) {
//      $elements['body'] = t('Treaty is tagged with %term', array('%term' => $term->name));
    }
    $ret[$row->nid] = array(
      '#theme' => 'informea_bootstrap_collapse',
      '#elements' => array($row->nid => $elements),
      '#no-data-parent' => 1,
    );
    return $ret;
  }

  public static function view_articles($treaty) {
    $ret = array();
    if (!empty($treaty->articles)) {
      foreach ($treaty->articles as $row) {
        $aw = entity_metadata_wrapper('node', $row);
        $tags = $aw->field_informea_tags->value();

        $paragraphs = self::view_article_paragraphs($row, $treaty);
        $elements = array(
          'header' => $row->title . l(
              '[View]',
              treaty_url_article($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('permalink pull-right'),
                ),
              )
            ),
          'tags' => theme('treaty_text_tags', array('tags' => $tags)),
          '#children' => $paragraphs,
        );
        if (!empty($row->excerpt)) {
          $elements['body'] = $row->excerpt;
        }
        $ret[$row->nid] = array(
          '#theme' => 'informea_bootstrap_collapse',
          '#elements' => array($row->nid => $elements),
          '#no-data-parent' => 1,
        );
      }
    }
    return $ret;
  }

  protected static function view_article_paragraphs($article, $treaty) {
    $ret = array();
    if (!empty($article->paragraphs)) {
      $items = array();
      foreach ($article->paragraphs as $row) {
        if (!empty($row->excerpt)) {
          $items[] = $row->excerpt;
        }
      }
      $ret = array(
        '#theme' => 'item_list',
        '#type' => 'ol',
        '#items' => $items,
        '#attributes' => array('class' => array('paragraphs')),
      );
    }
    return $ret;
  }

  protected static function view_decisions($treaty) {
    $ret = array();
    if (!empty($treaty->decisions)) {
      foreach ($treaty->decisions as $row) {
        $w = entity_metadata_wrapper('node', $row);
        $tags = $w->field_informea_tags->value();
        $paragraphs = self::view_decision_paragraphs($row, $treaty);
        $elements = array(
          'header' => $row->title . l(
              '[View]',
              treaty_url_decision($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('permalink pull-right'),
                ),
              )
            ),
          'tags' => theme('treaty_text_tags', array('tags' => $tags)),
          '#children' => $paragraphs,
        );
        $body = '';
        if (!empty($row->excerpt)) {
          $body = $row->excerpt;
        }
        if ($files = $w->field_files->value()) {
          $fr = field_view_field('node', $row, 'field_files', 'teaser');
          $body .= drupal_render($fr);
        }
        $elements['body'] = $body;
        $ret[$row->nid] = array(
          '#theme' => 'informea_bootstrap_collapse',
          '#elements' => array($row->nid => $elements),
          '#no-data-parent' => 1,
        );
      }
    }
    return $ret;
  }

  protected static function view_decision_paragraphs($decision) {
    $ret = array();
    if (!empty($decision->paragraphs)) {
      $items = array();
      foreach ($decision->paragraphs as $row) {
        if (!empty($row->excerpt)) {
          $items[] = $row->excerpt;
        }
      }
      $ret = array(
        '#theme' => 'item_list',
        '#type' => 'ol',
        '#items' => $items,
        '#attributes' => array('class' => array('paragraphs')),
      );
    }
    return $ret;
  }

  public static function view_national_reports($treaty) {
    $ret = array();
    if (!empty($treaty->national_reports)) {
      foreach ($treaty->national_reports as $row) {
        $w = entity_metadata_wrapper('node', $row);
        $tags = $w->field_informea_tags->value();
        $body = '';
        $elements = array(
          'header' =>
            $row->title
            . l(
              '[View]',
              treaty_url_national_report($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('permalink pull-right'),
                ),
              )
            ),
          'tags' => theme('treaty_text_tags', array('tags' => $tags)),
        );
        if (!empty($row->excerpt)) {
          $body .= $row->excerpt;
        }
        else {
          // report missing excerpt
          // dpm($row);
          // dpm($row);
        }
        if ($files = $w->field_files->value()) {
          $fr = field_view_field('node', $row, 'field_files', 'teaser');
          $body .= drupal_render($fr);
        }
        $elements['body'] = $body;
        $ret[$row->nid] = array(
          '#theme' => 'informea_bootstrap_collapse',
          '#elements' => array($row->nid => $elements),
          '#no-data-parent' => 1,
        );
      }
    }
    return $ret;
  }

  public static function view_action_plans($treaty) {
    $ret = array();
    if (!empty($treaty->action_plans)) {
      foreach ($treaty->action_plans as $row) {
        $w = entity_metadata_wrapper('node', $row);
        $tags = $w->field_informea_tags->value();
        $body = '';
        $elements = array(
          'header' =>
            $row->title
            . l(
              '[View]',
              treaty_url_action_plan($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('permalink pull-right'),
                ),
              )
            ),
          'tags' => theme('treaty_text_tags', array('tags' => $tags)),
        );
        if (!empty($row->excerpt)) {
          $body .= $row->excerpt;
        }
        else {
          // report missing excerpt
          // dpm($row);
          // dpm($row);
        }
        if ($files = $w->field_files->value()) {
          $fr = field_view_field('node', $row, 'field_files', 'teaser');
          $body .= drupal_render($fr);
        }
        $elements['body'] = $body;
        $ret[$row->nid] = array(
          '#theme' => 'informea_bootstrap_collapse',
          '#elements' => array($row->nid => $elements),
          '#no-data-parent' => 1,
        );
      }
    }
    return $ret;
  }
}
