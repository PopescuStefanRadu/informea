jQuery(document).ready(function ($) {
  // Disable all clicks
  $('.disabled').click(function (event) { event.preventDefault() });

  $('#dialog-modal-ajax').on('loaded.bs.modal', function () {
    $(window).trigger('resize');
  });

  $('#dialog-modal-ajax').on('hidden.bs.modal', function () {
    $(this).removeData('bs.modal');
  });

  $('.permalink').click(function (event) {
    event.stopPropagation();
  });

  $('[data-toggle="select"]').click(function (event) {
    var $element = $(this);
    var target = $element.attr('href');

    event.preventDefault();

    $('option', target).prop('selected', true);
  });

  $.widget('custom.catcomplete', $.ui.autocomplete, {
    _create: function() {
      this._super();
      this.widget().menu('option', 'items', '> :not(.ui-autocomplete-category)');
    },
    _renderMenu: function(ul, items) {
      var that = this,
        currentCategory = '';
      $.each(items, function(index, item) {
        var li;

        if (item.category != currentCategory) {
          ul.append('<li class="ui-autocomplete-category">' + item.category + '</li>');
          currentCategory = item.category;
        }

        li = that._renderItemData(ul, item);

        if (item.category) {
          li.attr('aria-label', item.category + ' : ' + item.label);
        }
      });
    },
    // https://github.com/scottgonzalez/jquery-ui-extensions/blob/master/src/autocomplete/jquery.ui.autocomplete.html.js
    _renderItem: function(ul, item) {
      return $('<li></li>')
        .append($('<a></a>').html(item.label))
        .appendTo(ul);
    }
  });

  $('#edit-keys').catcomplete({
    delay: 0,
    source: function (request, response) {
      var url = Drupal.settings.basePath + 'ajax/search/' + encodeURIComponent(request.term);

      $.get(url, function (data) {
        response(data);
      });

    },
    select: function (event, ui) {
      if (ui.item.link) {
        window.location.href = ui.item.link;
      }
    }
  });

  $('.node-switcher').on('change', function() {
    var val = $(this).val();

    if (val !== 0) {
      window.location.href = val;
    }
  });

  $('[data-toggle="informea-bootstrap-collapse"]').click(function () {
    var $element = $(this);
    var target = $element.data('target');

    if ($element.data('pressed')) {
      $element.data('pressed', false);
      $element.html(Drupal.t('Show all'));
      $('.panel-collapse', target).collapse('hide');
    } else {
      $element.data('pressed', true);
      $element.html(Drupal.t('Hide all'));
      $('.panel-collapse', target).collapse('show');
    }
  });

  $('[data-filter="list"]').keyup(function () {
    var selector = $(this).data('selector');
    var target = $(this).data('target');
    var value = $(this).val();

    $('.panel', target).hide().filter(function () {
      return $('table > tbody > tr', this).hide().filter(function () {
        return $(selector, this).text().toLowerCase().indexOf(value.toLowerCase()) > -1;
      }).show().length > 0;
    }).show();
  });

  $('.back-to-top').on('click', function (event) {
    event.preventDefault();

    $('html, body').animate({
      scrollTop: 0
    }, 600);
  });

  var timer;

  $(window).on('scroll', function () {
    if (!timer) {
      timer = setTimeout(function () {
        if ($(window).scrollTop() > 100) {
          $('.back-to-top').fadeIn();
        } else {
          $('.back-to-top').fadeOut();
        }

        timer = null;
      }, 300);
    }
  });
});
