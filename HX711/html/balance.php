 <?php

$balanceIni = fopen('/home/pi/Capteurs_I2C/HX711/balance.ini', 'r+');

//--------------------si des données  sont reçues---------------------------------------------------------
if( !empty($_POST['envoyer'])){
	$ligne =  $_POST['scale'] . " " . $_POST['offset']. " " . $_POST['gain'] . " " . $_POST['unite'] . " " . $_POST['precision'] . "                ";
    fputs($balanceIni, $ligne);

}
else
{

    $ligne = fgets($balanceIni);
    list($_POST['scale'], $_POST['offset'], $_POST['gain'], $_POST['unite'], $_POST['precision']) = explode(" ", $ligne);


}

fclose($balanceIni);
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
