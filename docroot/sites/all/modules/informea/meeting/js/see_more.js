(function($){
    Drupal.behaviors.meeting_see_more = {
        attach: function(context, settings) {
            $('.pane-node-body').once('tools_see_more', function() {
                var $body = $(this).find('.field-name-body');
                $body.expander({
                    slicePoint:       250,
                    expandPrefix:     '',
                    expandText:       'Show full text', // default is 'read more'
                    userCollapseText: 'Show less text'
                });
            });

        }
    };
})(jQuery);
