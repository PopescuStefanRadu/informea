<?php
/**
 * @file
 * template.php
 */

/**
 * Preprocesses variables for page template.
 *
 * @param $variables
 *   An associative array with generated variables.
 *
 * @return
 *   Nothing.
 */
function informea_theme_preprocess_page(&$variables) {
  $breadcrumbs = array();
  // Add the autocomplete library.
  drupal_add_library('system', 'ui.autocomplete');
  menu_secondary_local_tasks();
  if (arg(0) == 'taxonomy') {
    // Unset related terms in taxonomy page
    unset($variables['page']['content']['system_main']['nodes']);
    unset($variables['page']['content']['system_main']['pager']);
    unset($variables['page']['content']['system_main']['no_content']);
    $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');
    /** @var stdClass $term */
    if ($term = taxonomy_term_load(arg(2))) {
      if ($term->vid == $voc->vid) {
        $variables['theme_hook_suggestions'][] = 'page__taxonomy__thesaurus_informea';
        $variables['content_column_class'] = ' class="col-sm-9"';
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
      }
    }
  }
  $path = request_path();
  switch ($path) {
    case 'countries':
      $breadcrumbs[] = t('Countries');
      break;
    case 'terms':
      $breadcrumbs[] = t('Glossary');
      break;
    case 'events':
      $breadcrumbs[] = t('Events');
      break;
    case 'events/past':
      $breadcrumbs[] = t('Past events');
      break;
    case 'news':
      $breadcrumbs[] = t('News');
      break;
    case 'about':
      $breadcrumbs[] = t('About InforMEA');
      break;
    case 'about/api':
      $breadcrumbs[] = t('API documentation');
      break;
  }
  if(isset($variables['node'])) {
    $node = $variables['node'];
    switch ($node->type) {
      case 'event_calendar':
        $breadcrumbs[] = l(t('Events'), 'events');
        $breadcrumbs[] = $node->title;
        break;

      case 'country':
        $countries = country_get_countries_select_options();
        $countries1 = $countries;
        array_unshift($countries1, t('View another country'));
        $variables['content_column_class'] = ' class="col-sm-9"';
        $variables['countries'] = $countries;
        $variables['select-switch-countries'] = array(
          '#attributes' => array('class' => array('form-control', 'node-switcher', 'country-switcher')),
          '#options' => $countries1,
          '#type' => 'select'
        );
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
        break;

      case 'treaty':
        $variables['content_column_class'] = ' class="col-sm-9"';
        $treaties = treaty_get_treaties_as_select_options();
        $variables['treaties'] = $treaties;
        $treaties1 = $treaties;
        array_unshift($treaties1, t('View another treaty'));
        $variables['select-switch-treaties'] = array(
          '#attributes' => array('class' => array('form-control', 'node-switcher', 'treaty-switcher')),
          '#options' => $treaties1,
          '#type' => 'select'
        );
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
        break;

      case 'decision':
        if (!empty($node->field_decision_number[LANGUAGE_NONE][0]['value'])) {
          $variables['classes_array'][] = 'decision-page';
          $variables['title_prefix'] = $node->field_decision_number[LANGUAGE_NONE][0]['value'];
          $variables['page']['above_content'] = array(
            '#type' => 'container',
            '#attributes' => array(
              'id' => array('decision-date-title'),
            ),
            '#attached' => array(
              'js' => array(
                drupal_get_path('theme', 'informea_theme') . '/js/decision.js',
              ),
            ),
          );
          if (!empty($node->field_sorting_date[LANGUAGE_NONE][0]['value'])) {
            $decision_date = date('d-m-Y', strtotime($node->field_sorting_date[LANGUAGE_NONE][0]['value']));
            $variables['page']['above_content']['date'] = array(
              '#type' => 'item',
              '#title' => t('Date'),
              '#markup' => $decision_date,
              '#prefix' => '<div class="field-name-field-sorting-date"><div class="container">',
              '#suffix' => '</div></div>',
            );
          }
          $variables['page']['above_content']['title'] = array(
            '#type' => 'item',
            '#title' => t('Full title'),
            '#markup' => $node->title,
            '#prefix' => '<div class="field-name-title-field"><div class="container">',
            '#suffix' => '</div></div>',
          );
          if (!empty($node->field_treaty[LANGUAGE_NONE][0]['target_id'])) {
            $treaty_node = node_load($node->field_treaty[LANGUAGE_NONE][0]['target_id']);
            $variables['page']['above_content']['tabs'] = _decision_get_treaty_links($treaty_node, array('un-treaty-collection-link'));
            $variables['page']['above_content']['tabs']['#prefix'] = '<div class="decision-treaty-tabs"><div class="container">';
            $variables['page']['above_content']['tabs']['#suffix'] = '</div></div>';
          }
        }
        break;

      case 'goal':
        $sdgs_tid = 1753;
        if (!empty($node->field_goal_source)
          && !empty($node->field_goal_source[LANGUAGE_NONE])
          && $node->field_goal_source[LANGUAGE_NONE][0]['tid'] == $sdgs_tid) {
          $node_w = entity_metadata_wrapper('node', $node);
          if (($term = $node_w->field_goal_type->value()) && in_array($term->name, ['Target', 'Indicator'])) {
            $tw = entity_metadata_wrapper('taxonomy_term', $term);
            drupal_set_title($tw->label() . ' ' . $node_w->label());
          }
        }
        break;
    }
  }
  if (isset($variables['node']->type)) {
    $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
  }

  if ($variables['is_front']) {
    // Adds the front page JavaScript file to the page.
    drupal_add_js(drupal_get_path('theme', 'informea_theme') . '/js/front.js');

    // Country block from the front page
    // Replace the <select> at this stage to avoid replacement issue coming from i18n_block_translate_block
    if (!empty($variables['page']['front_page_content']['block_10'])) {
      $block_data =& $variables['page']['front_page_content']['block_10'];
      $countries = country_get_countries_select_options();
      array_unshift($countries, t('Select a country…'));
      $html = array(
        '#attributes' => array('class' => array('form-control', 'node-switcher', 'country-switcher')),
        '#options' => $countries,
        '#type' => 'select'
      );
      $block_data['#markup'] = preg_replace('/<select.*><\/select>/i', drupal_render($html), $block_data['#markup']);
    }
  }

  if (!empty($breadcrumbs)) {
    informea_theme_set_page_breadcrumb($breadcrumbs);
  }
}

