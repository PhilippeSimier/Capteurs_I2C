<?php
require_once('ini/ini.php');

//------------si des données  sont reçues on les enregistrent dans le fichier configuration.ini ---------
if( !empty($_POST['envoyer'])){

    //  lecture du fichier de configuration
    $array  = parse_ini_file("/home/pi/Capteurs_I2C/HX711/configuration.ini", true);
    //  Modification des valeurs pour la section [ruche]
 
	//  Modification des valeurs pour la section [BDlocale]
	$array['BDlocale'] = array ('host'  => $_POST['BDlocale_host'],
                                'user' => $_POST['BDlocale_user'],
							    'passwd' => $_POST['BDlocale_passwd'],
								'bdd' => $_POST['BDlocale_bdd'],
                               );
	//  Modification des valeurs pour la section [BDdistante]
	$array['BDdistante'] = array ('host'  => $_POST['BDdistante_host'],
                                'user' => $_POST['BDdistante_user'],
								'passwd' => $_POST['BDdistante_passwd'],
							    'bdd' => $_POST['BDdistante_bdd'],
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
     
   $_POST['BDlocale_host'] = $ini['BDlocale']['host'];
   $_POST['BDlocale_user'] = $ini['BDlocale']['user'];
   $_POST['BDlocale_passwd'] = $ini['BDlocale']['passwd'];
   $_POST['BDlocale_bdd'] = $ini['BDlocale']['bdd'];
   
   $_POST['BDdistante_host'] = $ini['BDdistante']['host'];
   $_POST['BDdistante_user'] = $ini['BDdistante']['user'];
   $_POST['BDdistante_passwd'] = $ini['BDdistante']['passwd'];
   $_POST['BDdistante_bdd'] = $ini['BDdistante']['bdd'];
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
</head>
<body>
<div class="container" style="padding-top: 35px;">
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

		<form class="form-horizontal" method="post" action="<?php echo $_SERVER['SCRIPT_NAME'] ?>" name="configuration" >
		<div class="row">

			
			<div class="col-md-6 col-sm-6 col-xs-12">
				<div class="popin">
				<h2>Bdd locale</h2>
					
						<div class="form-group">
							<label for="scale">Host : </label>
							<input type="int"  name="BDlocale_host" size="22" <?php echo 'value="' . $_POST['BDlocale_host'] . '"'; ?> />
						</div>

						<div class="form-group">
							<label for="offset">Utilisateur : </label>
							<input id="offset" type="int"  name="BDlocale_user" size="22" <?php echo 'value="' . $_POST['BDlocale_user'] . '"'; ?> />
						</div>
						
						<div class="form-group">
							<label for="offset">Mot de passe : </label>
							<input id="offset" type="int"  name="BDlocale_passwd" size="22" <?php echo 'value="' . $_POST['BDlocale_passwd'] . '"'; ?> />
						</div>
						
						<div class="form-group">
							<label for="offset">Bdd : </label>
							<input id="offset" type="int"  name="BDlocale_bdd" size="22" <?php echo 'value="' . $_POST['BDlocale_bdd'] . '"'; ?> />
						</div>
			
				</div>
			</div>	
				
			<div class="col-md-6 col-sm-6 col-xs-12">
				<div class="popin">
				<h2>Bdd distante</h2>
					
						<div class="form-group">
							<label for="scale">Host : </label>
							<input type="int"  name="BDdistante_host" size="22" <?php echo 'value="' . $_POST['BDdistante_host'] . '"'; ?> />
						</div>

						<div class="form-group">
							<label for="offset">Utilisateur : </label>
							<input id="offset" type="int"  name="BDdistante_user" size="22" <?php echo 'value="' . $_POST['BDdistante_user'] . '"'; ?> />
						</div>
						
						<div class="form-group">
							<label for="offset">Mot de passe : </label>
							<input id="offset" type="int"  name="BDdistante_passwd" size="22" <?php echo 'value="' . $_POST['BDdistante_passwd'] . '"'; ?> />
						</div>
						
						<div class="form-group">
							<label for="offset">Bdd : </label>
							<input id="offset" type="int"  name="BDdistante_bdd" size="22" <?php echo 'value="' . $_POST['BDdistante_bdd'] . '"'; ?> />
						</div>
				</div>
			</div>
		
		</div>
		<div class="row">
			<button type="submit" class="btn btn-primary" value="Valider" name="envoyer" > Appliquer</button>
		</div>
		</form>
</div>
	
</body>

	
		