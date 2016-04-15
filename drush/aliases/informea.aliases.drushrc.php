<?php
$aliases['prod'] = array(
  'uri' => 'http://www.informea.org',
);

$aliases['staging'] = array(
  'uri' => 'http://informea-staging.edw.ro',
  'root' => '/var/www/html/informea-staging.edw.ro/docroot',
  'remote-host' => 'php-devel1.edw.ro',
  'remote-user' => 'php',
);


// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
