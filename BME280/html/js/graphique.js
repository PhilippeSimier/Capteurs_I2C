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
                        lineWidth: 3
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
            }
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
            weekdays: ["Dim "," Lun "," Mar "," Mer "," Jeu "," Ven "," Sam"],
			shortMonths: ['Jan', 'Fev', 'Mar', 'Avr', 'Mai', 'Juin', 'Juil','Août', 'Sept', 'Oct', 'Nov', 'Déc'],
            decimalPoint: ',',
            resetZoom: 'Reset zoom',
            resetZoomTitle: 'Reset zoom à 1:1'
            },
		tooltip: {
            crosshairs:[true],
            borderColor: '#4b85b7',
            shared: true,
            backgroundColor: '#edf1c8',
			
            formatter: function() {
               var s = '<b>'+ Highcharts.dateFormat("%e %B à %Hh%M", this.x) +'</b>';
			   
			   $.each(this.points, function(i, point) {
					s += '<br /><span style="color:'+ point.series.color +'">' + point.series.name + '</span> :<b> ' +Highcharts.numberFormat(point.y,1,","," ");
					s += unite + '</b>';
				});
			   
               return s;
            }
        }
	});
	
	// fonction pour afficher les données json reçues sous forme graphique
    function affiche( json ) {               	
		console.log(json);
			
		options.series[0] 		= json.series[0];
		unite = json.series[0].unite;
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
		$.getJSON("php/grandeur.php", {to: debut.format('MMMM D, YYYY'), from: fin.format('MMMM D, YYYY'), grandeur:grandeur}, affiche);	
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