<?php

require_once("config.inc.php");

function connexionBD() {
    try {

        $bdd = new PDO('mysql:host=' . SERVEURBD . ';dbname=' . NOMDELABASE, LOGIN, MOTDEPASSE);
    } catch (Exception $ex) {
        die('<br />Pb connexion serveur BD : ' . $ex->getMessage());
    }
    return $bdd;
}


// retourne les valeurs sous le format tableau de data
// ["22.56","22.5","22.5","22.56","22.56","22.5","22.44","22.44","22.38","22.31","22.25","22.13"]


function getTemperature($to) {
    $bdd = connexionBD();
	

    $requete = $bdd->prepare("SELECT * FROM `dataBme280` WHERE date BETWEEN :to AND now() ORDER BY `id` ASC;");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));

    $valeur = array();   
    while ($ligne = $requete->fetch()) {
        array_push($valeur, $ligne['temperature']);	
    }
	
	$requete = $bdd->prepare("SELECT avg(temperature) as average, min(temperature) as mini, max(temperature) as maxi FROM `dataBme280` WHERE date BETWEEN :to AND now()");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));
	$ligne = $requete->fetch();
	
	$options['average'] =  round($ligne['average'], 1);
	$options['maxi']    =  round($ligne['maxi'], 1);
	$options['mini']    =  round($ligne['mini'], 1);
	
	$options['title'] = "du ".substr($to, 0, -14);
	//$options['debug'] = $to;
	$options['subtitle'] = "BME280 sur ".$_SERVER["SERVER_NAME"];
	
	$to1 = substr($to, 0, -6)."+0000";
	$options['to'] = strtr($to1, " ", "T");  //la date au format ISO 8601
	
	$data['name']  = "Temperature";
	$data['data']  = $valeur;
	
	$options[serie] = $data;
	
	
	$requete->closeCursor();
    echo json_encode($options, JSON_NUMERIC_CHECK);

}

function getPression($to) {
    $bdd = connexionBD();
	

    $requete = $bdd->prepare("SELECT * FROM `dataBme280` WHERE date BETWEEN :to AND now() ORDER BY `id` ASC;");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));

    $valeur = array();   
    while ($ligne = $requete->fetch()) {
        array_push($valeur, $ligne['pression']);	
    }
	
	$requete = $bdd->prepare("SELECT avg(pression) as average, min(pression) as mini, max(pression) as maxi FROM `dataBme280` WHERE date BETWEEN :to AND now()");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));
	$ligne = $requete->fetch();
	
	$options['average'] =  round($ligne['average'], 1);
	$options['maxi']    =  round($ligne['maxi'], 1);
	$options['mini']    =  round($ligne['mini'], 1);
	
	$options['title'] = "du ".substr($to, 0, -14);
	//$options['debug'] = $to;
	$options['subtitle'] = "BME280 sur ".$_SERVER["SERVER_NAME"];
	
	$to1 = substr($to, 0, -6)."+0000";
	$options['to'] = strtr($to1, " ", "T");  //la date au format ISO 8601
	
	$data['name']  = "Pression";
	$data['data']  = $valeur;
	
	$options[serie] = $data;
	
	
	$requete->closeCursor();
    echo json_encode($options, JSON_NUMERIC_CHECK);

}

function getHumidite($to) {
    $bdd = connexionBD();
	

    $requete = $bdd->prepare("SELECT * FROM `dataBme280` WHERE date BETWEEN :to AND now() ORDER BY `id` ASC;");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));

    $valeur = array();   
    while ($ligne = $requete->fetch()) {
        array_push($valeur, $ligne['humidite']);	
    }
	
	$requete = $bdd->prepare("SELECT avg(humidite) as average, min(humidite) as mini, max(humidite) as maxi FROM `dataBme280` WHERE date BETWEEN :to AND now()");
    $requete->bindParam(":to", $to);
    $requete->execute() or die(print_r($requete->errorInfo()));
	$ligne = $requete->fetch();
	
	$options['average'] =  round($ligne['average'], 1);
	$options['maxi']    =  round($ligne['maxi'], 1);
	$options['mini']    =  round($ligne['mini'], 1);
	
	$options['title'] = "du ".substr($to, 0, -14);
	//$options['debug'] = $to;
	$options['subtitle'] = "BME280 sur ".$_SERVER["SERVER_NAME"];
	
	$to1 = substr($to, 0, -6)."+0000";
	$options['to'] = strtr($to1, " ", "T");  //la date au format ISO 8601
	
	$data['name']  = "Humidite";
	$data['data']  = $valeur;
	
	$options[serie] = $data;
	
	$requete->closeCursor();
    echo json_encode($options, JSON_NUMERIC_CHECK);

}
?>



