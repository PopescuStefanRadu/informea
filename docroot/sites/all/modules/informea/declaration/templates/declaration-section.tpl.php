<?php
$aw = entity_metadata_wrapper('node', $section);
$tags = $aw->field_informea_tags->value();
$expanded = isset($_GET['section']) ? $_GET['section'] == $section->nid : FALSE;
$parents = array();
if (isset($_GET['parents'])) {
  $parents = $_GET['parents'];
  if ($expanded == FALSE) {
    $expanded = in_array($section->nid, $parents) ? TRUE : FALSE;
  }
}
?>
<div class="panel <?php print $expanded ? 'panel-warning' : 'panel-default'; ?>">
  <div class="panel-heading smallipop <?php print $expanded ? '' : ' collapsed' ;?>" role="tab" id="heading-<?php echo $section->nid; ?>" data-toggle="collapse" data-target="#section-<?php echo $section->nid; ?>" aria-expanded="<?php print $expanded ? 'true' : 'false' ;?>" aria-controls="section-<?php echo $section->nid; ?>">
    <ul class="list-inline actions">
      <li class="action-hover">
        <?php
        print l('<i class="glyphicon glyphicon-link"></i>', $base_declaration_url, array(
          'attributes' => array(
            'data-toggle' => 'tooltip', 'data-placement' => 'top',
            'title' => t('Permalink'),
            'class' => array('pull-right permalink'),
            'target' => '_blank'
          ),
          'fragment' => 'heading-' . $section->nid,
          'html' => TRUE,
          'query' => array('parents' => $parents_nids, 'section' => $section->nid)
        ));
        ?>
      </li>
    </ul><!-- .list-inline .actions -->
    <h4 class="panel-title">
      <?php print $section->title; ?>
    </h4><!-- .panel-title -->
    <?php print theme('declaration_text_tags', array('tags' => $tags)); ?>
  </div><!-- .panel-heading -->
  <div id="section-<?php echo $section->nid; ?>" class="panel-collapse collapse<?php print $expanded ? ' in' : '' ;?>" role="tabpanel" aria-labelledby="heading-<?php echo $section->nid; ?>">
    <div class="section">
      <?php if (property_exists($section, 'children')): ?>
        <?php $parents_nids[] = $section->nid; ?>
        <?php foreach ($section->children as $child): ?>
          <?php if ($child->type == 'declaration_section'): ?>
            <?php print theme('declaration_section', array('section' => $child, 'parents_nids' => $parents_nids, 'base_declaration_url' => $base_declaration_url)); ?>
          <?php else: ?>
            <?php print theme('declaration_paragraph', array('paragraph' => $child, 'parents_nids' => $parents_nids, 'base_declaration_url' => $base_declaration_url)); ?>
          <?php endif; ?>
        <?php endforeach; ?>
      <?php endif; ?>
    </div><!-- .section -->
  </div><!-- .panel-collapse .collapse -->
</div>
