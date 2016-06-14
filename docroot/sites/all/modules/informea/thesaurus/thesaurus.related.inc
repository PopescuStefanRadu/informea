<?php

class InforMEAThesaurusTermRelatedContent {
  protected $term = NULL;

  public function __construct($term) {
    $this->term = $term;
  }

  function getRelatedContent($term) {
    $items = db_select('field_data_field_informea_tags', 'a')->fields('a')->condition('field_informea_tags_tid', $term->tid)->execute()->fetchAll();
    $treaties = array();
    foreach($items as $item) {
      $wrapper = entity_metadata_wrapper($item->entity_type, $item->entity_id);
      switch($item->bundle) {
        case 'treaty_paragraph':
          $paragraph = node_load($item->entity_id);
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $treaties)) {
            $treaty = $treaties[$treaty->nid];
          }
          $article = $wrapper->field_parent_treaty_article->value();
          if (isset($treaty->articles) && array_key_exists($article->nid, $treaty->articles)) {
            $article = $treaty->articles[$article->nid];
          }
          if (!isset($article->paragraphs) || !array_key_exists($paragraph->nid, $article->paragraphs)) {
            $article->paragraphs[$paragraph->nid] = $paragraph;
          }
          $treaty->articles[$article->nid] = $article;
          $treaties[$treaty->nid] = $treaty;
        break;
        case 'decision_paragraph':
          $paragraph = node_load($item->entity_id);
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $treaties)) {
            $treaty = $treaties[$treaty->nid];
          }
          $decision = $wrapper->field_parent_decision->value();
          if (isset($treaty->decisions) && array_key_exists($decision->nid, $treaty->decisions)) {
            $decision = $treaty->decisions[$decision->nid];
          }
          if (!isset($decision->paragraphs) || !array_key_exists($paragraph->nid, $decision->paragraphs)) {
            $decision->paragraphs[$paragraph->nid] = $paragraph;
          }
          $treaty->decisions[$decision->nid] = $decision;
          $treaties[$treaty->nid] = $treaty;
        break;
        case 'treaty_article':
          $article = node_load($item->entity_id);
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $treaties)) {
            $treaty = $treaties[$treaty->nid];
          }
          if (!isset($treaty->articles) || !array_key_exists($article->nid, $treaty->articles)) {
            $treaty->articles[$article->nid] = $article;
          }
        break;
        case 'decision':
          $decision = node_load($item->entity_id);
          $treaty = $wrapper->field_treaty->value();reset($treaty);
          $treaty = current($treaty);
          if (array_key_exists($treaty->nid, $treaties)) {
            $treaty = $treaties[$treaty->nid];
          }
          if (!isset($treaty->decisions) || !array_key_exists($decision->nid, $treaty->decisions)) {
            $treaty->decisions[$decision->nid] = $decision;
          }
        break;
        case 'treaty':
          $treaty = node_load($item->entity_id);
          if (!array_key_exists($treaty->nid, $treaties)) {
            $treaties[$treaty->nid] = $treaty;
          }
        break;
        default:
          if (!user_is_anonymous()) {
            drupal_set_message('[thesaurus.related.inc] Related content bundle not handled: ' . $item->bundle, 'warning');
          }
      }
    }
    return array(
      'treaties' => $treaties,
    );
  }

  public static function view($term, $relatedContent) {
    $ret = array();
    foreach($relatedContent as $id => $row) {
      switch($row->type) {
        case 'treaty':
          // Articles
          $content = self::view_articles($term, $row);
          if (!empty($content)) {
            array_unshift($content, array(
              '#type' => 'item',
              '#markup' => '<h3>' . t('Treaty articles') . '</h3>',
            ));
          }
          // Decisions
          $decisions = self::view_decisions($term, $row);
          if (!empty($decisions)) {
            array_unshift($decisions, array(
              '#type' => 'item',
              '#markup' => '<h3>' . t('Decisions') . '</h3>',
            ));
            $content = array_merge($content, $decisions);
          }

          $elements = array(
            'header' =>
                treaty_url_logo($row)
                . $row->title
                . l(
                '<i class="glyphicon glyphicon-link"></i>',
                treaty_url_text($row->nid),
                array(
                  'html' => TRUE,
                  'attributes' => array(
                    'class' => array('permalink pull-right'),
                  ),
                )
              ),
            '#children' => $content
          );
          if (empty($content)) {
            $elements['body'] = t('Treaty is tagged with %term', array('%term' => $term->name));
          }
          $ret[$row->nid] = array(
            '#theme' => 'informea_bootstrap_collapse',
            '#elements' => array($row->nid => $elements),
            '#no-data-parent' => 1,
          );
          break;
      }
    }
    return $ret;
  }

  protected static function view_articles($term, $treaty) {
    $ret = array();
    if (!empty($treaty->articles)) {
      foreach ($treaty->articles as $row) {
        $paragraphs = self::view_article_paragraphs($row, $treaty);
        $elements = array(
          'header' => $row->title . l(
              '<i class="glyphicon glyphicon-link"></i>',
              treaty_url_article($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('permalink pull-right'),
                ),
              )
            ),
          '#children' => $paragraphs,
        );
        if (empty($paragraphs)) {
          $elements['body'] = t('Article is tagged with %term', array('%term' => $term->name));
          $elements['in'] = TRUE;
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
      foreach ($article->paragraphs as $row) {
        $w = entity_metadata_wrapper('node', $row);
        $body = $w->body->value();
        if (!empty($body['value'])) {
          $link = treaty_url_paragraph($treaty->nid, $article->nid, $row->nid);
          $content = '';
          if ($p = $w->field_official_order->value()) {
            $content = $p . ' ';
          }
          $content .= strip_tags($body['value']) . ' ' . l('<i class="glyphicon glyphicon-link"></i>', $link, array('html' => TRUE));
          $items[] = $content;
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

  protected static function view_decisions($term, $treaty) {
    $ret = array();
    if (!empty($treaty->decisions)) {
      foreach ($treaty->decisions as $row) {
        $paragraphs = self::view_decision_paragraphs($row, $treaty);
        $elements = array(
          'header' => $row->title . l(
              '<i class="glyphicon glyphicon-link"></i>',
              treaty_url_decision($treaty->nid, $row->nid),
              array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => array('pull-right'),
                ),
              )
            ),
          '#children' => $paragraphs,
        );
        if (empty($paragraphs)) {
          $elements['body'] = t('Decision is tagged with %term', array('%term' => $term->name));
          $elements['in'] = TRUE;
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

  protected static function view_decision_paragraphs($decision, $treaty) {
    $ret = array();
    if (!empty($decision->paragraphs)) {
      foreach ($decision->paragraphs as $row) {
        $w = entity_metadata_wrapper('node', $row);
        $body = $w->body->value();
        if (!empty($body['value'])) {
          $content = '';
          if ($p = $w->field_official_order->value()) {
            $content = $p . ' ';
          }
          $content .= strip_tags($body['value']);
          $items[] = $content;
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
}
