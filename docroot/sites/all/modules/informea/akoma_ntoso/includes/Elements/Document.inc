<?php

namespace Drupal\akoma_ntoso\Elements;

class Document extends Element {

  protected static $acceptedDocumentTypes = [
    'act',
    'bill',
    'judgement',
    'debateReport',
    'debate',
    'amendmentList',
    'officialGazette',
    'documentCollection',
    'amendment',
    'doc',
  ];

  public function __construct($type = 'doc') {
    parent::__construct($type);
    $this->setType($type);
  }

  public function setType($type) {
    if (!in_array($type, self::$acceptedDocumentTypes)) {
      throw new \Exception("Document type not accepted: '{$type}'.");
    }
    $this->type = $type;
  }
}