<?php
/* 
 * Réponse aux requétes get pour obtenir les données
 * sur les dernières 24heures
 * ou à partir d'une date.
 */


require_once 'fonctions.inc.php';
header('Content-type: application/json');

if (!empty($_GET['to'])){
	
	if($_GET['to'] == "troisJours"){
		$to = new DateTime();
		$to->sub(new DateInterval('P3D'));
		getHumidite($to->format('Y-m-d H:00:00P'));
	}
	if($_GET['to'] == "uneSemaine"){
		$to = new DateTime();
		$to->sub(new DateInterval('P7D'));
		getHumidite($to->format('Y-m-d H:00:00P'));
	}
	
}
else{
	// si la variable $_GET['to'] est vide alors on renvoie les données du dernier jour
	// On prend la date et heure actuelles du jour 
	$to = new DateTime();
	
	// on retire 24 heures avec la methode sub de DateTime
	$to->sub(new DateInterval('PT24H'));
	// on tronque $to à l'heure entière
	getHumidite($to->format('Y-m-d H:00:00P'));

}	
	
?>