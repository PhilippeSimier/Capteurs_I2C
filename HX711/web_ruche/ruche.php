<?php
require_once('ini/ini.php');

//------------si des données  sont reçues on les enregistrent dans le fichier configuration.ini ---------
if( !empty($_POST['envoyer'])){

    //  lecture du fichier de configuration
    $array  = parse_ini_file("/home/pi/Capteurs_I2C/HX711/configuration.ini", true);
    //  Modification des valeurs pour la section [ruche]
    $array['ruche'] = array ('id'  => $_POST['ruche_id'],
                             'altitude' => $_POST['ruche_altitude'],
							 'latitude' => $_POST['ruche_latitude'],
							 'longitude' => $_POST['ruche_longitude']
                            );
					   
    //  Ecriture du fichier de configuration modifié
    $ini = new ini ("/home/pi/Capteurs_I2C/HX711/configuration.ini");
    $ini->ajouter_array($array);
    $ini->ecrire(true);

}

// -------------- sinon lecture du fichier de configuration  -----------------------------
else
{
   $ini  = parse_ini_file("/home/pi/Capteurs_I2C/HX711/configuration.ini", true);
   
   $_POST['ruche_id'] = $ini['ruche']['id'];
   $_POST['ruche_altitude']  = $ini['ruche']['altitude'];
   $_POST['ruche_latitude']  = $ini['ruche']['latitude'];
   $_POST['ruche_longitude']  = $ini['ruche']['longitude'];

}

?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <title>Configuration</title>
    <!-- Bootstrap CSS version 4.1.1 -->
    <link rel="stylesheet" href="css/bootstrap.min.css">
	<script src="//ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
	<script src="scripts/bootstrap.min.js"></script>
	<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBKUqx5vjYkrX15OOMAxFbOkGjDfAPL1J8"></script>
	<script src="scripts/gmaps.js"></script>
    <link rel="stylesheet" href="/css/bootstrap.min.css" >
    <link rel="stylesheet" href="css/ruche.css" />

    <!-- Style pour la boite (div id popin) coins arrondis bordure blanche ombre -->
        <style type="text/css">
		.popin {
				background-color: #fff;
				border-radius: 8px;
				box-shadow: 0 0 20px #999;
				padding: 10px;
				margin: 10px;

		}

		.h1 {
			font-size: 80px;
		}

		</style>
		
		
		
		<script>
		
		$(function () {
    /*****************  options de placement et de zoom **************/
    /*****************  creation et affichage de la map **************/
	
	var	map = new GMaps({
		div: '#map-canvas',
		lat: <?php echo  $_POST['ruche_latitude']; ?> , 
		lng: <?php echo  $_POST['ruche_longitude']; ?> ,
		zoom : 13 ,
		mapType : 'terrain',
		click: function(e){
            console.log(e.latLng.lat().toFixed(6));
		    console.log(e.latLng.lng().toFixed(6));
		    map.removeMarkers();
		    map.addMarker({
                lat: e.latLng.lat(),
                lng: e.latLng.lng(),
                title: 'Nouvelle position'
			});
			$('input[name=ruche_latitude]').val(e.latLng.lat().toFixed(6));
			$('input[name=ruche_latitude]').css("backgroundColor", "#00ff00");
			$('input[name=ruche_longitude]').val(e.latLng.lng().toFixed(6));
			$('input[name=ruche_longitude]').css("backgroundColor", "#00ff00");
			// Elevation de la position 
			map.getElevations({
				locations : [[e.latLng.lat(),e.latLng.lng()]],
				callback : function (result, status){
				if (status == google.maps.ElevationStatus.OK) {
					console.log(result["0"].elevation.toFixed(0));
					$('input[name=ruche_altitude]').val(result["0"].elevation.toFixed(1));
					$('input[name=ruche_altitude]').css("backgroundColor", "#00ff00");
				}
			}
			});
        }
	});
	

	
	/************  placement d'une puce au milieu de la map ********/
	map.addMarker({
        lat: <?php echo  $_POST['ruche_latitude']; ?>, 
        lng: <?php echo  $_POST['ruche_longitude']; ?>,
        title: 'Ruche',
        infoWindow: {
          content: '<p> <?php echo "Ruche " . $_POST['ruche_id'] . "<br />Coordonnées GPS : </br> Lat : " . $_POST['ruche_latitude'] . "<br /> Lng : " . $_POST['ruche_longitude']; ?></p>' 
		  
        }
    });
	

    /******  gestion du formulaire positionner ********/
	
	$('#formulaire').submit(function(e){
        e.preventDefault();
		mon_adresse = $('#mon_adresse').val().trim(); 
			
        GMaps.geocode({
          address: mon_adresse,
          callback: function(results, status){
            if(status=='OK'){
              map.removeMarkers();
			  console.log(results["0"].formatted_address);
			  var latlng = results[0].geometry.location;
              map.setCenter(latlng.lat(), latlng.lng());
              var marker = map.addMarker({
                lat: latlng.lat(),
                lng: latlng.lng(),
				title: mon_adresse,
				infoWindow: {
					content: '<p>' + results["0"].formatted_address + '<br />Coordonnées GPS : ' + latlng.lat().toFixed(6) + ' , ' + latlng.lng().toFixed(6) + '</p>'
				}
				
              });
				$('input[name=ruche_latitude]').val(latlng.lat().toFixed(6));
				$('input[name=ruche_latitude]').css("backgroundColor", "#00ff00");
				$('input[name=ruche_longitude]').val(latlng.lng().toFixed(6));
				$('input[name=ruche_longitude]').css("backgroundColor", "#00ff00");
				$('#mon_adresse').val(results["0"].formatted_address);
				
				// Elevation de la position 
				map.getElevations({
					locations : [[latlng.lat(),latlng.lng()]],
					callback : function (result, status){
					if (status == google.maps.ElevationStatus.OK) {
						console.log(result["0"].elevation.toFixed(0));
						$('input[name=ruche_altitude]').val(result["0"].elevation.toFixed(1));
						$('input[name=ruche_altitude]').css("backgroundColor", "#00ff00");
					}
					}
				});
			  
            }
			else{
				alert("Oups cette adresse est inconnue !!!");
			}
          }
        });
      });
	
    /***** Menu *******************/

    map.setContextMenu({
        control: 'map',
        options: [{
            title: 'Changer la position',
            name: 'add_marker',
            action: function(e) {
                this.removeMarkers();
				this.addMarker({
                lat: e.latLng.lat(),
                lng: e.latLng.lng(),
                title: 'Nouvelle position'
				});
				$('input[name=ruche_latitude]').val(e.latLng.lat().toFixed(6));
				$('input[name=ruche_latitude]').css("backgroundColor", "#00ff00");
				$('input[name=ruche_longitude]').val(e.latLng.lng().toFixed(6));
				$('input[name=ruche_longitude]').css("backgroundColor", "#00ff00");
				
				
			}
		}, {
			title: 'Centrer la carte ici',
			name: 'center_here',
			action: function(e) {
				this.setCenter(e.latLng.lat(), e.latLng.lng());
			}
		}]
	})	
  
});
		
		</script>
				
