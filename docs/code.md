---
layout: default
nav_order: 6
title: Programmation
---

Programmation de la machine Puzzle Bot

# Gestion des actions de la machine principale (Programmation en C++)

## Plan du programme

Cette partie de la machine a été réalisée via platformio auquel a été ajouté la bibliothèque Accelstepper (gestion des moteurs pas à pas)

Le programme est divisé en 5 types de fichier : 
* Programme principale (main.c) pour l'execution de toutes les instructions
* Gestion des mouvements de la machine (zone de déplacement,zone de placement des pièces) via motion.h
* Gestion de la saisie et du placement ainsi que la rotation des pièces par l'intermédiaire de actionneur.h
* Réception et traitement des données reçues par la caméra en utilisant Déplacement_Caméra.h et Lecture.h
* Définition des pins via PuzzleBoardDef.h

**Plan du programme**

![Plan du programme](images/PlanProgrammePuzzleBot.png)

(programme disponible dans le dossier project sur le GitHub)

## Déplacements

La partie lié au mouvement de la base mobile, gérée par l'intermédiaire de motion.h, permet le placement de la machine dans l'espace lors de l'initialisation, de la récupération des pièces et de l'emboitement du puzzle

**Algorigramme pour le déplacement de la machine**

![Algorigramme Déplacement machine](images/Algo_Deplacements_PuzzleBot.png)



## Saisie et dépot des pièces de puzzle

Cette section du programme permet la gestion des actionneurs de la machine (Servomoteurs et Pompe) afin de pouvoir saisir, déposer ainsi que tourner les pièces si nécessaire

**Algorigramme pour la saisie et le dépôt des pièces sur le plateau**

![Algorigramme saisie et dépot pièce machine](images/Algo_Actionneurs_PuzzleBot.png)


# Traitement d'image et détection de marker avec OpenCV (programmation python)

## Calcul de la matrice de distorsion de la camera

Avant de pouvoir detecter les marker, il faut calibrer la caméra. Plusieur étapes sont nécessaire pour calculer la matrice de distorsion afin de calibrer la caméra.

Il faut tout d'abord prendre plusieurs photos d'un damier avec la caméra (10 à 15 photos). les photos doivent être prises sous plusieurs angles différents.
Une fois les photos prises, il faut lancer un programme qui calcul, à partir des images prises, la matrice de distorsion. cette matrice permet d'

## Détection de Marker AruCo (Programme principale)

### Concept et reflexion

Pour la partie vision du projet, le programme est réalisé en python avec plusieurs bibliothèque dont OpenCV avec la partie Aruco.
Au départ, le but était de récupérer la distance entre les marker. Le problème avec cette méthode est le fait que l'on ne récupère que le rayon où se situe la pièce, ce qui ne n'indique aucunement son emplacement exacte par rapport au point d'origine (le marker 5).
Par la suite nous sommes partis sur un système de coordonnées. En effe, le programme récupère (grâce à la caméra) les coordonnées ainsi que l'angle des marker attachés aux pièces de puzzle à partir d'un marker de repère.

Un autre problème rencontré lors de la conception fût avec le marker 5. Ce marker était cencé être placé sur la tête de la machine. Or cette partie étant trop haute, la caméra ne detecte plus le marker. La solution trouvé fut de placer le marker à l'opposé de la machine et de traité les calucul dans le programme. 

### Fonctionnement

Le programme commence par pendre une photo du plateau avec les pièces de puzzle. Un filtre noir et blanc est appliqué à la photo grâce à la bibliothèque OpenCV.

La biblioyhèque Aruco d'OpenCV nous permet d'utiliser les variables Tvec et Rvec de chaques marker.
La variable Tvec (translation vector) contient les coordonnées d'un marker par rapport à un autre. 
Concernant Rvec (rotation vector), elle contient l'angle de rotation d'un marker par rapport à un autre. Une fois les coordonnées en x et y ainsi que l'angle de rotation des marker obtenus, ces données sont ensuite ajoutées à une liste (sous cette forme: liste[x,y,angle marker 1, x,y,angle marker2, x,y,angle marker3, x,y,angle marker4]). La liste est ensuite envoyer sur un port com vers la carte Arduino. Le calcul des coordonnées ainsi que des angles prend en compte la matrice de distorsion afin d'avoir des mesures correctes.

Pour finir la liste est envoyer sur un port communication vers la carte arduino.

Ci-dessous un algorigramme simplifiant la compréhension du fonctionnement du programme
![Algorigramme Détection de Marker](images/Algo_Aruco_detect.png)
*Algorigramme du programme pour la detection de marker*