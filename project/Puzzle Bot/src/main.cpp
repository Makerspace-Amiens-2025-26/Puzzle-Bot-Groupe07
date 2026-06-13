#include <Deplacement_Camera.h>

void setup() {
  // Initialisation des entrées et sorties utilisées, des moteurs ainsi que les actionneurs
  Init_Pins();
  InitMotors(4000,4000);
  Init_actionneurs();

  // Mise à la position 0 de la machine
  InitPos();
  delay(500);

  // Déplacement par vision
  
  // initialisation du tableau de coordonnées à 0 et initialisation du port série
  Init_coordonnees();
  Serial.begin(9600);
  // récupération des coordonnées et exécution des séquences
  Sequence_Deplacement_Tags();
}
void loop() {
}