function informea_theme_theme() {
  return array(
    'informea_bootstrap_collapse' => array(
      'render element' => 'element',
      'template' => 'templates/informea-bootstrap-collapse',
      'variables' => array('elements' => array(), 'id' => 0, 'no-data-parent' => FALSE, 'no-panel-body' => FALSE),
    ),
    'informea_bootstrap_tabs' => array(
      'render element' => 'element',
      'template' => 'templates/informea-bootstrap-tabs',
      'variables' => array('id' => 0, 'elements' => array(), 'active' => FALSE, 'header-attributes' => array()),
      'path' => drupal_get_path('theme', 'informea_theme'),
    ),
    'informea_bootstrap_carousel' => array(
      'render element' => 'element',
      'template' => 'templates/informea-bootstrap-carousel',
      'variables' => array('slides' => array(), 'attributes' => array()),
      'path' => drupal_get_path('theme', 'informea_theme'),
    ),
    'informea_search_form_wrapper' => array(
      'render element' => 'element',
    ),
    'bootstrap_btn_dropdown' => array(
      'variables' => array(
        'links' => array(),
        'attributes' => array(),
        'type' => NULL,
      ),
    ),
  );
}

/**
 * Implements theme_bootstrap_btn_dropdown().
 */
function informea_theme_bootstrap_btn_dropdown($variables) {
  $path = drupal_get_path('theme', 'bootstrap');
  require_once $path . '/theme/bootstrap/bootstrap-btn-dropdown.func.php';
  return theme_bootstrap_btn_dropdown($variables);
}


function informea_theme_meeting_type($term) {
  if ($term) {
    switch ($term->name_original) {
      case 'cop':
        return 'COP';
      default:
        return ucfirst($term->name);
    }
  }
  return '';
}

function informea_theme_treaty_logo($node, $style = 'logo-large') {
  $w = entity_metadata_wrapper('node', $node->nid);
  if ($logo = $w->field_logo->value()) {
    return theme('image_style', array('style_name' => $style, 'path' => $logo['uri']));
  }
  return NULL;
}

