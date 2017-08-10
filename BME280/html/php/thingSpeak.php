<?php
/* 
 * Envoie les mesures à thingSpeak
 */
 
	$curl = curl_init();
	curl_setopt($curl, CURLOPT_URL, 'http://philippes.ddns.net');
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);  //Cette option permet d'indiquer que nous voulons recevoir le résultat du transfert au lieu de l'afficher.
	curl_setopt($curl, CURLOPT_COOKIESESSION, true);   //Cette option permet de dire à cURL de démarrer un nouveau cookie session.
	$return = curl_exec($curl);
	curl_close($curl);
	
	echo $return;
 
 
 ?>