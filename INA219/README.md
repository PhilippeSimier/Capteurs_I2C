# INA 219

## Introduction

L’INA219 est un circuit permettant de mesurer  la puissance délivrée par un générateur comme  un panneau solaire ou une batterie. Il permet de mesurer une tension continue jusqu'à 26V et un courant continu jusqu’à 3.2A (avec un shunt de 0.1 ohm). 
Un amplificateur différentielle mesure la tension aux bornes de la résistance shunt de **0.1 ohm** (précison 1%). La différence d'entrée maximum de l'amplificateur différentielle est de ±320mV, cela implique que l'on peut donc mesurer un courant maximum de ±3.2 Ampères au maximum. la sortie de l'amplificateur est connectée à un convertisseur Analogique Digital  12 bits (ADC 12 bits), La résolution sur la gamme ±3.2A est de 0.8mA.

la conversion se fait sur 12 bits (2 exp 12 = 4096)   	L'ADC peut mesurer des tensions comprises entre ± 40mV (± pour la mesure du courant bidirectionnel).
le PGA est un diviseur de tension programmable par 1, 2, 4, or 8.   	Cela donne à l'INA219 une plage effective de ± 40 mV, ± 80 mV, ± 160mV, ou ± 320mV respectivement.

![raccordement](/INA219/images/Schema_bloc.PNG)


L’INA219 vient se placer en série sur le pole positif du circuit entre la source d’alimentation et le consommateur d’énergie.
Le bus I2C permet de transferer les valeures mesurées. (tension, courant puissance)

![raccordement](/INA219/images/schema_INA219.png)


 
 
## l’adresse I2C

Deux jumper A0 et A1 permettent de choisir une adresse sur le bus i2C. Suivant la position des jumpers, 4 adresses I2C  sont possibles:

**0x40** Offset = binary 00000 (par défaut)
**0x41** Offset = binary 00001 (pont A0)
**0x44** Offset = binary 00100 (pont A1)
**0x45** Offset = binary 00101 (pont A0 et A1)

![INA219](/INA219/images/INA219.png)



## Changelog

 **04/08/2018 :** Ajout du README . 
 **10/09/2018 :** Ajout du  script shell RaspbianOSsetup.sh
 
> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER Lycée Touchard Le Mans**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#



