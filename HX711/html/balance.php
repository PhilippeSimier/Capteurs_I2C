<?php
require_once('ini/ini.php');

//------------si des données  sont reçues on les enregistrent dans le fichier configuration.ini ---------
if( !empty($_POST['envoyer'])){

    $array = array();
    $array['balance'] = array ('scale'  => $_POST['scale'],
                               'offset' => $_POST['offset'],
                               'gain'   => $_POST['gain'],
			       'unite'  => $_POST['unite'],
                               'precision' => $_POST['precision']);
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
</head>
<body>
    <div class="row">
	<div class=" col-md-3"></div>
    <div class=" col-md-6">

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
	<div class=" col-md-3"></div>
    </div>
</body>
