<?php
// https://www.mt.com/mt_ext_files/Editorial/Generic/4/Operator_Manual_IND425_Editorial-Generic_1102076714093_files/22011482A.pdf

require_once('ini/ini.php');

//------------si des données  sont reçues on les enregistrent dans le fichier configuration.ini ---------
if( !empty($_POST['envoyer'])){

    //  lecture du fichier de configuration
    $array  = parse_ini_file("/home/pi/Capteurs_I2C/HX711/configuration.ini", true);
    //  Modification des valeurs pour la section [balance]
    $array['balance'] = array ('scale'  => $_POST['scale'],
                               'offset' => $_POST['offset'],
                               'gain'   => $_POST['gain'],
			       'unite'  => $_POST['unite'],
                               'precision' => $_POST['precision']);

    //  Ecriture du fichier de configuration modifié
    $ini = new ini ("/home/pi/Capteurs_I2C/HX711/configuration.ini");
    $ini->ajouter_array($array);
    $ini->ecrire(true);

}

// -------------- sinon lecture du fichier de configuration section balance -----------------------------
else
{
   $ini  = parse_ini_file("/home/pi/Capteurs_I2C/HX711/configuration.ini", true);
   $_POST['unite'] = $ini['balance']['unite'];
   $_POST['gain']  = $ini['balance']['gain'];
   $_POST['offset'] = $ini['balance']['offset'];
   $_POST['precision'] = $ini['balance']['precision'];
   $_POST['scale'] = $ini['balance']['scale'];
}

?>


<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <title>Balance</title>
    <!-- Bootstrap CSS version 4.1.1 -->
    <link rel="stylesheet" href="css/bootstrap.min.css">
	<script src="//ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
	<script src="scripts/bootstrap.min.js"></script> -->
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

		<script src="//ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
		<script type="text/javascript">
			var  enable = true;
			function affiche( data ) {               // fonction pour afficher les données reçues
				//console.log(data);               // affichage de data dans la console
				if (enable){
					$('#Weight').text(data.Weight);
				}
			}

			function requete_ajax(){
				// requete Ajax méthode getJSON
				if (enable){
				
				$.getJSON(
					"/cgi-bin/balanceJson", // Le fichier cible côté serveur. data au format Json
					affiche
				);
				}
			}

			$(document).ready(function(){
			    	$.getJSON("/cgi-bin/balanceJson", affiche); // affichage des données quand la page est dispo
				setInterval(requete_ajax, 1200);  // appel de la fonction requete_ajax toutes les 10 secondes

				$("#zero").click(function(){
					
					if (confirm("Confirmez-vous la correction de zéro ?")) { 
						enable = false;
						$('#Weight').text("RAZ");
						$.getJSON("/cgi-bin/tarageCGI", function(data){
							console.log(data);
							if(data.success == true){
								enable = true;
								$('input[name=offset]').val(data.offset);
								$('input[name=offset]').css("backgroundColor", "#00ff00");
							}
							else{
								window.alert(data.error);
							}	
							
						});
					}
			   });
			   
			   $("#calibrage").click(function(){
					var poids = prompt('Donnez la valeur du poids étalon','poids');
					enable = false;
					$('#Weight').text("Calibrage");
					console.log(poids);
					$.post("/cgi-bin/scaleCGI",
					{
					valeur: poids,
					},
					function(data, status){
						if(data.success == true){
							enable = true;
							$('input[name=scale]').val(data.scale);
							$('input[name=scale]').css("backgroundColor", "#00ff00");
							}
							else{
								window.alert(data.error);
							}
					});
					
				});	
			   
			});
		</script>

</head>
<body>
<div class="container" >
	<nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
		 <a class="navbar-brand" href="index.html">Accueil</a>
		  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		  </button>

		  <div class="collapse navbar-collapse" id="navbarsExampleDefault">
			<ul class="navbar-nav mr-auto">
			  <li class="nav-item active">
				<a class="nav-link" href="configuration.php">Configuration<span class="sr-only">(current)</span></a>
			  </li>
			  <li class="nav-item">
				<a class="nav-link" href="balance.php">Balance</a>
			  </li>
			  <li class="nav-item">
				<a class="nav-link" href="capteurs.php">Capteurs</a>
			  </li>
			</ul>
			
      </div>
    </nav>
	
	<div class="row" style="padding-top: 35px;">
        
	    <div class="col-md-6">
            <div class="popin">
                <h1 class="h1"><span id="Weight"></span></h1>
            </div>
			<div class="popin">
			<button class="btn btn-primary" value="zero" name="zero" id="zero">  Remise à zéro </button>
			<button class="btn btn-primary" value="calibrage" name="calibrage" id="calibrage"> Calibrage </button>
			</div>
	    </div>
		
		<div class="col-md-6">
            <div class="popin">
            <h2>Configuration de la balance</h2>
		        <form class="form-horizontal" method="post" action="<?php echo $_SERVER['SCRIPT_NAME'] ?>" name="configuration" >

					<div class="form-group">
						<label for="scale">Scale : </label>
						<input type="int"  name="scale" size="22" <?php echo 'value="' . $_POST['scale'] . '"'; ?> />
					</div>

					<div class="form-group">
						<label for="offset">Offset : </label>
						<input id="offset" type="int"  name="offset" size="22" <?php echo 'value="' . $_POST['offset'] . '"'; ?> />
					</div>

					<div class="form-group">
						<label for="gain">Gain : </label>
						<input type="radio" <?php if (isset($_POST['gain']) && $_POST['gain']=='128') echo 'checked="checked"' ?> name="gain"  value="128" /> 
						<label for="128"> 128 </label>
						<input type="radio" <?php if (isset($_POST['gain']) && $_POST['gain']=='64')  echo 'checked="checked"' ?> name="gain"  value="64" />
						<label for="64"> 64</label>
					</div>

					<div class="form-group">
						<label for="unite">Unite : </label>
						<input type="int"  name="unite" size="22" <?php echo 'value="' . $_POST['unite'] . '"'; ?> />
					</div>

					<div class="form-group">
						<label for="unite">Précision : </label>
						<input type="int"  name="precision" size="22" <?php echo 'value="' . $_POST['precision'] . '"'; ?> />
					</div>


					<button type="submit" class="btn btn-primary" value="Valider" name="envoyer" > Appliquer</button>
				</form>	
		
			</div>
        </div>

    </div>
</div>	
</body>
