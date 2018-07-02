<?php

    require_once('ini.php');

    $array = array();
    $array['nb'] = 10;
    $array['pi'] = 3.1415;
    $array['val3'] = "Hello ; Bonjour";
    $array['maurice'] = array ('test' => 'valeur1', 'test2' => 'valeur2');
    $array['georges'] = array ('test' => 'valeur1', 'test2' => 'valeur2');

    $ini = new ini ("fichier.ini", "fichier ini pour les tests");
    $ini->ajouter_array($array);
    $ini->ecrire(true);

?>
