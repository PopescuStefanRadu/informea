<?php
/**
 * @file
 * goal.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function goal_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Goals and principles disclaimer';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'goals_disclaimer';
  $fe_block_boxes->body = '<div class="alert alert-warning">Dear Visitor, we would like to inform you that we are &nbsp;currently working on this section of the site (Goals and Principles). As such the content featured here may vary from the official text but we are working to address these issues. Thank you for your understanding.</div><p>&nbsp;</p>';

  $export['goals_disclaimer'] = $fe_block_boxes;

  return $export;
}
