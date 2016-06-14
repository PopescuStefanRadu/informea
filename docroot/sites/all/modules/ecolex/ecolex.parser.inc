<?php
class EcolexParser {
  private $url = NULL;
  private $curl_timeout = 10;
  private $page_url = NULL;

  private $html = NULL;
  private $parsed = FALSE;
  private $doc = NULL;
  public $sid = NULL;

  public static $ECOLEX_ORG = 'http://ecolex.org';
  public static $WWW_ECOLEX_ORG = 'http://www.ecolex.org';

  /**
   * @param string $url - URL from Ecolex to parse
   * @param string $page_url - URL to modify links to point to (links from paginator and sorter)
   */
  public function __construct($url = '', $page_url = '') {
    $this->url = $url;
    $this->page_url = $page_url;
  }

  protected function get_remote_html() {
    //echo "Retrieving the HTML content from {$this->url}\n";
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $this->url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $this->curl_timeout);
    curl_setopt($ch, CURLOPT_HTTPHEADER, Array("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.15) Gecko/20080623 Firefox/2.0.0.15 InforMEA"));
    curl_setopt($ch, CURLOPT_NOBODY, 0);
    $this->html = curl_exec($ch);
    curl_close($ch);

    //@todo: check for errors or empty results before going further.
    // ""

    // Remove <meta name="keywords" as contains non UTF-8 characters
    $this->html = preg_replace('/\<meta name="keywords" content=".*">/', '', $this->html);

    // Replace & with &amp; (only when not followed by n (&nbsp;) or a (&amp;)
    $this->html = preg_replace('/&(![n,a])/', '&amp;', $this->html);

    // Remove the "clear" div
    $this->html = preg_replace('/<div class="clear"><\/div>/', '', $this->html);
    return $this->html;
  }

  protected function parse_html() {
    if (!$this->parsed) {
      $this->parsed = TRUE;
      $this->get_remote_html();
      $d = new DOMDocument();
      $d->strictErrorChecking = FALSE;
      $d->recover = TRUE;
      //echo "    * Parsing the HTML content\n";
      libxml_use_internal_errors(TRUE);
      if (!empty($this->html)) {
        $d->loadHTML($this->html);
        libxml_use_internal_errors(FALSE);
        $this->doc = $d;
        // Extract the session id
        $m = array();
        preg_match('/;DIDPFDSIjsessionid=.*\?/', $this->html, $m);
        if (!empty($m)) {
          $this->sid = $m[0];
        }
      }
    }
  }

  protected function get_content_div() {
    $ret = NULL;
    $this->parse_html();
    if (!empty($this->doc)) {
      $cn = $this->doc->getElementById('content');
      if ($cn) {
        $newdoc = new DOMDocument();
        $cloned = $cn->cloneNode(TRUE);
        $this->fix_url_informea($cloned);

        // Clean the heading
        $tables = $cloned->getElementsByTagName('table');
        foreach($tables as $table) {
          $t = $table->attributes->item(0);
          if (!empty($t) && $t->value == 'results-header') {
            $table->parentNode->removeChild($table);
          }
        }
        $newdoc->appendChild($newdoc->importNode($cloned, TRUE));
        //echo "    * Extract the content div\n";
        $ret = $newdoc->saveHTML();
      }
    }
    return $ret;
  }

  protected function fix_url_informea(&$node) {
    // Fix the links from sorter table
    $tables = $node->getElementsByTagName('table');
    $orphans = array();
    if ($tables->length > 0) {
      // Item title link - fix the link to open new tab
      foreach ($node->getElementsByTagName('a') as $a) {
        $a->setAttribute('target', '_blank');
        $attr = $a->getAttribute('href');
        if (strpos($attr, 'http') === FALSE) {
          $a->setAttribute('href', self::$ECOLEX_ORG . $a->getAttribute('href'));
        }
      }
      // Fix the links inside top and botom paginators (First Last etc.)
      $spans = $node->getElementsByTagName('span');
      foreach ($spans as $span) {
        if ($span->getAttribute('class') == 'table-pager') {
          $orphans[] = $span;
          /*
          foreach ($span->getElementsByTagName('a') as $a) {
            $a->setAttribute('href', 'javascript:void(0)');
          }
          */
        }
      }
    }
    $rows = $node->getElementsByTagName('div');
    foreach($rows as $row) {
      $a0 = $row->attributes->item(0);
      if(!empty($a0) && $a0->value == 'footer') {
        $orphans[] = $row;
      }
    }

    $rows = $node->getElementsByTagName('input');
    foreach($rows as $row) {
      $orphans[] = $row;
    }
    foreach($orphans as $row) {
      $row->parentNode->removeChild($row);
    }
  }

  /**
   * Returns the HTML after being processed. May return NULL if parsing fails
   * @return string Content as HTML
   */
  public function get_content() {
    $ret = $this->get_content_div();
    $ret = preg_replace('/\<div id="content"\>/', '<div id="ecolex-content">', $ret);
    return $ret;
  }

  /**
   * Returns the raw HTML as was loaded from Ecolex website
   */
  public function get_raw_html() {
    $this->parse_html();
    return $this->html;
  }
}
