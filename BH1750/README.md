Capteur d'éclairement BH1750
==================================

##  Mesure des quantités de lumière
On distingue deux domaines : Il s'agit juste de quelques définitions.

-   La **radiométrie** (ou photométrie énergétique) : pour exprimer l'énergie rayonnée indépendamment de notre physiologie.
-   La **photométrie** (ou photométrie visuelle) : pour exprimer l'énergie rayonnée telle qu'elle est perçue par l'œil humain dont la sensibilité est limitée à un petit domaine spectral.

### La Photométrie

L’éclairement lumineux se différencie de l’éclairement énergétique par l’application d’une pondération par longueurs d’onde qui correspond à la sensibilité de la vision humaine. Les appareils de mesure doivent avoir une sensibilité spectrale similaire.
Les grandeurs photométriques sont adaptées à la sensibilité spectrale de l'œil humain. Pour la définition des unités photométriques, on considère la sensibilité de l'œil pendant la vision diurne.  Pour les concevoir, il faut considérer un "œil moyen". Celui-ci est défini par la Commission Internationale de l'Eclairage (CIE). La courbe de la figure 2 est tracée à partir des valeurs indiquées par la CIE, elle montre l'efficacité de l'œil humain pour les différentes longueurs d'onde de la lumière visible. 
L’éclairement lumineux est la grandeur définie par la photométrie

l’éclairement lumineux correspond à un **flux lumineux reçu** par unité de surface. Son unité dans le système international d’unités est le **lux** :  
1 lux (lx) correspond à un flux lumineux de 1 lumen (lm) couvrant uniformément 1 mètre carré (m^2) : 1 lx = 1 lm /m^2.

![répartition spectrale](/lumi2.jpg)

*Remarque :* Compte tenu des caractéristiques de la vision photopique chez les êtres humains, il n’y a pas de facteur de conversion unique entre le lux (lumen par mètre carré) et le watt par mètre carré, mais des facteurs de conversion différents pour chaque longueur d’onde. Par exemple, pour une couleur vert-jaune, un éclairement énergétique de 1 W/m-2 correspond à 683 lux, tandis que pour du rouge ou du bleu, il s’agit de moins de 50 lux. Il est donc impossible de faire une conversion lux vers énergie sans connaître la répartition spectrale de la lumière.

Le lux sert de cadre normatif pour définir, dans les législations française et européenne, les niveaux minimums requis pour l’éclairage public et l’éclairage des lieux de travail.

# BH1750

Le circuit intégré BH1750 est un capteur numérique de la lumière ambiante avec une interface I2C. Il est capable de détecter une large gamme (0-65535 lx) en haute résolution (0.5 lx) .
