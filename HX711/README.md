# Amplificateur convertisseur HX711

# Description
le module HX711 est un amplificateur pour capteurs de force à pont de Wheatstone associé à un convertisseur analogique-numérique. Les données  sont transmises sur un bus SPI de type propriétaire qui utilise une ligne d'horloge (SCK) et de données (DOUT).  Le nombre d'impulsions d'horloge permet de configurer le gain de l'amplificateur. 


 - 25 impulsions gain = 128 Canal = A (tension d'entrée différentielle +- 20mV)
 - 26 impulsions gain =  32 Canal = B (+- 80mV)
 - 27 impulsions gain =  64 Canal = A (+- 40mV)

 
le driver **SPI** (Serial Peripheral Interface) du noyau linux permet seulement de créer des impulsions d'horloge par multiple de 8, pour contourner cette limitation l'idée originale consiste à utiliser la ligne de données MOSI du bus SPI pour générer les 25 impulsions d'horloge. En écrivant la valeur **10101010** (0xaa en hexadécimal), nous obtenons 4 impulsions. Il suffit donc d'envoyer 6 fois cette valeur pour obtenir 24 impulsions, puis d'écrire la valeur 0x80 pour obtenir la 25 éme impulsions.
 
# Câblage 
 ![schema cablage HX711](/HX711/images/schema-HX711.png)


# Changelog

 **14/04/2018 :** Ajout du README . 
 **10/06/2018 :** Ajout programme d'étalonnage
> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER Lycée Touchard Le Mans**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


