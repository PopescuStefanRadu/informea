<ul class="informea-share-widget">
  <li>
    <a id="btn-share-facebook-<?php print $node->nid; ?>" onclick="window.open(this.href, 'informea-share', 'left=20,top=20,width=500,height=500,toolbar=1,resizable=0'); return false;" href="https://www.facebook.com/sharer/sharer.php?u=<?php print $url ?>">
      <img src="<?php print file_create_url(drupal_get_path('theme', 'informea_theme') . '/img/btn-share-facebook.png') ?>" alt="Facebook">
    </a>
  </li>
  <li>
    <a id="btn-share-twitter-<?php print $node->nid; ?>" href="<?php print $tweet_url; ?>">
      <img src="<?php print file_create_url(drupal_get_path('theme', 'informea_theme') . '/img/btn-share-twitter.png') ?>" alt="Twitter">
    </a>
  </li>
  <li>
    <a id="btn-share-linkedin-<?php print $node->nid; ?>" href="https://www.linkedin.com/shareArticle?mini=true&amp;url=<?php print $url ?>">
      <img src="<?php print file_create_url(drupal_get_path('theme', 'informea_theme') . '/img/btn-share-linkedin.png') ?>" alt="LinkedIn">
    </a>
  </li>
</ul>
<script>
  (function ($) {
    $('#btn-share-twitter-<?php print $node->nid; ?>').click(function (event) {
      event.preventDefault();

      var width  = 575,
        height = 400,
        left   = ($(window).width()  - width)  / 2,
        top    = ($(window).height() - height) / 2,
        url    = this.href,
        opts   = 'status=1' +
          ',width='  + width  +
          ',height=' + height +
          ',top='    + top    +
          ',left='   + left;

      window.open(url, 'Twitter', opts);
    });

    $('#btn-share-linkedin-<?php print $node->nid; ?>').click(function (event) {
      event.preventDefault();

      var width  = 575,
        height = 400,
        left   = ($(window).width()  - width)  / 2,
        top    = ($(window).height() - height) / 2,
        url    = this.href,
        opts   = 'status=1' +
          ',width='  + width  +
          ',height=' + height +
          ',top='    + top    +
          ',left='   + left;

      window.open(url, 'LinkedIn', opts);
    });
  })(jQuery);
</script>
