<?php

require_once 'vendor/autoload.php';

/**
 * Use drush scr filename to run these tests
 */
class TreatiesMigrationTest extends PHPUnit_Framework_TestCase {

  function setUp() {
    $config = array(
      'group_name' => 'elis',
      'source_url_pattern' => 'http://leo.local.ro/sites/all/modules/ecolex/ecolex_migration/tests/data/Treaties.xml',
      'xml_encoding' => 'UTF-8'
    );
    MigrationBase::registerMigration('ElisTreatyMigration', 'test_elis_treaties', $config);

    // Remove all terms from all related taxonomies to test multilingual term creation
    $taxonomies = array(
      'type_of_text',
      'field_of_application',
      'jurisdiction',
      'ecolex_region',
      'thesaurus_ecolex',
      'ecolex_subjects',
    );
    foreach ($taxonomies as $machine_name) {
      $voc = taxonomy_vocabulary_machine_name_load($machine_name);
      $terms = taxonomy_term_load_multiple(array(), array('vid' => $voc->vid));
      foreach ($terms as $tid => $term) {
        taxonomy_term_delete($tid);
      }
    }
  }

  function testMigration() {
    $migration = MigrationBase::getInstance('test_elis_treaties');
    $migration->processRollback();
    $result = $migration->processImport();
    $this->assertEquals(MigrationBase::RESULT_COMPLETED, $result);

    $count = db_select('migrate_map_test_elis_treaties')
      ->fields(NULL, array('destid1'))
      ->isNotNull('destid1')
      ->countQuery()
      ->execute()
      ->fetchField();
    $this->assertEquals(3, $count);

    $nid = db_select('migrate_map_test_elis_treaties', 'a')
      ->fields('a', array('destid1'))
      ->condition('sourceid1', 'TRE-000140')
      ->execute()
      ->fetchField();
    $this->assertNotNull($nid);
    $node = node_load($nid);
    $this->assertNotNull($node);
    /** @var stdClass $w */
    $w = entity_metadata_wrapper('node', $node);
    // idRecid => field_original_id
    $this->assertEquals('TRE-000140', $w->field_original_id->value());

    // dateOfEntry => field_date_of_entry
    $this->assertEquals('1981-10-20', date('Y-m-d', $w->field_date_of_entry->value()));
    // dateOfModification => field_date_of_modification
    $this->assertEquals('2016-03-17', date('Y-m-d', $w->field_date_of_modification->value()));
    // title_english => title
    $this->assertEquals('Convention on the Prohibition of Military', $w->label());
    // titleOfText + titleOfText_languages => title + title_field
    $this->assertEquals('Convention on the Prohibition of Military', $node->title_field['en'][0]['value']);
    $this->assertEquals("Convention sur l'interdiction d'utiliser des techniques de modification de l'environnement à", $node->title_field['fr'][0]['value']);
    $this->assertEquals("Convención sobre la Prohibición de Utilizar Técnicas de Modificación", $node->title_field['es'][0]['value']);

    // titleAbbreviation
    $this->assertEquals('LBS Protocol', $w->field_title_abbreviation->value());
    // @todo: titleAbbreviation_languages


    // typeOfText => field_type_of_text
    $this->assertEquals('Multilateral', $w->field_type_of_text->value()->name);
    $q = taxonomy_get_term_by_name('Multilateral');
    $term = reset($q);
    $this->assertNotNull($term);
    $this->assertEquals('Multilateral', $term->name);
    $this->assertEquals('Multilateral', $term->name_field['en'][0]['value']);
    $this->assertEquals('Multilatéral', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Multilateral', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // jurisdiction => field_jurisdiction
    $this->assertEquals('International', $w->field_jurisdiction->value()->name);
    $term = $w->field_jurisdiction->value();
    $this->assertEquals('International', $term->name);
    $this->assertEquals('International', $term->name_field['en'][0]['value']);
    $this->assertEquals('International', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Internacional', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // fieldOfApplication => field_field_of_application
    $this->assertEquals('Global', $w->field_field_of_application->value()->name);
    $term = $w->field_field_of_application->value();
    $this->assertEquals('Global', $term->name_field['en'][0]['value']);
    $this->assertEquals('Mondial', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Mundial', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // @todo: sortFieldOfApplication =>
    // $this->assertEquals(1, $row->sortFieldOfApplication);

    // region => field_ecolex_region
    $values = $w->field_ecolex_region->value();
    $this->assertEquals(2, count($values));
    $this->assertTrue(in_array($values[0]->name, array('Arctic', 'Asia')));
    $this->assertTrue(in_array($values[1]->name, array('Arctic', 'Asia')));

    // subject + subject_fr + subject_es => field_ecolex_tags
    $tags = $w->field_ecolex_tags->value();
    $this->assertEquals(2, count($tags));
    $term = $tags[0];
    $this->assertEquals('Environment gen.', $term->name_field['en'][0]['value']);
    $this->assertEquals('Environnement gén.', $term->name_field['fr'][0]['value']);
    $this->assertEquals('Medio ambiente gen.', $term->name_field['es'][0]['value']);
    $term = $tags[1];
    $this->assertEquals('term2', $term->name_field['en'][0]['value']);

    // @todo: languageOfDocument
    // @todo: languageOfTranslation

    // placeOfAdoption => field_place_of_adoption
    $this->assertEquals('Geneva', $w->field_place_of_adoption->value());
    // depository => field_depositary (@note: not translated)
    $this->assertEquals('UN United Nations', $w->field_depositary->value());
    // dateOfText => field_sorting_date
    $this->assertEquals('1977-05-18', date('Y-m-d', $w->field_sorting_date->value()));

    // @todo: searchDate
    // entryIntoForceDate =>field_entry_into_force
    $this->assertEquals('1978-10-05', date('Y-m-d', $w->field_entry_into_force->value()));

    // obsolete =>field_obsolete
    $this->assertTrue($w->field_obsolete->value());

    // officialPublication => field_official_publication
    $this->assertEquals('TIAS 9614 UN Doc.A/Res./31/72 UNJBB(1976)125 BGBl. 1983 II 125 UNTS I:17119', $w->field_official_publication->value());

    // availableIn => field_available_in
    $this->assertEquals('B7 p. 977:37; UNE 1108 UNTS 151', $w->field_available_in->value());

    // linkToFullText + linkToFullText_languages => field_url
    $links = $node->field_treaty_text_url;
    $link_values = array(
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/En/TRE-000140.pdf',
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Fr/TRE-000140.pdf',
      'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Sp/TRE-000140.pdf'
    );
    $this->assertEquals(3, count($links));
    $this->assertTrue(in_array($node->field_treaty_text_url['en'][0]['url'], $link_values));
    $this->assertTrue(in_array($node->field_treaty_text_url['fr'][0]['url'], $link_values));
    $this->assertTrue(in_array($node->field_treaty_text_url['es'][0]['url'], $link_values));

    // relatedWebSite => field_related_website
    $this->assertEquals('www.un.org', $node->field_related_website[LANGUAGE_NONE][0]['value']);
    $this->assertEquals('http://treaties.un.org/Pages/ViewDetails.aspx?src=IND&mtdsg_no=XXVI-1&chapter=26&lang=en', $node->field_related_website[LANGUAGE_NONE][1]['value']);

    // keyword + keyword_fr + keyword_es => field_ecolex_keywords
    $keywords = $w->field_ecolex_keywords->value();
    $kw_values = array(
      'dispute settlement',
      'military activities',
      'institution',
      'international relations/cooperation',
    );
    $this->assertEquals(4, count($keywords));
    $this->assertTrue(in_array($keywords[0]->name, $kw_values));
    $this->assertTrue(in_array($keywords[1]->name, $kw_values));
    $this->assertTrue(in_array($keywords[2]->name, $kw_values));
    $this->assertTrue(in_array($keywords[3]->name, $kw_values));

    $term = $keywords[0];
    $this->assertNotNull($term);
    $this->assertEquals('dispute settlement', $term->name);
    $this->assertEquals('dispute settlement', $term->name_field['en'][0]['value']);
    $this->assertEquals('règlement des différends', $term->name_field['fr'][0]['value']);
    $this->assertEquals('solución de controversias', $term->name_field['es'][0]['value']);
    $th = entity_translation_get_handler('taxonomy_term', $term);
    $translations = $th->getTranslations();
    $this->assertEquals('en', $translations->original);
    $this->assertTrue(array_key_exists('en', $translations->data));
    $this->assertTrue(array_key_exists('fr', $translations->data));
    $this->assertTrue(array_key_exists('es', $translations->data));

    // abstract => field_abstract @todo: not sure is multilingual
    $abstract = 'Objective: To control emissions of heavy metals'
      . PHP_EOL . 'Summary of provisions:      Parties agree'
      . PHP_EOL . 'Institutional mechanisms'
      . PHP_EOL . '(Source: IUCN ELC, 08.2005)';
    $this->assertEquals($abstract, $node->field_abstract['en'][0]['value']);

    // @todo: amendsTreaty => field_amends_treaty
    // amendsTreatyText => field_amends_treaty_t
    $this->assertEquals(array('TRE-000544', 'TRE-000543'), $w->field_amends_treaty_t->value());
    // @todo: party
  }

  function tearDown() {
    $migration = MigrationBase::getInstance('test_elis_treaties');
    $migration->processRollback();
    MigrationBase::deregisterMigration('test_elis_treaties');
  }
}


class TreatiesElisMigrateSourceTest extends PHPUnit_Framework_TestCase {

  /** @var CourtDecisionElisMigrateSource */
  protected $source = NULL;

  function setUp() {
    $this->source = new TreatyElisMigrateSource(
      'http://leo.local.ro/sites/all/modules/ecolex/ecolex_migration/tests/data/Treaties.xml',
      'UTF-8'
    );
  }

  function testMigration() {
    $this->assertEquals(4, $this->source->computeCount());
    $this->source->performRewind();
    while ($row = $this->source->getNextRow()) {
      if ($row->id == 'TRE-000140') {
        break;
      }
    }
    // id
    $this->assertEquals('TRE-000140', $row->id);
    // Recid
    $this->assertEquals('TRE-000140', $row->Recid);
    // dateOfEntry
    $this->assertEquals('1981-10-20', $row->dateOfEntry);
    // dateOfModification
    $this->assertEquals('2016-03-17', $row->dateOfModification);

    // title_english
    $this->assertEquals('Convention on the Prohibition of Military', $row->title_english);
    // titleOfText
    $this->assertEquals(array('Convention on the Prohibition of Military', "Convention sur l'interdiction d'utiliser des techniques de modification de l'environnement à", "Convención sobre la Prohibición de Utilizar Técnicas de Modificación"), $row->titleOfText);
    // titleOfText_languages
    $this->assertEquals(array('en', 'fr', 'es'), $row->titleOfText_languages);
    // titleAbbreviation
    $this->assertEquals(array('LBS Protocol'), $row->titleAbbreviation);
    // titleAbbreviation_languages
    $this->assertEquals(array('en'), $row->titleAbbreviation_languages);

    // typeOfText
    $this->assertEquals(array('Multilateral'), $row->typeOfText);
    // typeOfTextFr
    $this->assertEquals(array('Multilatéral'), $row->typeOfText_fr);
    // typeOfTextSp
    $this->assertEquals(array('Multilateral'), $row->typeOfText_es);

    // jurisdiction
    $this->assertEquals(array('International'), $row->jurisdiction);
    $this->assertEquals(array('International'), $row->jurisdiction_fr);
    $this->assertEquals(array('Internacional'), $row->jurisdiction_es);
    // fieldOfApplication
    $this->assertEquals(array('Global'), $row->fieldOfApplication);
    $this->assertEquals(array('Mondial'), $row->fieldOfApplication_fr);
    $this->assertEquals(array('Mundial'), $row->fieldOfApplication_es);
    // sortFieldOfApplication
    $this->assertEquals(1, $row->sortFieldOfApplication);
    // region
    $this->assertEquals(array('Arctic', 'Asia'), $row->region);
    // subject + subject_fr + subject_es
    $this->assertEquals(array('Environment gen.', 'term2'), $row->subject);
    $this->assertEquals(array('Environnement gén.'), $row->subject_fr);
    $this->assertEquals(array('Medio ambiente gen.'), $row->subject_es);

    // languageOfDocument
    $this->assertEquals(array('Arabic', 'Chinese', 'English', 'French', 'Russian', 'Spanish'), $row->languageOfDocument);
    $this->assertEquals(array('Arabe', 'Chinois', 'Anglais', 'Français', 'Russe', 'Espagnol'), $row->languageOfDocument_fr);
    $this->assertEquals(array('Árabe', 'Chino', 'Inglés', 'Francés', 'Ruso', 'Español'), $row->languageOfDocument_es);

    // languageOfTranslation
    $this->assertEquals(array('German'), $row->languageOfTranslation);
    $this->assertEquals(array('Allemand'), $row->languageOfTranslation_fr);
    $this->assertEquals(array('Alemán'), $row->languageOfTranslation_es);

    // placeOfAdoption
    $this->assertEquals('Geneva', $row->placeOfAdoption);

    // depository
    $this->assertEquals(array('UN United Nations', 'NU Nations Unies', 'NU Naciones Unidas'), $row->depository);
    $this->assertEquals(array('en', 'fr', 'es'), $row->depository_languages);

    // dateOfText
    $this->assertEquals('1977-05-18', $row->dateOfText);
    // searchDate
    $this->assertEquals('1977-05-18', $row->searchDate);
    // entryIntoForceDate
    $this->assertEquals('1978-10-05', $row->entryIntoForceDate);
    // obsolete
    $this->assertTrue($row->obsolete);
    // officialPublication
    $this->assertEquals('TIAS 9614 UN Doc.A/Res./31/72 UNJBB(1976)125 BGBl. 1983 II 125 UNTS I:17119', $row->officialPublication);
    // availableIn
    $this->assertEquals('B7 p. 977:37; UNE 1108 UNTS 151', $row->availableIn);

    // linkToFullText
    $this->assertEquals(
      array(
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/En/TRE-000140.pdf',
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Fr/TRE-000140.pdf',
        'http://www.ecolex.org/server2.php/server2neu.php/libcat/docs/TRE/Full/Sp/TRE-000140.pdf'
      ),
      $row->linkToFullText
    );
    $this->assertEquals(array('en', 'fr', 'es'), $row->linkToFullText_languages);
    // relatedWebSite
    $this->assertEquals(
      array(
        'www.un.org',
        'http://treaties.un.org/Pages/ViewDetails.aspx?src=IND&mtdsg_no=XXVI-1&chapter=26&lang=en',
      ),
      $row->relatedWebSite
    );

    // keyword
    // keyword
    $kw_values_en = array(
      'dispute settlement',
      'military activities',
      'institution',
      'international relations/cooperation',
    );
    $this->assertEquals($kw_values_en, $row->keyword);

    // keyword_fr
    $kw_values_fr = array(
      'règlement des différends',
      'activités militaires',
      'institution',
      'relations internationales/coopération',
    );
    $this->assertEquals($kw_values_fr, $row->keyword_fr);

    // keyword_es
    $kw_values_es = array(
      'solución de controversias',
      'actividades militares',
      'institución',
      'relaciones internacionales/cooperación',
    );
    $this->assertEquals($kw_values_es, $row->keyword_es);

    // abstract
    $this->assertEquals(
      'Objective: To control emissions of heavy metals'
      . PHP_EOL . 'Summary of provisions:      Parties agree'
      . PHP_EOL . 'Institutional mechanisms'
      . PHP_EOL . '(Source: IUCN ELC, 08.2005)', $row->abstract[0]);

    // amendsTreaty + amendsTreatyText
    $this->assertEquals(array('TRE-000544', 'TRE-000543'), $row->amendsTreaty);
    $this->assertEquals(array('TRE-000544', 'TRE-000543'), $row->amendsTreatyText);

    // languages
    $this->assertEquals(array('en', 'fr', 'es'), $row->languages);

    // party
    $this->assertEquals(4, count($row->party));
    $p0 = $row->party[0];
    $this->assertTrue($p0->potentialParty);
    $this->assertEquals('1985-10-22', $p0->dateOfAccessionApprobation);
    $this->assertEquals('1986-10-22', $p0->entryIntoForce);
    $this->assertEquals(array('Ethiopia', 'Éthiopie', 'Etiopía'), $p0->country);
    $this->assertEquals(array('en', 'fr', 'es'), $p0->country_languages);
  }
}


if (informea_is_development_environment()) {

  $suite = new PHPUnit_Framework_TestSuite('TreatiesMigrationTest');
  PHPUnit_TextUI_TestRunner::run($suite);

  $suite = new PHPUnit_Framework_TestSuite('TreatiesElisMigrateSourceTest');
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
