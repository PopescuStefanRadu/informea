<?php

require_once 'vendor/autoload.php';

/**
 * Use drush scr filename to run these tests
 */
class CourtDecisionsMigrationTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'group_name' => 'elis',
      'source_url_pattern' => 'http://leo.local.ro/sites/all/modules/ecolex/ecolex_migration/tests/data/CourtDecisions.xml',
      'xml_encoding' => 'UTF-8'
    );
    MigrationBase::registerMigration('ElisCourtDecisionMigration', 'test_elis_court_decisions', $config);

    // Remove all terms from all related taxonomies to test multilingual term creation
    $taxonomies = array(
      'type_of_text',
      'territorial_subdivision',
      'jurisdiction',
      'ecolex_decision_status',
      // 'field_data_source',
      // field_region
      'ecolex_region',
      'thesaurus_ecolex',
      'ecolex_subjects',
    );
    foreach($taxonomies as $machine_name) {
      $voc = taxonomy_vocabulary_machine_name_load($machine_name);
      $terms = taxonomy_term_load_multiple(array(), array('vid' => $voc->vid));
      foreach($terms as $tid => $term) {
        taxonomy_term_delete($tid);
      }
    }
  }

  function testMigration() {
    $migration = MigrationBase::getInstance('test_elis_court_decisions');
    $migration->processRollback();
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_elis_court_decisions')
      ->fields(NULL, array('destid1'))
      ->isNotNull('destid1')
      ->countQuery()
      ->execute()
      ->fetchField();
    $this->assertEquals(3, $count);

    $nid = db_select('migrate_map_test_elis_court_decisions', 'a')->fields('a', array('destid1'))->condition('sourceid1', 'COU-143756')->execute()->fetchField();
    $this->assertNotNull($nid);
    $node = node_load($nid);
    /** @var stdClass $w */
    $w = entity_metadata_wrapper('node', $node);

    // id => field_original_id
    $this->assertEquals('COU-143756', $w->field_original_id->value());
    // id2 => field_alternative_record_id
    $this->assertEquals('800000+C-997120400+', $w->field_alternative_record_id->value());
    // isisMfn => field_isis_number
    $this->assertEquals('000103', $w->field_isis_number->value());
    // dateOfEntry => field_date_of_entry
    $this->assertEquals('2006-11-29', date('Y-m-d', $w->field_date_of_entry->value()));
    // dateOfModification => field_date_of_modification
    $this->assertEquals('2016-03-11', date('Y-m-d', $w->field_date_of_modification->value()));

    // title_english => title
    $this->assertEquals('The M/V Saiga case', $w->label());
    // titleOfText + titleOfText_languages => title + title_field
    $this->assertEquals('The M/V Saiga case', $node->title_field['en'][0]['value']);
    $this->assertEquals('French The M/V Saiga case', $node->title_field['fr'][0]['value']);

    // titleOfTextShort + titleOfTextShort_languages => field_title_of_text_short
    $this->assertEquals('Montreal Protocol', $w->field_title_of_text_short->value());
    $this->assertEquals('Montreal Protocol', $node->field_title_of_text_short['en'][0]['value']);
    $this->assertEquals('Montreal Protocol French', $node->field_title_of_text_short['fr'][0]['value']);

    // titleOfTextOther => field_title_of_text_other
    $this->assertEquals('Bundesminister für soziale Sicherheit', $w->field_title_of_text_other->value());
    // titleOfTextShortOther => field_title_of_text_short_other
    $this->assertEquals('Dr Eva Glawischnig v. Bündeskanzler', $w->field_title_of_text_short_other->value());

    // country => field_country
    $countries = $w->field_country->value();
    $this->assertEquals(2, count($countries));
    $this->assertTrue(in_array($countries[0]->nid, array(190514, 190424)));
    $this->assertTrue(in_array($countries[1]->nid, array(190514, 190424)));

    // subject + subject_fr + subject_es => field_ecolex_tags
    $tags = $w->field_ecolex_tags->value();
    $this->assertEquals(4, count($tags));
    $this->assertTrue(in_array($tags[0]->name, array('Fisheries', 'Sea', 'Subject1_EN', 'Legal questions')));
    $this->assertTrue(in_array($tags[1]->name, array('Fisheries', 'Sea', 'Subject1_EN', 'Questions juridiques')));
    $this->assertTrue(in_array($tags[2]->name, array('Fisheries', 'Sea', 'Subject1_EN', 'Cuestiones jurídicas')));

    $q = taxonomy_get_term_by_name('Subject1_EN');
    $term = reset($q);
    $this->assertNotNull($term);
    $this->assertEquals('Subject1_EN', $term->name);
    $this->assertEquals('Subject1_EN', $term->name_field['en'][0]['value']);
    $this->assertEquals('Subject1_FR', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Subject1_ES', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // languageOfDocument => field_source_language
    $this->assertEquals('English', $w->field_source_language->value()['value']);
    // courtName => field_court_name
    $this->assertEquals('International Tribunal for the Law of the Sea', $w->field_court_name->value());
    // dateOfText => field_sorting_date
    $this->assertEquals('1997-12-04', date('Y-m-d', $w->field_sorting_date->value()));
    // referenceNumber => field_reference_number
    $this->assertEquals('List of cases No. 1', $w->field_reference_number->value());
    // numberOfPages => field_number_of_pages
    $this->assertEquals(19, $w->field_number_of_pages->value());
    // availableIn => field_available_in
    $this->assertEquals('B7 p. 985:22/A', $w->field_available_in->value());
    // linkToFullText + linkToFullText_languages => field_url
    $links = $node->field_url;
    $link_values = array(
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/En/TRE-000953.pdf',
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Fr/TRE-000953.pdf',
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Sp/TRE-000953.pdf',
    );
    $this->assertEquals(3, count($links));
    $this->assertTrue(in_array($node->field_url['en'][0]['url'], $link_values));
    $this->assertTrue(in_array($node->field_url['fr'][0]['url'], $link_values));
    $this->assertTrue(in_array($node->field_url['es'][0]['url'], $link_values));

    $nid2 = db_select('migrate_map_test_elis_court_decisions', 'a')->fields('a', array('destid1'))->condition('sourceid1', 'COU-143757')->execute()->fetchField();
    $this->assertNotNull($nid2);
    $node2 = node_load($nid2);
    $this->assertEquals($node2->field_url['es'][0]['url'], 'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Sp/TRE-000953.pdf');

    // linkToFullTextOther => field_url_other
    $this->assertEquals('http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Other/TRE-000953.pdf', $w->field_url_other->value()['url']);
    // internetReference + internetReference_languages => field_internet_reference_url
    $this->assertEquals('http://www.itlos.org/cgi-bin/cases/case_detail.pl?id=1&lang=en', $node->field_internet_reference_url['en'][0]['url']);
    $this->assertEquals('http://www.unece.org/env/lrtap/full%20text/1988.NOX.f.pdf', $node->field_internet_reference_url['fr'][0]['url']);
    // relatedWebSite => field_related_url
    $this->assertEquals('http://www.itlos.org/cgi-bin/cases/case_detail.pl?id=1&lang=en', $node->field_related_url['en'][0]['url']);
    // keyword + keyword_fr + keyword_es => field_ecolex_keywords
    $keywords = $w->field_ecolex_keywords->value();
    $kw_values = array(
      'Authorization/permit',
      'fishing area',
      'fishing vessel',
      'international agreement-text',
      'marine area',
      'marine fisheries',
      'maritime zone',
      'offences/penalties',
      'Keyword1_EN',
    );
    $this->assertEquals(9, count($keywords));
    $this->assertTrue(in_array($keywords[0]->name, $kw_values));
    $this->assertTrue(in_array($keywords[1]->name, $kw_values));
    $this->assertTrue(in_array($keywords[2]->name, $kw_values));
    $this->assertTrue(in_array($keywords[3]->name, $kw_values));
    $this->assertTrue(in_array($keywords[4]->name, $kw_values));
    $this->assertTrue(in_array($keywords[5]->name, $kw_values));
    $this->assertTrue(in_array($keywords[6]->name, $kw_values));
    $this->assertTrue(in_array($keywords[7]->name, $kw_values));
    $this->assertTrue(in_array($keywords[8]->name, $kw_values));

    $q = taxonomy_get_term_by_name('Keyword1_EN');
    $term = reset($q);
    $this->assertNotNull($term);
    $this->assertEquals('Keyword1_EN', $term->name);
    $this->assertEquals('Keyword1_EN', $term->name_field['en'][0]['value']);
    $this->assertEquals('Keyword1_FR', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Keyword1_ES', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // abstract + abstract_languages => field_abstract
    $this->assertEquals('ABCD' . PHP_EOL . 'EFG', $node->field_abstract['en'][0]['value']);
    $this->assertEquals('La Supreme impugnación?' . PHP_EOL . 'El último', $node->field_abstract['fr'][0]['value']);
    $this->assertEquals('Cámara' . PHP_EOL . 'confirmó', $node->field_abstract['es'][0]['value']);

    // typeOfText => field_type_of_text
    $this->assertEquals('International court', $w->field_type_of_text->value()->name);
    $term = $w->field_type_of_text->value();
    $this->assertEquals('International court', $term->name_field['en'][0]['value']);
    $this->assertEquals('International court FR', $term->name_field['fr'][0]['value']);
    $this->assertEquals('International court ES', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // referenceToNationalLegislation => field_reference_to_legislation_t
    $values = $w->field_reference_to_legislation_t->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('LEG-12345', $values));
    $this->assertTrue(in_array('LEG-45678', $values));

    // referenceToTreaties => field_ecolex_treaty_raw
    $values = $w->field_ecolex_treaty_raw->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('TRE-000753', $values));
    $this->assertTrue(in_array('TRE-000754', $values));

    // referenceToCourtDecision => field_court_decision_raw
    $values = $w->field_court_decision_raw->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('COU-143770', $values));
    $this->assertTrue(in_array('COU-143771', $values));

    // subdivision => field_court_decision_subdivision
    $value = $w->field_court_decision_subdivision->value();
    $this->assertEquals('Chamber of Consults', $value);

    // justices => field_justices
    $values = $w->field_justices->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('Rao Chandrasekhara', $values));
    $this->assertTrue(in_array('Nelson', $values));

    // territorialSubdivision => field_territorial_subdivision
    $values = $w->field_territorial_subdivision->value();
    $this->assertEquals(1, count($values));
    $term = $values[0];
    $this->assertTrue(in_array($term->name, array('District of Columbia')));
    $this->assertEquals('District of Columbia', $term->name_field['en'][0]['value']);
    $this->assertEquals('District au Columbia', $term->name_field['fr'][0]['value']);
    $this->assertEquals('District de Columbia', $term->name_field['es'][0]['value']);

    // linkToAbstract => field_link_to_abstract
    $this->assertEquals('http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/COU/Abstracts/COU-AB-EN-143758.rtf', $w->field_link_to_abstract->value()['url']);

    // statusOfDecision => field_ecolex_decision_status (not multilingual)
    $this->assertEquals('Unknown', $w->field_ecolex_decision_status->value()->name);

    // referenceToEULegislation => field_legislation_eu_reference
    $values = $w->field_legislation_eu_reference->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('LEG-142630', $values));
    $this->assertTrue(in_array('LEG-142631', $values));

    // seatOfCourt => field_city
    $this->assertEquals('Hamburg', $w->field_city->value());
    // courtJurisdiction => field_jurisdiction
    $this->assertEquals('Civil', $w->field_jurisdiction->value()->name);
    // instance => field_instance
    $this->assertEquals('Grand Chamber', $w->field_instance->value());
    // officialPublication => field_official_publication
    $this->assertEquals('In the High Court of New Zealand Auckland Registry', $w->field_official_publication->value());

    // region => field_ecolex_region
    $values = $w->field_ecolex_region->value();
    $this->assertEquals(1, count($values));
    $this->assertTrue(in_array($values[0]->name, array('Australia and New Zealand')));

    // referenceToFaolex => field_faolex_reference_raw
    $values = $w->field_faolex_reference_raw->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array('LEX-FAOC003172', $values));
    $this->assertTrue(in_array('LEX-FAOC003173', $values));

    // languages => entity translation configuration (Check node translations)
    $th = entity_translation_get_handler('node', $node);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // field_data_source
    $this->assertEquals('ECOLEX/ELIS', $w->field_data_source->value()[0]->name);

    // languageOfTranslation ??? @todo: I dont understand this field
  }


  function tearDown() {
    $migration = MigrationBase::getInstance('test_elis_court_decisions');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_elis_court_decisions');
  }
}


