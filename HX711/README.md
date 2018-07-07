# Amplificateur convertisseur HX711

# Description


le module HX711 est un amplificateur pour capteurs de force à pont de Wheatstone associé à un convertisseur analogique-numérique. Les données  sont transmises sur un bus SPI de type propriétaire qui utilise une ligne d'horloge (SCK) et de données (DOUT).  Le nombre d'impulsions d'horloge permet de configurer le gain de l'amplificateur. 


 - 25 impulsions gain = 128 Canal = A (tension d'entrée différentielle +- 20mV)
 - 26 impulsions gain =  32 Canal = B (+- 80mV)
 - 27 impulsions gain =  64 Canal = A (+- 40mV)

 
le driver **SPI** (Serial Peripheral Interface) du noyau linux permet seulement de créer des impulsions d'horloge par multiple de 8, pour contourner cette limitation l'idée originale consiste à utiliser la ligne de données MOSI du bus SPI pour générer les 25 impulsions d'horloge. En écrivant la valeur **10101010** (0xaa en hexadécimal), nous obtenons 4 impulsions. Il suffit donc d'envoyer 6 fois cette valeur pour obtenir 24 impulsions, puis d'écrire la valeur 0x80 pour obtenir la 25 éme impulsions.
 
# Câblage
La plupart des cellules de pesage disposent de quatre « jauges de contrainte » pour mesurer la force exercée par l'objet pesé.
La tendance actuelle est aux jauges à trame, dites aussi jauges imprimées. Elles sont obtenues à partir d'une lame, formée d'une feuille mince (quelques micromètres) d'un alliage métallique et d'un support isolant (résine synthétique). À mesure que le flexible ploie, les jauges de contrainte se déforment, ce qui modifie le courant électrique qui les traverse. Cette modification est proportionnelle au poids de l'objet pesé. 


 ![schema cablage HX711](/HX711/images/schema-HX711.png)
Réaliser le câblage suivant le schéma ci-dessus 
# Installation
**Prérequis** : Cloner le dépôt
```
    pi@raspberry:~ $ git clone https://github.com/PhilippeSimier/Capteurs_I2C.git
    pi@raspberry:~ $ cd Capteurs_I2C/HX711
```
**Compilation & installation** : des programmes
```
    root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ make all
    root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ make install
    root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ make clean
```
**Configuration et Etalonage** de la balance

L'étalonnage  est  l'établissement de la relation entre une valeur connue et la valeur mesurée dans des conditions de mesure précises. En d'autres termes, l'étalonnage consiste à prendre un poids connu (p. ex. 1 kg) et d'établir la relation pour que la valeur affichée à l'écran corresponde à la valeur connue.

Ce que nous appelons « **poids** » est la force gravitationnelle de la terre exercée sur la force gravitationnelle de l'objet pesé. Plus un objet est éloigné du centre de la terre, plus le poids mesuré est faible. Par conséquent, un objet situé au niveau de la mer est légèrement plus lourd qu'à 1 000 mètres d'altitude – même si sa **masse**, elle, reste identique. 
Deuxièmement, l'accélération centrifuge provoquée par la rotation terrestre compense de manière subtile la force de la gravité. Cette accélération est à son maximum au niveau de l'équateur et diminue à mesure que l'on se rapproche des pôles. Donc, plus un objet s'éloigne de l'équateur, plus il devient lourd.
Le programme **etalonnage** permet de déterminer les paramètres de cette relation et de les enregistrer dans le fichier **configuration.ini**. 
```
root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ ./etalonnage
Quelle est l'unité de mesure ? (g kg lb)
g
Quelle est la précision d'affichage : 1 ou 2 chiffres après la virgule
1
Donnez le gain souhaité : 128 ou 64 ?
128
```
**Tarage** de la balance

Le terme « **tare** » provient d'un ancien mot arabe signifiant « **déduction ou rejet** » et désigne le contenant renfermant l'article dont vous voulez connaître le poids. le programme **tarage** permet de réinitialiser l'affichage lorsque le contenant vide est posé sur le plateau de pesée.
```
root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ ./tarage
root@raspberry:~/home/pi/Capteurs_I2C/HX711 $ ./main
```
Le programme **main** permet d'effectuer la pesé  en continu.



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



