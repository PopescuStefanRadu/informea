<?php if (isset($goals) && is_array($goals)): ?>
  <div class="clearfix">
    <div class="btn-toolbar pull-right">
      <button class="btn btn-default" data-toggle="group" data-target="#goal-text"><?php print t('Expand all'); ?></button>
    </div><!-- .btn-toolbar .pull-right -->
  </div>
  <h2><?php print t('Goals, targets and indicators:'); ?></h2>
  <div class="panel-group tagged-content" id="goal-text" role="tablist" aria-multiselectable="true">
    <?php foreach ($goals as $goal) : ?>
      <?php print theme('goal_text', array('goal' => $goal, 'base_goal_url' => url('taxonomy/term/' . $term->tid))); ?>
    <?php endforeach; ?>
  </div><!-- .panel-group .tagged-content -->
<?php endif; ?>