function informea_theme_country_flag($node, $style = 'logo-large') {
  $w = entity_metadata_wrapper('node', $node->nid);
  if($code = $w->field_country_iso2->value()) {
    $code = strtolower($code);
    global $base_url;
    $img_path = $base_url . '/' . drupal_get_path('theme', 'informea_theme') . '/img/flags/flag-' . $code . '.png';

    return theme('image', array('path' => $img_path, 'attributes' => array('class' => array('flag', 'flag-large'))));
  }
  return NULL;
}

function informea_theme_treaty_logo_link($node) {
  if ($img = informea_theme_treaty_logo($node)) {
    $w = entity_metadata_wrapper('node', $node->nid);
    if ($url = $w->field_treaty_website_url->value()) {
      return l($img, $url['url'], array('absolute' => TRUE, 'html' => TRUE, 'attributes' => array('target' => '_blank', 'class' => array('treaty-logo-large'))));
    }
    else {
      return $img;
    }
  }
  return NULL;
};

function informea_theme_slider() {
  $max_slides_count = variable_get('informea_max_slides_count', 7);
  $slides = array();
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'entityqueue_subqueue')
    ->entityCondition('bundle', 'front_page_slider');
  $result = $query->execute();
  if (!empty($result['entityqueue_subqueue'])) {
    drupal_add_js('https://www.youtube.com/iframe_api');
    $subqueues = entity_load('entityqueue_subqueue', array_keys($result['entityqueue_subqueue']));
    foreach ($subqueues as $subqueue) {
      $wrapper = entity_metadata_wrapper('entityqueue_subqueue', $subqueue);
      $key = $wrapper->getIdentifier();
      $nodes = $wrapper->eq_node->value();
      foreach ($nodes as $node) {
        $w = entity_metadata_wrapper('node', $node);
        switch ($w->getBundle()) {
          case 'feed_item':
            $url = $w->field_url->value();
            $url = empty($url) ? 'node/' . $w->getIdentifier() : $url['url'];

            break;

          default:
            $url = 'node/' . $w->getIdentifier();

            break;
        }
        $image = NULL;
        try {
          $video = field_view_field('node', $node, 'field_video', 'full');
          $image = drupal_render($video);
        }
        catch(Exception $e) {}
        if (empty($image)) {
          $alt = !empty($w->field_image->value()['alt']) ? $w->field_image->value()['alt'] : $w->label();
          $image = theme('image_style', array(
            'path' => $w->field_image->value()['uri'],
            'style_name' => 'front_page_slider',
            'alt' => $alt,
          ));
        }
        $slide = array(
          'image' => l($image, $url, array('absolute' => TRUE, 'html' => TRUE)),
          'link' => l($w->label(), $url, array('absolute' => TRUE, 'attributes' => array('target' => '_blank')))
        );

        $slides[] = $slide;
      }
    }
  }

  $length = $max_slides_count - count($slides);

  if ($length <= 0) {
    return theme(
      'informea_bootstrap_carousel',
      array(
        'slides' => $slides,
        'attributes' => array(
          'id' => 'col-carousel',
        )
      )
    );
  }

  $images = array(
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/Biological-Diversity.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/african-bush-elephants.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/botanical.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/coral-reef.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/ferns.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/green-crowned.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/guillemot-uria-aalge.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/lingonberries-vaccinium-vitus.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/mu-ko-lanta-marine.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/palmoil-plantage.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/parrothfish-scaridae.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/rottumerplaat-dutch-wadden-sea.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/slide-coral-reef.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'biological-diversity/thompsons-gazelles.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'chemicals-waste/Chemicals-and-Waste-Management.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'chemicals-waste/icebergs.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'chemicals-waste/nickel-smelters.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'climate-change/Climate-Atmosphere-and-Deserts.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'climate-change/icebergs.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'drylands/drylands.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'financing-trade/green-economy.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'financing-trade/international.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'international-cooperation/international.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/african-bush-elephants.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/ferns.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/parrothfish-scaridae.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/rottumerplaat-dutch-wadden-sea.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/slide-bird.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/slide-jaguar.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'species/species.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'wetlands-national-heritage-sites/mangroves.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'wetlands-national-heritage-sites/pechora-delta.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'wetlands-national-heritage-sites/swamp.jpg',
    '/sites/all/themes/informea.theme/img/syndication/' . 'wetlands-national-heritage-sites/wetlands.jpg',
  );
  // Select one upcoming event from each MEA
  /*
   SELECT a.* FROM node a
      INNER JOIN field_data_event_calendar_date b ON a.nid = b.entity_id
      INNER JOIN field_data_field_treaty c ON a.nid = c.entity_id
        WHERE b.event_calendar_date_value >= NOW()
      GROUP BY c.field_treaty_target_id
   */
  $q = db_select('node', 'a')->fields('a', array('nid'))->fields('c', array('field_treaty_target_id'));
  $q->innerJoin('field_data_event_calendar_date', 'b', 'a.nid = b.entity_id');
  $q->innerJoin('field_data_field_treaty', 'c', 'a.nid = c.entity_id');
  $q->where('b.event_calendar_date_value >= NOW()');
  $q->range(0, $length);
  $q->groupBy('c.field_treaty_target_id');
  if ($rows = $q->execute()->fetchAll()) {
    foreach($rows as $ob) {
      $w = entity_metadata_wrapper('node', $ob->nid);
      $tw = entity_metadata_wrapper('node', $ob->field_treaty_target_id);
      $logo = $tw->field_logo->value();
      $url = $w->field_url->value();
      $url = empty($url) ? $url = url('node/' . $ob->nid) : $url = $url['url'];
      $start = $w->event_calendar_date->value();
      $start = format_date(strtotime($start['value']), 'short');
      $image = theme('image', array('path' => $images[array_rand($images)], 'alt' => $w->label()));
      $slide = array(
        'image' => l($image, $url, array('absolute' => TRUE, 'html' => TRUE)),
        'logo' => theme('image', array('path' => $logo['uri'], 'alt' => $tw->label())),
        'date' => $start,
        'link' => l($w->label(), $url, array('absolute' => TRUE, 'attributes' => array('target' => '_blank'))),
      );

      $slides[] = $slide;
    }
  }

  return theme(
    'informea_bootstrap_carousel',
    array(
      'slides' => $slides,
      'attributes' => array(
        'id' => 'col-carousel',
      )
    )
  );
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function informea_theme_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'views_exposed_form') {
    if (isset($form['submit'])) {
      $form['submit']['#attributes']['class'][] = 'btn-primary';
      $form['submit']['#value'] = t('Filter');
    }

    if (isset($form['reset'])) {
      $form['reset']['#attributes']['class'][] = 'btn-link';
    }

    // Events
    if ($form['#id'] == 'views-exposed-form-events-page') {
      $form['#prefix'] = '<h3 class="lead">' . t('Meeting finder') . '</h3>';
      $form['field_treaty_target_id']['#suffix'] = '<p class="help-block text-right">' . l(t('Select all'), NULL, array('attributes' => array('data-toggle' => 'select'), 'external' => TRUE, 'fragment' => 'edit-field-treaty-target-id')) . '</p>';
      $form['field_event_type_tid']['#suffix'] = '<p class="help-block text-right">' . l(t('Select all'), NULL, array('attributes' => array('data-toggle' => 'select'), 'external' => TRUE, 'fragment' => 'edit-field-event-type-tid')) . '</p>';
    }

    // News
    if (isset($form['search_api_views_fulltext'])) {
      $form['search_api_views_fulltext']['#attributes']['placeholder'] = t('Type some text here…');
    }

    if (isset($form['field_mea_topic'])) {
      $form['field_mea_topic']['#options']['All'] = t('-- All topics --');
    }
  }
}


