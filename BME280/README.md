# Le Capteur BME280

# Description
Le BME280 est un capteur environnemental qui permet de mesurer la : 

 - **température** (de -40°C à 85°C avec une précision de +/- 1°C) ;
 - **la pression**  ( de 300hPa à 1100 hPa avec une précision de +/- 1hPa) ;
 - **humidité relative** ( de 0% à 100%).

Les valeurs numériques sont transférées sur le bus **I2C** ou  le bus **SPI**. C'est la broche CSB qui permet de passer du mode SPI au mode I2C. Par défaut, CSB=1 c'est donc le mode I2C qui est sélectionné.  Par contre, si au démarrage CSB=0 , alors ce sera  le mode SPI qui sera utilisé pour le transfert.

En fonction du niveau de tension appliquée sur la broche SDO,  l'adresse sur le bus  I2C est **0x77** ou **0x76** .  SD0=0  configure l’adresse 0x76, tandis que  SD0=1 configure l’adresse  0x77.
 
# Diagramme de classe
![cablage BME280](/BME280/images/bme280_Class_diagram.png)


# Câblage 
Avec les branchements suivants, SD0=1 donc l’adresse du capteur sur le bus I2C sera 0x77
 ![cablage BME280](/BME280/images/schema-BME280.png)

# Installation

#### Activer le module **i2c** 

via l'utilitaire **raspi-config**

```bash
pi@raspberry:~ $ sudo raspi-config
```
sélectionner  l'option 5

> 5 Interfacing Options            Configure connections to peripher

puis sélectionner P5
>P5 I2C                           Enable/Disable automatic loading
> Would you like the ARM I2C interface to be enabled?

répondre OUI
le message suivant s'affiche : 
> The ARM I2C interface is enabled**

 
#### Installer les outils i2c 

```bash
pi@raspberry:~ $ sudo apt-get install i2c-tools
```
#### Vérifier la présence du capteur

```bash
pi@raspberry:~ $ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- 77
```
la valeur de l'adresse 77 ou 76 doit s'afficher si le câblage est correct.

#### Cloner le dépot

```bash
pi@raspberry:~ $ git clone https://github.com/PhilippeSimier/Capteurs_I2C.git

pi@raspberry:~ $ cd Capteurs_I2C/BME280/
```
#### Compiler puis exécuter le programme principal

```bash
pi@raspberry:~/Capteurs_I2C/BME280 $ g++ main.cpp i2c.cpp  bme280.cpp -o main

pi@pi3PSR:~/Capteurs_I2C/BME280 $ ./main
```

# Changelog

 **08/12/2019 : ** Suite à la découverte d'un bug lors de la mesure de température négative,  refonte complète de la classe Bme280 . Version 2.0 
 **21/04/2018 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


