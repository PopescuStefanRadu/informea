<?php

namespace Drupal\akoma_ntoso;

use Drupal\akoma_ntoso\Elements\Element;
use Drupal\akoma_ntoso\Elements\Document;

class AkomaNtoso {

  /**
   * @var \SimpleXMLElement
   */
  protected $xml;

  /**
   * @var array
   */
  protected $children = array();

  public function __construct() {
    $this->xml = new \SimpleXMLElement('<xml/>');
    $this->xml->addChild('akomaNtoso');
  }

  public function addChild(Document $element) {
    $this->children[] = $element;
  }

  /**
   * @return \SimpleXMLElement
   */
  public function render() {
    /** @var \SimpleXMLElement $root */
    $root = $this->xml->children()[0];
    foreach ($this->children as $child) {
      /** @var Element $child */
      $child->appendToXML($root);
    }
    return $this->xml;
  }
}