class CourtDecisionElisMigrateSourceTest extends PHPUnit_Framework_TestCase {

  /** @var CourtDecisionElisMigrateSource */
  protected $source = NULL;

  function setUp() {
    $this->source = new CourtDecisionElisMigrateSource(
      'http://leo.local.ro/sites/all/modules/ecolex/ecolex_migration/tests/data/CourtDecisions.xml',
      'UTF-8'
    );
  }

  function testMigration() {
    $this->assertEquals(4, $this->source->computeCount());
    $this->source->performRewind();
    while ($row = $this->source->getNextRow()) {
      if ($row->id == 'COU-143756') {
        break;
      }
    }
    // id
    $this->assertEquals('COU-143756', $row->id);
    // id2
    $this->assertEquals('800000+C-997120400+', $row->id2);
    // isisMfn
    $this->assertEquals('000103', $row->isisMfn);
    // dateOfEntry
    $this->assertEquals('2006-11-29', $row->dateOfEntry);
    // dateOfModification
    $this->assertEquals('2016-03-11', $row->dateOfModification);
    // title_english
    $this->assertEquals('The M/V Saiga case', $row->title_english);
    // titleOfText
    $this->assertEquals(array('The M/V Saiga case', 'French The M/V Saiga case'), $row->titleOfText);
    // titleOfText_languages
    $this->assertEquals(array('en', 'fr'), $row->titleOfText_languages);
    // titleOfTextShort
    $this->assertEquals(array('Montreal Protocol', 'Montreal Protocol French'), $row->titleOfTextShort);
    $this->assertEquals(array('en', 'fr'), $row->titleOfTextShort_languages);
    // titleOfTextOther
    $this->assertEquals('Bundesminister für soziale Sicherheit', $row->titleOfTextOther);
    // titleOfTextShortOther
    $this->assertEquals('Dr Eva Glawischnig v. Bündeskanzler', $row->titleOfTextShortOther);
    // country
    $this->assertEquals(array('Guinea', 'Saint Vincent and the Grenadines'), $row->country);

    // subject
    $this->assertEquals(array('Fisheries', 'Sea', 'Subject1_EN', 'Legal questions'), $row->subject);
    $this->assertEquals(array('Pêche', 'Mer', 'Subject1_FR', 'Questions juridiques'), $row->subject_fr);
    $this->assertEquals(array('Pesca', 'Mar', 'Subject1_ES', 'Cuestiones jurídicas'), $row->subject_es);

    // languageOfDocument
    $this->assertEquals('English', $row->languageOfDocument);
    // courtName
    $this->assertEquals('International Tribunal for the Law of the Sea', $row->courtName);
    // dateOfText
    $this->assertEquals('1997-12-04', $row->dateOfText);
    // referenceNumber
    $this->assertEquals('List of cases No. 1', $row->referenceNumber);
    // numberOfPages
    $this->assertEquals('19', $row->numberOfPages);
    // availableIn
    $this->assertEquals('B7 p. 985:22/A', $row->availableIn);
    // linkToFullText
    $this->assertEquals(array(
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/En/TRE-000953.pdf',
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Fr/TRE-000953.pdf',
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Sp/TRE-000953.pdf',
      ),
      $row->linkToFullText
    );
    // linkToFullText_languages
    $this->assertEquals(array('en', 'fr', 'es'), $row->linkToFullText_languages);
    // linkToFullTextOther
    $this->assertEquals('http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Other/TRE-000953.pdf', $row->linkToFullTextOther);
    // relatedWebSite
    $this->assertEquals('http://www.itlos.org/cgi-bin/cases/case_detail.pl?id=1&lang=en', $row->relatedWebSite);

    // internetReference
    $this->assertEquals(array(
      'http://www.itlos.org/cgi-bin/cases/case_detail.pl?id=1&lang=en',
      'http://www.unece.org/env/lrtap/full%20text/1988.NOX.f.pdf',
      'http://judis.nic.in/chennai/qrydisp.asp?tfnm=7675'
    ),
      $row->internetReference
    );
    $this->assertEquals(array('en', 'fr', 'es'), $row->internetReference_languages);

    // keyword
    $kw_values_en = array(
      'Authorization/permit',
      'fishing area',
      'fishing vessel',
      'international agreement-text',
      'marine area',
      'marine fisheries',
      'maritime zone',
      'offences/penalties',
      'Keyword1_EN',
    );
    $this->assertEquals($kw_values_en, $row->keyword);

    // keyword_fr
    $kw_values_fr = array(
      'autorisation/permis',
      'zone de pêche',
      'navire de pêche',
      'accord international-texte',
      'aire marine',
      'pêche maritime',
      'zone marine',
      'infractions/sanctions',
      'Keyword1_FR',
    );
    $this->assertEquals($kw_values_fr, $row->keyword_fr);

    // keyword_es
    $kw_values_es = array(
      'autorización/permiso',
      'zona de pesca',
      'embarcación de pesca',
      'acuerdo internacional-texto',
      'área marina',
      'pesca marítima',
      'zona marítima',
      'infracciones/sanciones',
      'Keyword1_ES',
    );
    $this->assertEquals($kw_values_es, $row->keyword_es);

    // abstract
    $this->assertEquals('ABCD' . PHP_EOL . 'EFG', $row->abstract[0]);
    // abstractFr
    $this->assertEquals('La Supreme impugnación?' . PHP_EOL . 'El último', $row->abstract[1]);
    // abstractSp
    $this->assertEquals('Cámara' . PHP_EOL . 'confirmó', $row->abstract[2]);
    $this->assertEquals(array('en', 'fr', 'es'), $row->abstract_languages);

    // typeOfText
    $this->assertEquals(array('International court'), $row->typeOfText);
    // typeOfTextFr
    $this->assertEquals(array('International court FR'), $row->typeOfText_fr);
    // typeOfTextSp
    $this->assertEquals(array('International court ES'), $row->typeOfText_es);

    // referenceToNationalLegislation
    $this->assertEquals(array('LEG-12345', 'LEG-45678'), $row->referenceToNationalLegislation);
    // referenceToTreaties
    $this->assertEquals(array('TRE-000753', 'TRE-000754'), $row->referenceToTreaties);


    // justices
    $this->assertEquals(array('Rao Chandrasekhara', 'Nelson'), $row->justices);
    // territorialSubdivision
    $this->assertEquals(array('District of Columbia'), $row->territorialSubdivision);
    $this->assertEquals(array('District au Columbia'), $row->territorialSubdivision_fr);
    $this->assertEquals(array('District de Columbia'), $row->territorialSubdivision_es);

    // linkToAbstract
    $this->assertEquals('http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/COU/Abstracts/COU-AB-EN-143758.rtf', $row->linkToAbstract);
    // statusOfDecision
    $this->assertEquals('Unknown', $row->statusOfDecision);
    // referenceToEULegislation
    $this->assertEquals(array('LEG-142630', 'LEG-142631'), $row->referenceToEULegislation);
    // seatOfCourt
    $this->assertEquals('Hamburg', $row->seatOfCourt);
    // courtJurisdiction
    $this->assertEquals('Civil', $row->courtJurisdiction);
    // instance
    $this->assertEquals('Grand Chamber', $row->instance);
    // officialPublication?
    $this->assertEquals('In the High Court of New Zealand Auckland Registry', $row->officialPublication);
    // region
    $this->assertEquals(array('Australia and New Zealand'), $row->region);
    $this->assertEquals(array('Australie et Nouvelle-Zélande'), $row->region_fr);
    $this->assertEquals(array('Australia y Nueva Zelandia'), $row->region_es);

    // referenceToFaolex?
    $this->assertEquals(array('LEX-FAOC003172', 'LEX-FAOC003173'), $row->referenceToFaolex);

    // languages
    $this->assertEquals(array('en', 'fr', 'es'), $row->languages);

    // referenceToCourtDecision
    $this->assertEquals(array('COU-143770', 'COU-143771'), $row->referenceToCourtDecision);
    // subdivision
    $this->assertEquals('Chamber of Consults', $row->subdivision);
  }
}

if (informea_is_development_environment()) {

  $suite = new PHPUnit_Framework_TestSuite('CourtDecisionsMigrationTest');
  PHPUnit_TextUI_TestRunner::run($suite);

  $suite = new PHPUnit_Framework_TestSuite('CourtDecisionElisMigrateSourceTest');
  PHPUnit_TextUI_TestRunner::run($suite);
}
else {
  $msg = "\nThis is not a development environment. These tests are distructive so I refuse to run them. Use 'drush vset environment devel' to set.\n";
  if (function_exists('drush_set_error')) {
    drush_set_error($msg);
  }
  else {
    echo $msg . "\n";
    exit(-1);
  }
}