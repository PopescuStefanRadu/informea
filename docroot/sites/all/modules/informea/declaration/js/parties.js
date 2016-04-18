jQuery(document).ready(function() {
  var map = AmCharts.makeChart('ammap_div', {
    type: 'map',
    theme: 'light',
    pathToImages: 'http://www.amcharts.com/lib/3/images/',
    dataProvider: {
      alpha: 1,
      map: 'worldHigh',
      areas: Drupal.settings.map.memberParties
    },
    backgroundZoomsToTop: true,
    areasSettings: {
      color: '#0099D5',
      rollOverColor: '#ED9F0D',
      selectable: true,
      selectedColor: '#ED9F0D'
    },
    zoomControl: {
      buttonFillColor: '#0099D5',
      buttonRollOverColor: '#FFCC66',
      zoomFactor: 4
    }
  });
});
