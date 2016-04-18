<?php
/**
 * @file
 * treaty-text.tpl.php
 */
$pw = entity_metadata_wrapper('node', $paragraph);
$tags = $pw->field_informea_tags->value();
$highlight = isset($_GET['paragraph']) ? $_GET['paragraph'] == $paragraph->nid : FALSE;
?>
<div class="paragraph smallipop <?php print $highlight ? 'highlight' : '' ;?>" id="paragraph-<?php print $paragraph->nid; ?>">
  <div class="text">
      <?php print $pw->field_official_order->value(); ?>
      <?php
        $body = $pw->body->value->value();
        $body = str_replace('<p>', '', $body);
        $body = str_replace('</p>', '', $body);
      ?>
      <?php print $body; ?>
  </div>
  <?php print theme('declaration_text_tags', array('tags' => $tags)); ?>
  <ul class="list-inline actions">
    <?php if (!empty($tags) && is_array($tags)): ?>
      <li>
        <span class="glyphicon glyphicon-tag"></span>
      </li>
    <?php endif; ?>
    <li class="action-hover">
      <?php
      print l('<i class="glyphicon glyphicon-link"></i>', $base_declaration_url, array(
        'attributes' => array(
          'data-toggle' => 'tooltip', 'data-placement' => 'top',
          'title' => t('Permalink'),
          'class' => array('pull-right permalink'),
          'target' => '_blank'
        ),
        'fragment' => 'paragraph-' . $paragraph->nid,
        'html' => TRUE,
        'query' => array('parents' => $parents_nids, 'paragraph' => $paragraph->nid)
      ));
      ?>
    </li>
    <?php if (user_access('edit any declaration content')): ?>
      <li>
        <?php print l('<span class="glyphicon glyphicon-pencil"></span> ' . t('Edit paragraph'), 'node/' . $paragraph->nid . '/edit', array('html' => TRUE)); ?>
      </li>
    <?php endif; ?>
  </ul><!-- .list-inline .actions -->
</div><!-- .paragraph .smallipop -->
