<?php
/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
            <?php if ($field == 'field_region'): ?>
              <a id="dRegion" data-target="#" href="#" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
                <?php print 'Geo. scope'; ?>
                <span class="caret"></span>
              </a><!-- #dRegion -->
              <ul class="dropdown-menu dropdown-menu-right" aria-labeledby="dRegion">
                <li class="active"><?php print l(t('All regions'), NULL, array('attributes' => array('data-filter' => 'table', 'data-selector' => '.views-field-field-region', 'data-value' => NULL), 'fragment' => 'table-treaties', 'external' => TRUE)); ?></li>
                <?php foreach ($view->regions as $region): ?>
                  <li><?php print l($region->name, NULL, array('attributes' => array('data-filter' => 'table', 'data-selector' => '.views-field-field-region', 'data-value' => $region->name), 'fragment' => 'table-treaties', 'external' => TRUE)); ?></li>
                <?php endforeach; ?>
              </ul><!-- .dropdown-menu .dropdown-menu-right -->
            <?php else: ?>
              <?php print $label; ?>
            <?php endif; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"'; } ?> <?php if (isset($view->result[$row_count]->parent_treaty)) { print 'data-parent-treaty="' . $view->result[$row_count]->parent_treaty . '"'; } ?>>
        <?php foreach ($row as $field => $content): ?>
          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php print $content; ?>
            <?php if ($field == 'field_title_abbreviation' && $view->result[$row_count]->total_protocols): ?>
              <p>
                <button type="button" class="btn btn-primary btn-xs" data-toggle="protocols" data-nid="<?php print $view->result[$row_count]->nid; ?>">
                  <span class="glyphicon glyphicon-plus-sign"></span>
                  <?php print t('View protocols'); ?>
                </button><!-- .btn .btn-primary .btn-xs -->
              </p>
            <?php endif; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
