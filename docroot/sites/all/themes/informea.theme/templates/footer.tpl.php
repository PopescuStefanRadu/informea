<?php
/**
 * @file
 * footer.tpl.php
 */
?>
<footer class="footer">
  <div class="container">
    <?php if (!empty($page['footer'])): ?>
      <div class="footer-section">
        <?php print render($page['footer']); ?>
      </div><!-- .footer-section -->
    <?php endif; ?>
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Organizations'); ?></h5>
      <ul class="list-inline">
        <li>
          <a class="brand brand-hover brand-un" href="http://www.un.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UN'); ?>
          </a><!-- .brand .brand-hover .brand-un -->
        </li>
        <li>
          <a class="brand brand-hover brand-unep" href="http://www.unep.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UNEP'); ?>
          </a><!-- .brand .brand-hover .brand-unep -->
        </li>
        <li>
          <a class="brand brand-hover brand-fao" href="http://www.fao.org/" target="_blank">
            <div class="image"></div>
            <?php print t('FAO'); ?>
          </a><!-- .brand .brand-hover .brand-fao -->
        </li>
        <li>
          <a class="brand brand-hover brand-unesco" href="http://www.unesco.org/" target="_blank">
            <div class="image"></div>
            <?php print t('UNESCO'); ?>
          </a><!-- .brand .brand-hover .brand-unesco -->
        </li>
        <li>
          <a class="brand brand-hover brand-unece" href="http://www.unece.org/env/treaties/welcome.html" target="_blank">
            <div class="image"></div>
            <?php print t('UNECE'); ?>
          </a><!-- .brand .brand-hover .brand-unece -->
        </li>
        <li class="pull-right">
          <a class="brand brand-hover brand-eu" href="http://ec.europa.eu/" target="_blank">
            <div class="image"></div>
            <?php print t('European Union'); ?>
          </a><!-- .brand .brand-hover .brand-eu -->
        </li>
      </ul><!-- .list-inline -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Global treaties'); ?></h5>
      <ul class="list-inline">
        <li>
          <a class="brand brand-hover brand-unfccc" href="http://unfccc.int/" target="_blank">
            <div class="image"></div>
            <?php print t('UNFCCC'); ?>
          </a><!-- .brand .brand-hover .brand-unfccc -->
        </li>
        <li>
          <a class="brand brand-hover brand-unccd" href="http://www.unccd.int/" target="_blank">
            <div class="image"></div>
            <?php print t('UNCCD'); ?>
          </a><!-- .brand .brand-hover .brand-unccd -->
        </li>
        <li>
          <a class="brand brand-hover brand-ozone" href="http://ozone.unep.org/" target="_blank">
            <div class="image"></div>
            <?php print t('OZONE'); ?>
          </a><!-- .brand .brand-hover .brand-ozone -->
        </li>
        <li>
          <a class="brand brand-hover brand-basel" href="http://www.basel.int/" target="_blank">
            <div class="image"></div>
            <?php print t('BASEL'); ?>
          </a><!-- .brand .brand-hover .brand-basel -->
        </li>
        <li>
          <a class="brand brand-hover brand-rotterdam" href="http://www.pic.int/" target="_blank">
            <div class="image"></div>
            <?php print t('ROTTERDAM'); ?>
          </a><!-- .brand .brand-hover .brand-rotterdam -->
        </li>
        <li>
          <a class="brand brand-hover brand-stockholm" href="http://chm.pops.int/" target="_blank">
            <div class="image"></div>
            <?php print t('STOCKHOLM'); ?>
          </a><!-- .brand .brand-hover .brand-stockholm -->
        </li>
        <li>
          <a class="brand brand-hover brand-cbd" href="http://www.cbd.int/" target="_blank">
            <div class="image"></div>
            <?php print t('CBD'); ?>
          </a><!-- .brand .brand-hover .brand-cbd -->
        </li>
        <li>
          <a class="brand brand-hover brand-cites" href="http://www.cites.org/" target="_blank">
            <div class="image"></div>
            <?php print t('CITES'); ?>
          </a><!-- .brand .brand-hover .brand-cites -->
        </li>
        <li>
          <a class="brand brand-hover brand-whc" href="http://whc.unesco.org/" target="_blank">
            <div class="image"></div>
            <?php print t('WHC'); ?>
          </a><!-- .brand .brand-hover .brand-whc -->
        </li>
        <li>
          <a class="brand brand-hover brand-ramsar" href="http://www.ramsar.org/" target="_blank">
            <div class="image"></div>
            <?php print t('Ramsar'); ?>
          </a><!-- .brand .brand-hover .brand-ramsar -->
        </li>
        <li>
          <a class="brand brand-hover brand-itpgrfa" href="http://www.planttreaty.org/" target="_blank">
            <div class="image"></div>
            <?php print t('ITPGRFA'); ?>
          </a><!-- .brand .brand-hover .brand-itpgrfa -->
        </li>
        <li>
          <a class="brand brand-hover brand-cms" href="http://www.cms.int/" target="_blank">
            <div class="image"></div>
            <?php print t('CMS'); ?>
          </a><!-- .brand .brand-hover .brand-cms -->
        </li>
      </ul><!-- .list-inline -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <h5 class="text-uppercase"><?php print t('Regional treaties'); ?></h5>
      <div class="row">
       <!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('UNECE'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Aarhus Convention'), 'http://www.unece.org/env/pp/welcome.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Espoo Convention'), 'http://www.unece.org/env/eia/welcome.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Long-Range Transboundary Air Pollution'), 'http://www.unece.org/env/lrtap/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('The Kyiv Protocol'), 'http://www.unece.org/env/eia/sea_protocol.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Protocol on Water and Health'), 'http://www.unece.org/?id=2975', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Water Convention'), 'http://www.unece.org/env/water/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Kiev Protocol'), 'http://www.unece.org/env/pp/prtr.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Industrial Accidents Convention'), 'http://www.unece.org/env/teia.html', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('CMS'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('ACCOBAMS'), 'http://www.accobams.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('AEWA'), 'http://www.unep-aewa.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('ASCOBANS'), 'http://www.ascobans.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('EUROBATS'), 'http://www.eurobats.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li class="divider"></li>
            <li><?php print l(t('ACAP'), 'http://www.the-acap.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('International Gorilla Conservation Programme'), 'http://www.igcp.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('WADDEN SEA SEALS'), 'http://www.waddensea-secretariat.org/', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('Regional Seas'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Abidjan Convention'), 'http://abidjanconvention.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Antigua Convention'), 'http://www.iattc.org/IATTCdocumentationENG.htm', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Apia Convention'), 'http://www.sprep.org/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Barcelona Convention'), 'http://www.unep.ch/regionalseas/regions/med/t_barcel.htm', array('attributes' => array('target' => '_blank'))); ?></li>
            <li class="divider"></li>
            <li><?php print l(t('Jeddah Convention'), 'http://www.unep.ch/regionalseas/main/persga/redconv.html', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Nairobi Convention'), 'http://www.unep.org/nairobiconvention/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Noumea Convention'), 'http://www2.unitar.org/cwm/publications/cbl/synergy/cat1_agree/noumea.htm', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
        <div class="col-md-3">
          <h6><?php print t('Regional Treaties'); ?></h6>
          <ul class="list-unstyled">
            <li><?php print l(t('Bamako Convention'), 'http://www.opcw.org/chemical-weapons-convention/related-international-agreements/toxic-chemicals-and-the-environment/bamako-convention/', array('attributes' => array('target' => '_blank'))); ?></li>
            <li><?php print l(t('Lusaka Agreement'), 'http://www.lusakaagreement.org/', array('attributes' => array('target' => '_blank'))); ?></li>
          </ul><!-- .list-unstyled -->
        </div><!-- .col-md-3 -->
      </div><!-- .row -->
    </div><!-- .footer-section -->
    <div class="footer-section">
      <p>
        <?php print t('<a href="@url">Terms and conditions</a> &dash; Portions Copyright &copy; United Nations, FAO, UNEP, UNESCO', array('@url' => url('disclaimer'))); ?>
        &nbsp; &middot; &nbsp;<?php print $user->uid == 0 ? l(t('Log in'), 'user/login') : l(t('Log out'), 'user/logout'); ?>
      </p>
    </div><!-- .footer-section -->
  </div><!-- .container -->
</footer><!-- .footer -->
<a class="back-to-top" href="#"></a>
