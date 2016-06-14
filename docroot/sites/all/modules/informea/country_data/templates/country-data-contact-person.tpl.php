<?php
/**
 * @file
 * country-data-contact-person.tpl.php
 */
?>
<?php
  $wrapper = entity_metadata_wrapper('node', $contact_person);
  $position = $wrapper->field_person_position->value();
  $department = $wrapper->field_person_department->value();
  $institution = $wrapper->field_person_institution->value();
  $address = $wrapper->field_address->value();
  $fax = $wrapper->field_contact_fax->value();
  $telephone = $wrapper->field_contact_telephone->value();
  $mail = $wrapper->field_person_email->value();
  $mail_link = FALSE;
  if ($mail) {
    $mail_url  = recaptcha_mailhide_url(variable_get('recaptcha_public'), variable_get('recaptcha_private'), $mail);
    $mail_part = implode('&hellip;@', _recaptcha_mailhide_email_parts( $wrapper->field_person_email->value()));
    $mail_link = l($mail_part, $mail_url, array(
      'attributes' => array(
        'onclick' => sprintf('window.open(\'%s\', \'\', \'toolbar=0,scrollbars=0,location=0,statusbar=0,menubar=0,resizable=0,width=500,height=300\'); return false;', $mail_url)
      ), 'external' => TRUE, 'html' => TRUE
    ));
  }
  $type_label = '';
  if ($type = $wrapper->field_person_type->value()) {
    $type_term = entity_metadata_wrapper('taxonomy_term', reset($type)->tid);
    $type_label = $type_term->label();
  }
?>
<h4 class="list-group-item-heading">
  <span class="glyphicon glyphicon-user"></span> <?php print $wrapper->label(); ?>
</h4>
<dl class="dl-horizontal">
<?php if (!empty($contact_person->roles)): ?>
  <dt><?php print format_plural(count($contact_person->roles), 'Role', 'Roles'); ?></dt>
  <dd><?php print implode(', ', $contact_person->roles); ?></dd>
<?php endif; ?>
<?php if ($position): ?>
  <dt><?php print t('Position'); ?></dt>
  <dd><?php print $position; ?></dd>
<?php endif; ?>

<?php if ($department): ?>
  <dt><?php print t('Department'); ?></dt>
  <dd><?php print $department; ?></dd>
<?php endif; ?>

<?php if ($institution): ?>
  <dt><?php print t('Institution'); ?></dt>
  <dd><?php print $institution; ?></dd>
<?php endif; ?>

<?php if ($address): ?>
  <dt><?php print t('Address'); ?></dt>
  <dd><?php print $address; ?></dd>
<?php endif; ?>

<?php if ($mail_link): ?>
  <dt><?php print t('E-Mail'); ?></dt>
  <dd><?php print $mail_link; ?></dd>
<?php endif; ?>

<?php if ($telephone): ?>
  <dt><?php print t('Telephone'); ?></dt>
  <dd><?php print $telephone; ?></dd>
<?php endif; ?>

<?php if ($fax): ?>
  <dt><?php print t('Fax'); ?></dt>
  <dd><?php print $fax; ?></dd>
<?php endif; ?>

<?php if ($type_label): ?>
  <dt><?php print t('Type'); ?></dt>
  <dd><?php print $type_label; ?></dd>
<?php endif; ?>
</dl>