</head>
<body>

<nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
		<a class="navbar-brand" href="index.html">Accueil</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>
		<div class="collapse navbar-collapse" id="navbarsExampleDefault">
        <ul class="navbar-nav mr-auto">
			
		  
			    <!-- Dropdown -->
			<li class="nav-item dropdown">
				  <a class="nav-link dropdown-toggle" href="#" id="navbardrop" data-toggle="dropdown">
					Configuration
				  </a>
				  <div class="dropdown-menu">
					<a class="dropdown-item" href="ruche.php">Ruche</a>
					<a class="dropdown-item" href="configuration.php">Bases de données</a>
					<a class="dropdown-item" href="balance.php">Balance</a>
				  </div>
			</li>
		  
		  
			<li class="nav-item">
				<a class="nav-link" href="apropos.html">A propos</a>
			</li>
          
        </ul>
        
		</div>
    </nav>

<div class="container" style="padding-top: 65px;">
    

		
		<div class="row">
			<div class="col-md-6 col-sm-12 col-xs-12">
				<div class="popin">
					<form class="form-horizontal" method="post" action="<?php echo $_SERVER['SCRIPT_NAME'] ?>" name="configuration" >
						<h2>Ruche</h2>
						
							<div class="form-group">
								<label for="ruche_id">Identificateur : </label>
								<input type="int"  name="ruche_id" size="22" <?php echo 'value="' . $_POST['ruche_id'] . '"'; ?> />
							</div>

							<div class="form-group">
								<label for="latitude">Latitude : </label>
								<input id="latitude" type="int"  name="ruche_latitude" size="22" <?php echo 'value="' . $_POST['ruche_latitude'] . '"'; ?> />
							</div>
							
							<div class="form-group">
								<label for="longitude">Longitude : </label>
								<input id="longitude" type="int"  name="ruche_longitude" size="22" <?php echo 'value="' . $_POST['ruche_longitude'] . '"'; ?> />
							</div>
							
							<div class="form-group">
								<label for="altitude">Altitude : </label>
								<input id="altitude" type="int"  name="ruche_altitude" size="22" <?php echo 'value="' . $_POST['ruche_altitude'] . '"'; ?> />
							</div>
							<button type="submit" class="btn btn-primary" value="Valider" name="envoyer" > Appliquer</button>
					</form>
				</div>
			</div>
			<!-- Localisation géographique -->
			<div class="col-md-6 col-sm-12 col-xs-12">	
				<div class="popin">
					<form method="post" id="formulaire" style="margin-bottom: 6px">
						<div class="form-group">
						<input type="text" id ="mon_adresse"  value="" placeholder="Adresse" style="width: 100%;" required/>
						</div>
						<input type="submit" class="btn" value="Positionner" />
					</form>
					<div id="map-canvas" style = "height: 500px; width: 100%;" ></div>
				</div>
			</div>	
				
			
		
		</div>
		<div class="row">
			
		</div>
		
</div>
	
</body>

	
		