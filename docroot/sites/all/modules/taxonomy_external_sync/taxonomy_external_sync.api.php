<?php


function hook_taxonomy_external_sync_source_plugin() {
  $config = array('url' => 'http://www.domain.com/terms.xml');
  $plugin = new RemoteXmlSource($config);
  return array($plugin);
}