/**
 * Theme function implementation for bootstrap_search_form_wrapper.
 */
function informea_theme_informea_search_form_wrapper($variables) {
  $output = '<div class="input-group">';
  $output .= $variables['element']['#children'];
  $output .= '<span class="input-group-btn">';
  $output .= '<button type="submit" class="btn btn-default">';
  $output .= _bootstrap_icon('search');
  $output .= '</button>';
  $output .= '</span>';
  $output .= '</div>';
  return $output;
}

function informea_theme_links__locale_block(&$variables) {
  global $user, $language;

  $variables['attributes']['class'][] = 'dropdown-menu';
  $variables['attributes']['class'][] = 'dropdown-menu-right';
  $variables['attributes']['aria-labelledby'] = 'dLanguage';

  $output = '<div class="dropdown">';
  $output .= '<button type="button" id="dLanguage" class="btn btn-default navbar-btn" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">';
  $output .= strtoupper($language->language);
  $output .= '</button>';
  $output .= theme_links($variables);
  $output .= '</div>';

  return $output;
}

/**
 * Preprocesses variables for block template.
 *
 * @param $variables
 *   An associative array with generated variables.
 *
 * @return
 *   Nothing.
 */
function informea_theme_preprocess_block(&$variables) {
  if ($variables['block']->module == 'treaty' && $variables['block']->delta == 'treaty_global') {
    $variables['title_attributes_array']['class'][] = 'lead';
    $variables['title_attributes_array']['class'][] = 'text-center';
  }
}

