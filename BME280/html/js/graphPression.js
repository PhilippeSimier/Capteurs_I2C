$(function () {
	var options = {
        chart: {
            type: 'spline',
			zoomType: 'x'
        },
		plotOptions: {
            spline: {
                lineWidth: 2,
                states: {
                    hover: {
                        lineWidth: 3
                    }
                },
                marker: {
                    enabled: false
                },
                pointInterval: 600000, // 600s soit 10 min
                pointStart: Date.parse("")
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
            text: '© Section SNIR Le Mans',
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
                text: 'Pression'
            },
			   labels: {
                formatter: function () {
                    return this.value + ' hPa';
                }
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: ' hPa'
        },
        
        series: []
    };
	
		
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
               var s = '<b>'+ Highcharts.dateFormat('%e %B à %H:%M', this.x) +'</b>';
			   
			   $.each(this.points, function(i, point) {
					var unit = {
					    'Pression': ' hPa',           
					}[this.point.series.name];
					s = s + '<br />' + '<span style="color:'+ point.series.color +'">' + point.series.name + '</span> : ' +Highcharts.numberFormat(point.y,1,","," ") + ' hPa';
                });
			   
               return s;
            }
        }
	});		
	
	$.getJSON("pression.php", function(json) {
            console.log(json);
			
			options.series[0] 		= json.serie;
			options.title.text 		= json.title;
			options.subtitle.text 	= json.subtitle;
			options.plotOptions.spline.pointStart = Date.parse(json.to);
			$('#average').text(json.average);
			$('#maxi').text(json.maxi);
			$('#mini').text(json.mini);
			$('#container').highcharts(options);
		
			
        });
	
	$("#jour").click( function() {
            $.get("pression.php", 
			function(json) {
            console.log(json);
			options.series[0] = json.serie;
			options.title.text = json.title;
			options.plotOptions.spline.pointStart = Date.parse(json.to);
			$('#average').text(json.average);
			$('#maxi').text(json.maxi);
			$('#mini').text(json.mini);	
			$('#container').highcharts(options);
			
        });	
	});	
	
	$("#semaine").click( function() {
            $.get("pression.php", 
			{to: "uneSemaine"},
			function(json) {
            console.log(json);
			options.series[0] = json.serie;
			options.title.text = json.title;
			options.plotOptions.spline.pointStart = Date.parse(json.to);
			$('#average').text(json.average);
			$('#maxi').text(json.maxi);
			$('#mini').text(json.mini);	
			$('#container').highcharts(options);
			
        });	
	});	
	
	$("#button").click( function() {
			
            $.get("pression.php", 
				{to: "troisJours"},
				function(json) {
				console.log(json);
				options.series[0] = json.serie;
				options.title.text = json.title;
				options.plotOptions.spline.pointStart = Date.parse(json.to); 
				$('#average').text(json.average);
				$('#maxi').text(json.maxi);
				$('#mini').text(json.mini);	
				$('#container').highcharts(options);
			
			});
    });	
	
	
    
    
});