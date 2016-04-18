jQuery(document).ready(function ($) {
  $('[data-toggle="tree"]').click(function () {
    var $element = $(this);
    var target = $element.data('target');

    if ($element.data('pressed')) {
      $element.data('pressed', false);
      $element.html(Drupal.t('Show all'));
      $('.list-tree', target).collapse('hide');
    } else {
      $element.data('pressed', true);
      $element.html(Drupal.t('Hide all'));
      $('.list-tree', target).collapse('show');
    }
  });

  $('[data-toggle="tree-item"]').click(function () {
    $(this).siblings('.list-tree').collapse('toggle');
  });

  $('.list-tree').on('show.bs.collapse', function (event) {
    event.stopPropagation();

    $(this).siblings('.toggle').find('.glyphicon').removeClass('glyphicon-plus-sign').addClass('glyphicon-minus-sign');
  });

  $('.list-tree').on('hide.bs.collapse', function (event) {
    event.stopPropagation();

    $(this).siblings('.toggle').find('.glyphicon').removeClass('glyphicon-minus-sign').addClass('glyphicon-plus-sign');
  });
});
