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
  if(isset($variables['node'])) {
    $node = $variables['node'];
    switch ($node->type) {
      case 'country':
        $countries = country_get_countries_select_options();
        $countries1 = $countries;
        array_unshift($countries1, t('View another country'));
        $variables['content_column_class'] = ' class="col-sm-9"';
        $variables['countries'] = $countries;
        $variables['select-switch-countries'] = array(
          '#id' => 'country-selector',
          '#type' => 'select',
          '#options' => $countries1,
          '#attributes' => array('class' => array('form-control')),
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
          '#id' => 'treaty-selector',
          '#type' => 'select',
          '#options' => $treaties1,
          '#attributes' => array('class' => array('form-control')),
        );
        array_unshift($variables['page']['sidebar_first'], menu_secondary_local_tasks());
    }
  }
  if (isset($variables['node']->type)) {
    $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
  }

  if ($variables['is_front']) {
    // Loads the enabled countries.
    $variables['countries'] = countries_get_countries('name', array('enabled' => COUNTRIES_ENABLED));

    // Adds the front page JavaScript file to the page.
    drupal_add_js(drupal_get_path('theme', 'informea_theme') . '/js/front.js');
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
  );
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
  $slides = array();
  $slides[0] = array(
    'image' => 'http://www.informea.org/wp-content/uploads/images/syndication/biological-diversity/guillemot-uria-aalge.jpg',
    'logo' => theme('image', array('path' => 'http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png')),
    'link' => '<a href="http://www.cbd.int/doc/press/2014/pr-2014-10-17-CPW-en.pdf">Recognizing that wildlife is an important renewable natural resource, with ...</a>',
    'date' => '27 Oct, 2014',
  );
  $slides[1] = array(
    'image' => 'http://www.informea.org/wp-content/uploads/images/syndication/biological-diversity/guillemot-uria-aalge.jpg',
    'logo' => theme('image', array('path' => 'http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png')),
    'link' => '<a href="http://www.cbd.int/doc/press/2014/pr-2014-10-17-CPW-en.pdf">Recognizing that wildlife is an important renewable natural resource, with ...</a>',
    'date' => '27 Oct, 2014',
  );
  $slides[2] = array(
    'image' => 'http://www.informea.org/wp-content/uploads/images/syndication/biological-diversity/guillemot-uria-aalge.jpg',
    'logo' => theme('image', array('path' => 'http://www.informea.org/wp-content/uploads/images/treaty/logo_cbd.png')),
    'date' => '27 Oct, 2014',
    'link' => '<a href="http://www.cbd.int/doc/press/2014/pr-2014-10-17-CPW-en.pdf">Recognizing that wildlife is an important renewable natural resource, with ...</a>',
  );

  $slides = array();

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
  $q->range(0, 7);
  $q->groupBy('c.field_treaty_target_id');
  if ($rows = $q->execute()->fetchAll()) {
    foreach($rows as $ob) {
      $w = entity_metadata_wrapper('node', $ob->nid);
      $tw = entity_metadata_wrapper('node', $ob->field_treaty_target_id);
      $logo = $tw->field_logo->value();
      $url = $w->field_url->value();
      if (empty($url)) {
        $url = url('node/' . $ob->nid);
      }
      else {
        $url = $url['url'];
      }
      $start = $w->event_calendar_date->value();
      $start = format_date(strtotime($start['value']), 'short');
      $slide = array(
        'image' => $images[array_rand($images)],
        'logo' => theme('image', array('path' => $logo['uri'])),
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
  // We can be sure that the font icons exist in CDN.
  if (theme_get_setting('bootstrap_cdn')) {
    $output .= _bootstrap_icon('search');
  }
  else {
    $output .= t('Search');
  }
  $output .= '</button>';
  $output .= '</span>';
  $output .= '</div>';
  return $output;
}

function informea_theme_links__locale_block(&$variables) {
  global $user;

  $variables['attributes']['class'][] = 'dropdown-menu';
  $variables['attributes']['class'][] = 'dropdown-menu-right';
  $variables['attributes']['aria-labelledby'] = 'dLanguage';

  $output = '<div class="dropdown">';
  $output .= '<button type="button" id="dLanguage" class="btn btn-default navbar-btn" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><span class="glyphicon glyphicon-globe"></span></button>';
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
    $variables['classes_array'][] = 'table-bordered';
  }
}
