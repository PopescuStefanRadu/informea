<?php
/**
 * @file
 * informea.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function informea_locale_default_languages() {
  $languages = array();

  // Exported language: ar.
  $languages['ar'] = array(
    'language' => 'ar',
    'name' => 'Arabic',
    'native' => 'العربية',
    'direction' => 1,
    'enabled' => 1,
    'plurals' => 6,
    'formula' => '(($n==1)?(0):(($n==0)?(1):(($n==2)?(2):(((($n%100)>=3)&&(($n%100)<=10))?(3):(((($n%100)>=11)&&(($n%100)<=99))?(4):5)))))',
    'domain' => '',
    'prefix' => 'ar',
    'weight' => -6,
  );
  // Exported language: en.
  $languages['en'] = array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => -10,
  );
  // Exported language: es.
  $languages['es'] = array(
    'language' => 'es',
    'name' => 'Spanish',
    'native' => 'Español',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n!=1)',
    'domain' => '',
    'prefix' => 'es',
    'weight' => -7,
  );
  // Exported language: fr.
  $languages['fr'] = array(
    'language' => 'fr',
    'name' => 'French',
    'native' => 'Français',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n>1)',
    'domain' => '',
    'prefix' => 'fr',
    'weight' => -9,
  );
  // Exported language: ru.
  $languages['ru'] = array(
    'language' => 'ru',
    'name' => 'Russian',
    'native' => 'Русский',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 3,
    'formula' => '(((($n%10)==1)&&(($n%100)!=11))?(0):((((($n%10)>=2)&&(($n%10)<=4))&&((($n%100)<10)||(($n%100)>=20)))?(1):2))',
    'domain' => '',
    'prefix' => 'ru',
    'weight' => -8,
  );
  // Exported language: zh-hans.
  $languages['zh-hans'] = array(
    'language' => 'zh-hans',
    'name' => 'Chinese, Simplified',
    'native' => '简体中文',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n!=1)',
    'domain' => '',
    'prefix' => 'zh-hans',
    'weight' => -5,
  );
  return $languages;
}
