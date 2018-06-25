<?php
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

    <title>Configuration Balance</title>
    <!-- Bootstrap CSS version 4.1.1 -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" integrity="sha384-WskhaSGFgHYWDcbwN70/dfYBj47jz9qbsMId/iRN3ewGhXQFZCSftd1LZCfmhktB" crossorigin="anonymous">
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js" integrity="sha384-smHYKdLADwkXOn1EmN1qk/HfnUcbVRZyYmZ4qpPea6sjB/pTJ0euyQp0Mk8ck+5T" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="/css/bootstrap.min.css" >

    <!-- Style pour la boite (div id popin) coins arrondis bordure blanche ombre -->
        <style type="text/css">
		.popin {
				background-color: #fff;
				border-radius: 8px;
				box-shadow: 0 0 20px #999;
				padding: 10px;
				margin: 30px;

		}

		.h1 {
			font-size: 80px;
		}

		</style>

		<script src="//ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
		<script type="text/javascript">
			function affiche( data ) {               // fonction pour afficher les données reçues
				console.log(data);               // affichage de data dans la console
				$('#Weight').text(data.Weight);

			}

			function requete_ajax(){
				// requete Ajax méthode getJSON
				$.getJSON(
					"/cgi-bin/balanceJson", // Le fichier cible côté serveur. data au format Json
					affiche
				);
			}

			$(document).ready(function(){

			    $.getJSON("/cgi-bin/balanceJson", affiche); // affichage des données quand la page est dispo
				setInterval(requete_ajax, 1200);  // appel de la fonction requete_ajax toutes les 10 secondes
				//setInterval("requete_ajax()", 1000);  écriture alternative  possible avec une chaîne "requete_ajax()"
			});
		</script>

</head>
<body>
    <div class="row">
        <div class="col-md-6">
            <div class="popin">
            <h2>Configuration de la balance</h2>
		<form class="form-horizontal" method="post" action="<?php echo $_SERVER['SCRIPT_NAME'] ?>" name="configuration" >

		<div class="form-group">
			<label for="scale">Scale : </label>
			<input type="int"  name="scale" size="30" <?php echo 'value="' . $_POST['scale'] . '"'; ?> />
		</div>

		<div class="form-group">
			<label for="offset">Offset : </label>
			<input type="int"  name="offset" size="30" <?php echo 'value="' . $_POST['offset'] . '"'; ?> />
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
			<input type="int"  name="unite" size="30" <?php echo 'value="' . $_POST['unite'] . '"'; ?> />
		</div>

                <div class="form-group">
                        <label for="unite">Précision : </label>
                        <input type="int"  name="precision" size="30" <?php echo 'value="' . $_POST['precision'] . '"'; ?> />
                </div>


		<button type="submit" class="btn btn-primary" value="Valider" name="envoyer" > Valider</button>

            </div>
            </div>

	    <div class="col-md-6">
            <div class="popin">
                <h1 class="h1"><span id="Weight"></span></h1>
            </div>
	    </div>

        </div>
</body>
