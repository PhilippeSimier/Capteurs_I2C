<?php
/* 
 * Réponse aux requétes get pour obtenir les données
 * sur une période donnée
 * ou à partir d'une date.
 */
 
require_once("config.inc.php");

function connexionBD() {
    try {

        $bdd = new PDO('mysql:host=' . SERVEURBD . ';dbname=' . NOMDELABASE, LOGIN, MOTDEPASSE);
    } catch (Exception $ex) {
        die('<br />Pb connexion serveur BD : ' . $ex->getMessage());
    }
    return $bdd;
}

function getValeur($to, $from, $grandeur) {
    $bdd = connexionBD();
	
    $requete = $bdd->prepare("SELECT * FROM `dataBme280` WHERE date BETWEEN :to AND :from ORDER BY `id` ASC;");
    $requete->bindParam(":to", $to);
	$requete->bindParam(":from", $from);
    $requete->execute() or die(print_r($requete->errorInfo()));

    $data = array();   
    while ($ligne = $requete->fetch()) {
        array_push($data, $ligne[$grandeur]);
		if(empty($debut)){     // on mémorise la première date retournée
			$debut = $ligne['date'];
		}	
    }
	$sql = "SELECT avg(".$grandeur.") as average, min(".$grandeur.") as mini, max(".$grandeur.") as maxi FROM `dataBme280` WHERE date BETWEEN :to AND :from";
	$requete = $bdd->prepare($sql);
    $requete->bindParam(":to", $to);
	$requete->bindParam(":from", $from);
    $requete->execute() or die(print_r($requete->errorInfo()));
	$ligne = $requete->fetch();
	
	$options['average'] =  round($ligne['average'], 1);
	$options['maxi']    =  round($ligne['maxi'], 1);
	$options['mini']    =  round($ligne['mini'], 1);
	

//	$to1 = substr($to, 0, -6)."+0000";
    $to1 = $debut."+0000";
	$options['to'] = strtr($to1, " ", "T");  //la date au format ISO 8601 (remplace l'espace par un T)

	$from = new DateTime($from);
	$from->sub(new DateInterval('PT24H'));
	$debut = new DateTime($debut);
	$options['subtitle'] = "du ".$debut->format('d/m/Y')." au ".$from->format('d/m/Y');

	$options['title'] = "BME280 sur ".$_SERVER["SERVER_NAME"];
	
	
	
 	if ($grandeur == 'temperature') {$serie['name'] = "Température"; $serie['unite'] = " °C";}
    if ($grandeur == 'pression') {   $serie['name'] = "Pression"; $serie['unite'] = " hPa";}
    if ($grandeur == 'humidite') {   $serie['name'] = "Humidité"; $serie['unite'] = " %";}
    
	$serie['type']  = "spline";		
	$serie['data']  = $data;
	
	$series = array();
	array_push($series, $serie);
	$options[series] = $series;
	
	$requete->closeCursor();
    echo json_encode($options, JSON_NUMERIC_CHECK);

}
header('Content-type: application/json');

if (!empty($_GET['to']) || !empty($_GET['from'])){
	$to = new DateTime($_GET['to']);
	$from = new DateTime($_GET['from']);
	$from->add(new DateInterval('PT24H'));
	if (empty($_GET['grandeur'])){
		$_GET['grandeur']= "temperature";
	}
    getValeur($to->format('Y-m-d H:00:00P'), $from->format('Y-m-d H:00:00P'), $_GET['grandeur']);
		
}
else{
	// si la variable $_GET['to'] est vide alors on renvoie les données du dernier jour
	// On prend la date et heure actuelles du jour 
	$de = new DateTime();
	$a = new DateTime();
	// on retire 24 heures avec la methode sub de DateTime
	$de->sub(new DateInterval('PT24H'));
	// on tronque $to à l'heure entière
	if (empty($_GET['grandeur'])){
		$_GET['grandeur']= "temperature";
	}
	getValeur($de->format('Y-m-d H:00:00P'), $a->format('Y-m-d H:00:00P'), $_GET['grandeur']);

}	


?>