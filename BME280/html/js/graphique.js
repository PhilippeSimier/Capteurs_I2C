$(function () {
	var options = {
        chart: {
			zoomType: 'xy',
			className: 'panel panel-info',
			backgroundColor: '#F9F9F9'
        },
		plotOptions: {
            spline: {
                lineWidth: 2,   // épaisseur de la ligne
                states: {
                    hover: {
                        lineWidth: 2
                    }
                },
                marker: {
                    enabled: false   // disable the point marker.
                },
                pointInterval: 600000 // pointInterval définit l'intervalle des valeurs sur x (600s soit 10 min)
            }
        },
		title: {
            text: '',
            x: -20 //center
        },
        subtitle: {
            text: '',
            x: -20
        },
		credits: {
            text: '© PST  Le Mans',
            href: 'http://philippes.ddns.net'
		},
		
        xAxis: {
            type: 'datetime',
			startOnTick: false,
            labels: {
                overflow: 'justify'
            },
			crosshair: true
			
        },
        yAxis: {
            title: {
                text: ''
            },
			labels: {
                formatter: function () {
					return this.value;
                }
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
		tooltip: {
			shared: true,
			borderColor: '#4b85b7',
			backgroundColor: '#edf1c8',
			dateTimeLabelFormats:{second:"%A %e %B à %Hh%M"}
		},
		legend: {
			layout: 'vertical',
			align: 'left',
			x: 100,
			verticalAlign: 'top',
			y: 80,
			floating: true,
			backgroundColor: (Highcharts.theme && Highcharts.theme.legendBackgroundColor) || '#FFFFFF'
		},

        series: []
    };

    var start = moment().subtract(1, 'days');
	var end = moment();
	var grandeur = 'pression';
	var unite = ' hPa';
		
	Highcharts.setOptions({
       		lang: {
            months: ["Janvier "," Février "," Mars "," Avril "," Mai "," Juin "," Juillet "," Août ","Septembre "," Octobre "," Novembre "," Décembre"],
            weekdays: ["Dimanche "," Lundi "," Mardi "," Mercredi "," Jeudi "," Vendredi "," Samedi"],
			shortMonths: ['Jan', 'Fev', 'Mar', 'Avr', 'Mai', 'Juin', 'Juil','Août', 'Sept', 'Oct', 'Nov', 'Déc'],
            decimalPoint: ',',
            resetZoom: 'Reset zoom',
            resetZoomTitle: 'Reset zoom à 1:1'
            } 

	});
	
	// fonction pour afficher les données json reçues sous forme graphique
    function affiche( json ) {               	
		console.log(json);
			
		options.series[0] 		= json.series[0];
		unite = json.series[0].tooltip.valueSuffix;
		options.title.text 		= json.title;
		

		//options.subtitle.text 	= json.subtitle;
		options.plotOptions.spline.pointStart = Date.parse(json.to); // pointStart définit la première valeur de x ici se sera json.to.
		$('#average').text(json.average + unite);
		$('#maxi').text(json.maxi + unite);
		$('#mini').text(json.mini + unite);
		$('#container').highcharts(options);
	}
	
	
	
	// fonction pour lancer une requète AJAX au click sur pression
	$("#pression").click( function() {
        grandeur = 'pression';
        cb(start,end);		
	});
	
	// fonction pour lancer une requète AJAX au click sur temperature
	$("#temperature").click( function() {
		grandeur = 'temperature';
        cb(start,end);	
	});

	// fonction pour lancer une requète AJAX au click sur humidité
	$("#humidite").click( function() {
 		grandeur = 'humidite';
        cb(start,end);	       
	});	
	
	// fonction pour afficher le datepicker


	function cb(debut, fin) {
		start = debut;
		end = fin;
		$('#reportrange span').html('du ' + debut.format('DD/MM/YYYY') + ' au ' + fin.format('DD/MM/YYYY'));
		$.getJSON("php/grandeur.php", {to: debut.format('MMMM D, YYYY'), from: fin.format('MMMM D, YYYY'), grandeur:grandeur}, affiche);	
	}

			$('#reportrange').daterangepicker({
				   "locale": {
						"format": "DD/MM/YYYY",
						"separator": " - ",
						"applyLabel": "Appliquer",
						"cancelLabel": "Annuler",
						"fromLabel": "de",
						"toLabel": "à",
						"customRangeLabel": "Définir l'intervalle",
						"weekLabel": "W",
						"daysOfWeek": [
							"Di",
							"Lu",
							"Ma",
							"Me",
							"Je",
							"Ve",
							"Sa"
						],
						"monthNames": [
							"Janvier",
							"Février",
							"Mars",
							"Avril",
							"Mai",
							"Juin",
							"Juillet",
							"Août",
							"Septembre",
							"Octobre",
							"Novembre",
							"Decembre"
						],
						"firstDay": 1
					},

				startDate: start,
				endDate: end,
				ranges: {
				   'Aujourd\'hui': [moment(), moment()],
				   'Hier': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
				   'Derniers 7 jours': [moment().subtract(6, 'days'), moment()],
				   'Derniers 30 jours': [moment().subtract(29, 'days'), moment()],
				   'Ce mois': [moment().startOf('month'), moment().endOf('month')],
				   'Mois précédent': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
				}
				
			}, cb);

			cb(start, end);
			$('input[name="daterange"]').daterangepicker();
		
});