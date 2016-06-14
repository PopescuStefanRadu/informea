<?php
$pw = entity_metadata_wrapper('node', $target->nid);
$tags = $pw->field_informea_tags->value();
$expanded = isset($_GET['target']) ? $_GET['target'] == $target->nid : FALSE;
?>
<div class="panel <?php print $expanded ? 'panel-warning' : 'panel-default'; ?>">
  <div class="panel-heading smallipop <?php print $expanded ? '' : ' collapsed' ;?>" role="tab" id="heading-<?php echo $target->nid; ?>" data-toggle="collapse" data-target="#target-<?php echo $target->nid; ?>" aria-expanded="<?php print $expanded ? 'true' : 'false' ;?>" aria-controls="goal-<?php echo $target->nid; ?>">
    <ul class="list-inline actions">
      <li class="action-hover">
        <?php
        print l('<i class="glyphicon glyphicon-eye-open"></i>', "node/{$target->nid}", array(
          'attributes' => array(
            'data-toggle' => 'tooltip', 'data-placement' => 'top',
            'title' => t('View target page'),
          ),
          'html' => TRUE,
        ));
        ?>
      </li>
      <li class="action-hover">
        <?php
        print l('<i class="glyphicon glyphicon-link"></i>', $base_goal_url, array(
          'attributes' => array(
            'data-toggle' => 'tooltip', 'data-placement' => 'top',
            'title' => t('Permalink'),
            'class' => array('permalink'),
            'target' => '_blank'
          ),
          'fragment' => 'target-' . $target->nid,
          'html' => TRUE,
          'query' => array('goal' => $goal->nid, 'target' => $target->nid)
        ));
        ?>
      </li>
      <?php if (user_access('edit any goal content')): ?>
        <li class="action-hover">
          <?php
          print l('<i class="glyphicon glyphicon-pencil"></i>', 'node/' . $target->nid . '/edit', array(
            'attributes' => array('data-toggle' => 'tooltip', 'data-placement' => 'top', 'title' => t('Edit target')),
            'html' => TRUE
          ));
          ?>
        </li>
      <?php endif; ?>
      <?php if (!empty($tags) && is_array($tags)): ?>
        <li>
          <span class="glyphicon glyphicon-tag" data-toggle="tooltip" data-placement="top" title="<?php print t('Tagged terms'); ?>"></span>
        </li>
      <?php endif; ?>
    </ul><!-- .list-inline .actions -->
    <i class="glyphicon glyphicon-plus-sign"></i>
    <h4 class="panel-title panel-title-target">
      <p class="title"><?php print $pw->label(); ?></p>
      <?php if($pw->body->value()): ?>
        <?php print($pw->body->value->value(array('decode' => FALSE))); ?>
      <?php endif; ?>
    </h4><!-- .panel-title -->
    <?php print theme('goal_text_tags', array('tags' => $tags)); ?>
  </div><!-- .panel-heading .smallipop -->
  <div id="target-<?php echo $target->nid; ?>" class="panel-collapse collapse<?php print $expanded ? ' in' : '' ;?>" role="tabpanel" aria-labelledby="heading-<?php echo $target->nid; ?>">
    <div class="target">
      <?php if (!empty($target->indicators)): ?>
        <h4><?php print t('Indicators:'); ?></h4>
        <?php foreach ($target->indicators as $indicator): ?>
          <?php print theme('goal_target_indicator', array('goal' => $goal, 'target' => $target, 'indicator' => $indicator, 'base_goal_url' => $base_goal_url)); ?>
        <?php endforeach; ?>
      <?php endif; ?>
    </div><!-- .goal -->
  </div><!-- .panel-collapse .collapse -->
</div><!-- .panel .panel-default -->
