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
                        lineWidth: 2  // épaisseur de la ligne quand la souris est au dessus
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
        yAxis: [{ // Primary yAxis
				gridLineWidth: 1,
				labels: {
					format: '{value}',
					style: {
						color: Highcharts.getOptions().colors[0]
					}
				},
				title: {
					text: 'Temperature',
					style: {
						color: Highcharts.getOptions().colors[0]
					}
				}
			}, { // Secondary yAxis
				gridLineWidth: 0,
				title: {
					text: 'Pression',
					style: {
						color: Highcharts.getOptions().colors[1]
					},
				},	
				plotLines: [{
                    value: 1013,   // ligne grise pour la pression atmosphérique moyenne
                    width: 2,
                    color: '#CCCCCC'
					}]	
				,
				labels: {
					format: '{value}',
					style: {
						color: Highcharts.getOptions().colors[1]
					}
				},
				opposite: true

			}, { // Tertiary yAxis
				gridLineWidth: 0,
				
				title: {
					text: 'humidité',
					style: {
						color: Highcharts.getOptions().colors[2]
					}
				},
				labels: {
					format: '{value}',
					style: {
						color: Highcharts.getOptions().colors[2]
					}
				},
				opposite: true
			}],
		
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
			y: 40,
			floating: true,
			backgroundColor: (Highcharts.theme && Highcharts.theme.legendBackgroundColor) || '#FFFFFF'
		},
        series: []
    };
    
	var chart;
    var start = moment();
	var end = moment();
	var grandeur = 'pression';
	var unite = ' hPa';
		
	Highcharts.setOptions({
        lang: {
            months: ["Janvier "," Février "," Mars "," Avril "," Mai "," Juin "," Juillet "," Août ","Septembre "," Octobre "," Novembre "," Décembre"],
            weekdays: ["Dimanche "," Lundi "," Mardi "," Mercredi "," Jeudi "," Venderdi "," Samedi"],
			shortMonths: ['Jan', 'Fév', 'Mar', 'Avr', 'Mai', 'Juin', 'Juil','Août', 'Sept', 'Oct', 'Nov', 'Déc'],
            decimalPoint: ',',
            resetZoom: 'Reset zoom',
            resetZoomTitle: 'Reset zoom à 1:1',
			downloadPNG: "Télécharger au format PNG image",
            downloadJPEG: "Télécharger au format JPEG image",
            downloadPDF: "Télécharger au format PDF document",
            downloadSVG: "Télécharger au format SVG vector image",
            exportButtonTitle: "Exporter image ou document",
            printChart: "Imprimer le graphique",
			noData: "Aucune donnée à afficher",			
            loading: "Chargement..."			
            },
		
	});

	
	// fonction pour afficher les données json reçues sous forme graphique
    function affiche( json ) {               	
		console.log(json);
			
		options.series 		= json.series;
		options.title.text 	= json.title;
		options.plotOptions.spline.pointStart = Date.parse(json.to); // pointStart définit la première valeur de x ici se sera json.to.
		chart = Highcharts.chart('graphique', options );
		if (visible0 == false) {chart.series[0].hide();}
		if (visible1 == false) {chart.series[1].hide();}
		if (visible2 == false) {chart.series[2].hide();}

	}
	
	// Action sur b0
	var $b0 = $('#b0');
	var visible0 = true;
	$b0.click(function () {
		var temperature = chart.series[0];
		if (temperature.visible) {
			temperature.hide();
			$b0.html('Afficher température');
			visible0 = false;
		} else {
			temperature.show();
			$b0.html('Cacher température');
			visible0 = true;
		}
	});
	
	// Action sur b1
	var $b1 = $('#b1');
	var visible1 = true;
	$b1.click(function () {
		var pression = chart.series[1];
		if (pression.visible) {
			pression.hide();
			$b1.html('Afficher pression');
			visible1 = false;
		} else {
			pression.show();
			$b1.html('Cacher pression');
			visible1 = true;
		}
	});
	
	// Action sur b2
	var $b2 = $('#b2');
	var visible2 = true;
	$b2.click(function () {
		var humidite = chart.series[2];
		if (humidite.visible) {
			humidite.hide();
			$b2.html('Afficher humidité');
			visible2 = false;
		} else {
			humidite.show();
			$b2.html('Cacher humidité');
			visible2 = true;
		}
	});
	
	
	
	// fonction pour lancer la requete AJAX methode GET
	function cb(debut, fin) {
		start = debut;
		end = fin;
		$('#reportrange span').html('du ' + debut.format('DD/MM/YYYY') + ' au ' + fin.format('DD/MM/YYYY'));
		$.getJSON("php/grandeur3.php", {to: debut.format('MMMM D, YYYY'), from: fin.format('MMMM D, YYYY'), grandeur:grandeur}, affiche);
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