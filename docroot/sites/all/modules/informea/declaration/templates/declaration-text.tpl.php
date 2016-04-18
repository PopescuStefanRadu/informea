<?php
/**
 * @file
 * treaty-text.tpl.php
 */
?>
<?php if (isset($text) && is_array($text)): ?>
  <div class="clearfix">
    <div class="btn-toolbar pull-right">
      <button class="btn btn-default" data-toggle="group" data-target="#declaration-text"><?php print t('Expand all'); ?></button>
    </div><!-- .btn-toolbar .pull-right -->
  </div>
  <div class="panel-group tagged-content" id="declaration-text" role="tablist" aria-multiselectable="true">
    <?php foreach ($text as $section): ?>
      <?php print theme('declaration_section', array('section' => $section, array(), 'base_declaration_url' => url('node/' . $declaration->nid))); ?>
    <?php endforeach; ?>
  </div><!-- .panel-group .tagged-content -->
<?php endif; ?>
