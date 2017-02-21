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
					}
				},
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
			x: 200,
			verticalAlign: 'top',
			y: 40,
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
            weekdays: ["Dimanche "," Lundi "," Mardi "," Mercredi "," Jeudi "," Venderdi "," Samedi"],
			shortMonths: ['Jan', 'Fév', 'Mar', 'Avr', 'Mai', 'Juin', 'Juil','Août', 'Sept', 'Oct', 'Nov', 'Déc'],
            decimalPoint: ',',
            resetZoom: 'Reset zoom',
            resetZoomTitle: 'Reset zoom à 1:1'
            },
		
	});
	
	// fonction pour afficher les données json reçues sous forme graphique
    function affiche( json ) {               	
		console.log(json);
			
		options.series 		= json.series;
		
		options.title.text 		= json.title;
		

		//options.subtitle.text 	= json.subtitle;
		options.plotOptions.spline.pointStart = Date.parse(json.to); // pointStart définit la première valeur de x ici se sera json.to.
		$('#graphique').highcharts(options);
	}
	
	
	
	// fonction pour lancer une requète AJAX au click sur pression
	$("#pression").click( function() {
        grandeur = 'pression';
//unite = ' hPa';
        cb(start,end);		
	});
	
	// fonction pour lancer une requète AJAX au click sur temperature
	$("#temperature").click( function() {
		grandeur = 'temperature';
//		unite = ' °C';
        cb(start,end);	
	});

	// fonction pour lancer une requète AJAX au click sur humidité
	$("#humidite").click( function() {
 		grandeur = 'humidite';
//		unite = ' %';
        cb(start,end);	       
	});	
	
	// fonction pour afficher le datepicker


	function cb(debut, fin) {
		start = debut;
		end = fin;
		$('#reportrange span').html('du ' + debut.format('DD/MM/YYYY') + ' au ' + fin.format('DD/MM/YYYY'));
		$.getJSON("php/grandeur3.php", {to: debut.format('MMMM D, YYYY'), from: fin.format('MMMM D, YYYY'), grandeur:grandeur}, affiche);	
	}

			$('#reportrange').daterangepicker({
				startDate: start,
				endDate: end,
				ranges: {
				   'Today': [moment(), moment()],
				   'Yesterday': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
				   'Last 7 Days': [moment().subtract(6, 'days'), moment()],
				   'Last 30 Days': [moment().subtract(29, 'days'), moment()],
				   'This Month': [moment().startOf('month'), moment().endOf('month')],
				   'Last Month': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
				}
			}, cb);

			cb(start, end);
			$('input[name="daterange"]').daterangepicker();
		
});