function informea_theme_preprocess_views_view_table(&$variables) {
  if ($variables['view']->name == 'treaty_listing_page') {
    $variables['attributes_array']['id'] = 'table-treaties';
    $variables['classes_array'][] = 'table-bordered';

    foreach ($variables['view']->result as $key => $result) {
      if (isset($result->parent_treaty)) {
        $variables['row_classes'][$key][] = 'active';
      }
    }
  }
}

function informea_theme_views_pre_render(&$view) {
  if ($view->name == 'treaty_listing_page' && $view->current_display == 'page') {
    foreach($view->result as &$row) {
      $wrapper = entity_metadata_wrapper('node', $row->_field_data['nid']['entity']);

      if ($parent_treaty = $wrapper->field_parent_treaty->value()) {
        $row->parent_treaty = $parent_treaty->nid;
      }

      $row->total_protocols = treaty_count_child_protocols($row->nid);
    }
  }
}

function informea_theme_set_page_breadcrumb($breadcrumbs = array()) {
  array_unshift($breadcrumbs, l(t('Home'), '<front>'));
  drupal_set_breadcrumb($breadcrumbs);
}

function informea_theme_preprocess_node(&$vars) {
  if ($view_mode = $vars['view_mode']) {
    $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $view_mode;
    $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->nid . '__' . $view_mode;
  }
}

/**
 * Draw the flexible layout.
 */
function informea_theme_panels_flexible($vars) {
  $css_id = $vars['css_id'];
  $content = $vars['content'];
  $settings = $vars['settings'];
  $display = $vars['display'];
  $layout = $vars['layout'];
  $handler = $vars['renderer'];

  panels_flexible_convert_settings($settings, $layout);

  $renderer = panels_flexible_create_renderer(FALSE, $css_id, $content, $settings, $display, $layout, $handler);

  $output = "<div class=\"panel-flexible " . $renderer->base['canvas'] . " clearfix\" $renderer->id_str>\n";
  $output .= "<div class=\"panel-flexible-inside " . $renderer->base['canvas'] . "-inside\">\n";

  $output .= panels_flexible_render_items($renderer, $settings['items']['canvas']['children'], $renderer->base['canvas']);

  // Wrap the whole thing up nice and snug
  $output .= "</div>\n</div>\n";

  return $output;
}

function informea_theme_views_mini_pager($vars) {
  global $pager_page_array, $pager_total;

  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $pager_current = $pager_page_array[$element] + 1;
  $pager_max = $pager_total[$element];

  if ($pager_total[$element] > 1) {
    $li_previous = theme('pager_previous', array(
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
      'text' => (isset($tags[1]) ? $tags[1] : t('‹‹'))
    ));

    $li_next = theme('pager_next', array(
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
      'text' => (isset($tags[3]) ? $tags[3] : t('››'))
    ));

    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous
    );

    $items[] = array(
      'class' => array('pager-current'),
      'data' => t('@current of @max', array('@current' => $pager_current, '@max' => $pager_max))
    );

    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next
    );

    return theme('item_list', array(
      'attributes' => array('class' => array('pager')),
      'items' => $items,
      'title' => NULL,
      'type' => 'ul'
    ));
  }
}
