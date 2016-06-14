<?php
/**
 * @file
 * treaty-text.tpl.php
 */
?>
<?php
/** @var array $variables */
$node = $variables['node'];
$node_wrapper = entity_metadata_wrapper('node', $node);
$odata_identifier = $node_wrapper->field_odata_identifier->value();
$print = sprintf('/treaties/%s/print', $odata_identifier);
$akoma = sprintf('/treaties/%s/export', $odata_identifier);
?>
<?php if (isset($articles) && is_array($articles)): ?>
  <?php if (!empty($articles)): ?>
    <p class="text-right">
      <button class="btn btn-default" data-toggle="group" data-target="#treaty-text">
        <?php print t('Expand all'); ?>
      </button>
      <a class="btn btn-primary" href="<?php print url($print); ?>" target="_blank">
        <i class="glyphicon glyphicon-print"></i>
        <?php print t('Print treaty text'); ?>
      </a>
      <a class="btn btn-default" href="<?php print url($akoma); ?>" target="_blank" onclick="return confirm('This feature is EXPERIMENTAL for reviewing purposes!');">
        <img class="akoma-logo" style="width: 16px; height: 16px;" src="/sites/all/themes/informea.theme/img/akoma-logo.png">
        <?php print t('Akoma Ntoso XML'); ?>
      </a>
    </p>
  <?php endif; ?>
  <div class="panel-group tagged-content" id="treaty-text" role="tablist" aria-multiselectable="true">
    <?php foreach ($articles as $article) : ?>
      <?php print theme('treaty_text_article', array('article' => $article)); ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>
<?php
if (user_access('create treaty_article content')):

  $query = array(
    'destination' => sprintf('node/%s/text', $node->nid)
  );
  if (isset($node->nid)) {
    $query['edit'] = array(
      'field_treaty' => array('und' => $node->nid)
    );
  }
  print l('<i class="glyphicon glyphicon-plus"></i> ' . t('Add article'), 'node/add/treaty-article', array(
    'attributes' => array('class' => array('btn', 'btn-default')),
    'html' => TRUE,
    'query' => $query,
  ));
endif;
?>

