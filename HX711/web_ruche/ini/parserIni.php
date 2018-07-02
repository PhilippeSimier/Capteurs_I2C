<?php

// Analyse du fichier ini
$ini  = parse_ini_file("example1.ini", true);

echo "Host : " . $ini['SGBD']['Host'] . "<br />";
echo "User : " . $ini['SGBD']['user'] . "<br />";
echo "mdp  : " . $ini['SGBD']['mdp']  . "<br />";

$ini = parse_ini_file("fichier.ini", true);
var_dump($ini);
?>
