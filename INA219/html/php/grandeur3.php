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

    $requete = $bdd->prepare("SELECT * FROM `batterie` WHERE date BETWEEN :to AND :from ORDER BY `id` ASC;");
    $requete->bindParam(":to", $to);
    $requete->bindParam(":from", $from);
    $requete->execute() or die(print_r($requete->errorInfo()));

    $data1 = array();
    $data2 = array();
    $data3 = array();
    $data4 = array();

    while ($ligne = $requete->fetch()) {
	    
        array_push($data1, $ligne['courantBus']);
		
		array_push($data2, $ligne['tensionBus']);
		
		array_push($data3, $ligne['puissanceBus']);
		
		array_push($data4, $ligne['energie']);

		if(empty($debut)){     // on mémorise la première date retournée
			$debut = $ligne['date'];
		}
    }
	$sql = "SELECT avg(".$grandeur.") as average, min(".$grandeur.") as mini, max(".$grandeur.") as maxi FROM `batterie` WHERE date BETWEEN :to AND :from";
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

	$options['title'] = "INA219 sur ".$_SERVER["SERVER_NAME"];

	$series = array();
	$tooltip[valueSuffix] = " A";
 	$serie['name'] = "Courant";
	$serie['type']  = "spline";
	$serie['data']  = $data1;
	$serie['tooltip'] = $tooltip;
	array_push($series, $serie);

 	$tooltip[valueSuffix] = " V";
	$serie['name'] = "Tension";
	$serie['type']  = "spline";
        $serie['yAxis'] = 1;
	$serie['data']  = $data2;
	$serie['tooltip'] = $tooltip;
	array_push($series, $serie);

 	$tooltip[valueSuffix] = " W";
	$serie['name'] = "Puissance";
	$serie['type']  = "spline";
    	$serie['yAxis'] = 2;
	$serie['data']  = $data3;
	$serie['tooltip'] = $tooltip;
	array_push($series, $serie);

 	$tooltip[valueSuffix] = " mWh";
	$serie['name'] = "Energie";
	$serie['type']  = "spline";
        $serie['yAxis'] = 0;
	$serie['data']  = $data4;
	$serie['tooltip'] = $tooltip;
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
		$_GET['grandeur']= "tensionBus";
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
		$_GET['grandeur']= "tensionBus";
	}
	getValeur($de->format('Y-m-d H:00:00P'), $a->format('Y-m-d H:00:00P'), $_GET['grandeur']);

}


?>
