<?php

namespace Drupal\akoma_ntoso\Elements;

class Element {

  protected $type;
  protected $attributes = array();
  protected $children = array();
  protected $content = NULL;
  protected $cdata = FALSE;

  public function __construct($type, $content = NULL, $cdata = FALSE) {
    $this->setType($type);
    $this->setContent($content);
    $this->cdata = $cdata;
  }

  public function setType($type) {
    $this->type = $type;
  }

  public function getType() {
    return $this->type;
  }

  public function addAttribute($name, $value) {
    $this->attributes[$name] = $value;
  }

  public function setContent($value) {
    $this->content = $value;
  }

  public function addChild(Element $element) {
    $this->children[] = $element;
  }

  public function appendToXML(\SimpleXMLElement &$parent) {
    if ($this->cdata) {
      $parent->{$this->type} = NULL;
      $parent->{$this->type}->addCData($this->content);
      foreach ($this->attributes as $name => $value) {
        $parent->{$this->type}->addAttribute($name, $value);
      }
    }
    else {
      $current = $parent->addChild($this->type, $this->content);
      foreach ($this->attributes as $name => $value) {
        $current->addAttribute($name, $value);
      }
    }
    foreach ($this->children as $child) {
      /** @var Element $child */
     $child->appendToXML($current);
    }
  }

}