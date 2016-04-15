<?php
$pw = entity_metadata_wrapper('node', $indicator->nid);
$tags = $pw->field_informea_tags->value();
$highlight = isset($_GET['indicator']) ? $_GET['indicator'] == $indicator->nid : FALSE;
?>
<div class="indicator smallipop <?php print $highlight ? 'highlight' : '' ;?>" id="indicator-<?php print $indicator->nid; ?>">
  <p>
    <?php if($pw->body->value()): ?>
      <?php print($pw->body->value->value(array('decode' => FALSE))); ?>
    <?php endif; ?>
  </p>
  <?php print theme('goal_text_tags', array('tags' => $tags)); ?>
  <ul class="list-inline actions">
    <?php if (!empty($tags) && is_array($tags)): ?>
      <li>
        <span class="glyphicon glyphicon-tag"></span>
      </li>
    <?php endif; ?>
    <li class="action-hover">
      <?php
      print l('<i class="glyphicon glyphicon-link"></i>', $base_goal_url, array(
        'attributes' => array(
          'data-toggle' => 'tooltip', 'data-placement' => 'top',
          'title' => t('Permalink'),
          'class' => array('pull-right permalink'),
          'target' => '_blank'
        ),
        'fragment' => 'indicator-' . $indicator->nid,
        'html' => TRUE,
        'query' => array('goal' => $goal->nid, 'target' => $target->nid, 'indicator' => $indicator->nid)
      ));
      ?>
    </li>
    <?php if (user_access('edit any goal content')): ?>
      <li class="action-hover">
        <?php
        print l('<i class="glyphicon glyphicon-pencil"></i>', 'node/' . $indicator->nid . '/edit', array(
          'attributes' => array('data-toggle' => 'tooltip', 'data-placement' => 'top', 'title' => t('Edit indicator')),
          'html' => TRUE
        ));
        ?>
      </li>
    <?php endif; ?>
  </ul><!-- .list-inline .actions -->
</div><!-- .indicator .smallipop -->
