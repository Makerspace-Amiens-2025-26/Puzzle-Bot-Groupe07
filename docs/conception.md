---
layout: default
nav_order: 5
title: Conception
---

# Conception et assemblage

Cette section décrit les étapes du processus de fabrication : le prototypage, la conception et l'assemblage.

## Conception

Pour la conception, la réalisation de la modélisation 3D a été faite en suivant un principe d'axe. Chaque axe a été modélisé sur un même fichier de conception pour assurer le bon fonctionnement des pièces entre elles. De plus, afin de simplifier le changement de certaines pièces et d'accélérer l'impressions 3D des nouveaux prototypes beaucoup de pièces sont interchangeables et indépendantes les unes des autres.

### Axe X

Le déplacement selon cet axe utilise un principe simple de poulie-courroie. On trouve un moteur pas à pas d'un coté de l'axe et une poulie libre de l'autre coté. Le wagon se déplace avec la courroie grace à une pièce de maitien de courroie. Pour éviter que le système se désaxe, le principe est utilisé des 2 cotés de la machine ce qui nécessite de créer certaines pièces en double ou en symétrie.
De plus, cet axe est celui du "bas" donc il supporte toutes les autres pièces, il faut que les pièces qui le compose soit résitantes. 

Sur cet axe on  trouve 5 pièces dont 3 possèdent une version en symétrie ou légerement différente :
* Wagon bas (2 versions symétriques)
* Maintien de courroie axe X (2 versions selon le coté par lequel est maintenue la courroie)
* Blocage courroie axe Y (2 versions dont une possédant une extension permettant de positionner un capteur de fin de course)
* Entretoise 4mm
* Entretoise 10mm

*Modélisation Axe X*

![Modélisation Axe X](images/Wagon_axe_X.png)

### Axe Y

Pour changer du principe de déplacement de l'axe X, sur cet axe le moteur bouge avec le wagon principal. Il coulisse le long de la courrroie qui elle est imobile.

Sur cet axe on  trouve 4 pièces dont 2 étant identiques à celles de l'axe X:
* Wagon haut
* Support de poulies
* Entretoise 4mm
* Entretoise 10mm

*Modélisation Axe Y*

![Modélisation Axe Y](images/Wagon_axe_Y.png)

### Axe Z

Contrairement aux 2 autres axes de translation celui n'utilise pas de moteur pas à pas mais un simple servo-moteur ayant 2 positions, une haute et une basse. CE changement permet de diminuer le nombre de pièces nécessaire à effectuer le mouvement.

On trouve 3 pièces pour cet axe dont 2 sont notamment utilisé pour maintenir la pompe du système :
* Support pompe
* Blocage pompe + guidage
* Axe Z principal

*Modélisation Axe Z*

![Modélisation Axe Z](images/Wagon_axe_Z.png)

### Axe R

Ce dernier axe est un axe de rotation de la ventouse de saisie des pièces de puzzle. Ce mouvement est comme pour le mouvement sur X effectué grâce à un servo-moteur.

Seulement 2 pièces sont nécessaires à cette rotation :
* Système de rotation
* Plaque de blocage

*Modélisation Axe R*

![Modélisation Axe R](images/Wagon_axe_R.png)

## Assemblage final

Un assemblage final du projet permet de vérifier le bon fonctionnement des axes avant de commencer l'impression des pièces et le prototypage.

*Assemblage final*

![Assemblage final](images/Assemblage.png)