<?php

echo '<pre>';

 // Affiche le résultat de la commande "ls" et retourne
 // la dernière lignes dans $last_line. Stocke la valeur retournée
 // par la commande shell dans $retval.
 $last_line = system("/home/pi/Capteurs_I2C/HX711/tarage", $retval);

 // Affichage d'autres informations
 echo '</pre><hr />Valeur retournée : ' . $retval;
?>
