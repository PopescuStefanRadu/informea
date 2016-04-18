jQuery(document).ready(function ($) {
  $('.smallipop').smallipop({
    invertAnimation: true,
    preferredPosition: 'left',
    theme: 'white'
  });

  $('[data-toggle="group"]').click(function () {
    var $element = $(this);
    var target = $element.data('target');

    if ($element.data('pressed')) {
      $element.data('pressed', false);
      $element.html('Expand all');
      $('.panel-collapse', target).collapse('hide');
    } else {
      $element.data('pressed', true);
      $element.html('Close all');
      $('.panel-collapse', target).collapse('show');
    }
  });

  var target;

  if (target = window.location.hash) {
    var $el = $(target);

    if ($el.length) {
      $.scrollTo(0).scrollTo(target, 'slow', {
        offset: -150
      });
    }
  }

});
