#include <Motion.h>
#include <Lecture.h>

// CODE GESTION DEPLACEMENT AVEC CAMERA
// Reconnaissance de tags en python et récupération des données par le port série

void Coordonnees_Tags();

void Sequence_Deplacement_Tags(){
    
    // Récupération des coordonnées des tags via port Série
    Coordonnees_Tags();

    // Boucle afin d'effectuer le placement de toutes les pièces de puzzle
    for(int i = 0; i < nb_pieces; i++)
    {
        //Séquence de déplacement avec détection (déplacement | récupération piece | dépot piece)

        // Envoie des coordonnées de la pièce
        robot_dep_absolu(Coordonnees_deplacement[3*i],Coordonnees_deplacement[3*i+1],0);
        // accroche de la pièce et rotation avec l'angle stocké dans le tableau
        Pompe(true,Coordonnees_deplacement[3*i+2]);
        // placement de la pièce à l'emplacement correspondant
        Placement_piece();
    }
    
}
void Init_coordonnees(){
    // Initialisation des coordonnées cibles à 0 au démarrage

    for(int i;i< 2*nb_pieces;i++){
      Coordonnees_deplacement[i] = 0;  
    }
}