jQuery(document).ready(function ($) {
    if ($('#decision-body-field').length == 0) {
        $('#skip-to-body').hide();
    }
    else {
        $('#skip-to-body').show();
    }
    function decision_toggle_title(){
        var $h1 = $('h1');
        var $title = $('#decision-date-title .field-name-title-field');
        if ($h1.length > 0 && $title.length > 0) {
            if ($h1.outerWidth() < $h1[0].scrollWidth) {
                $title.show();
            }
            else {
                $title.hide();
            }
        }
    }
    decision_toggle_title();
    $(window).on('resize', function(){
        decision_toggle_title();
    });
});
