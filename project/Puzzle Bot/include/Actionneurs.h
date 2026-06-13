#include <Servo.h>
// PIN DEF OF ALL OBJECT
#include <PuzzleBoardDef.h>

#define Default_angle_rotation 0
#define Default_angle_hauteur 100

#define angle_hauteur_bas 60
#define angle_hauteur_haut 120

//int Val_servo = 0;

Servo Servo_rotation;
Servo Servo_Hauteur;

void Init_actionneur();
void Pompe(bool Pompage, float angle);
void rotation(float angle, float hauteur);

void Init_actionneurs(){
  // PIN LINKING
  pinMode(Actionneur::Pompe,OUTPUT);
  pinMode(Actionneur::Pompe1B,OUTPUT);
  pinMode(Actionneur::Vanne,OUTPUT);
  //pinMode(A0,OUTPUT);
  Servo_rotation.attach(Actionneur::Servo_rot);
  Servo_Hauteur.attach(Actionneur::Servo_hauteur);
  // Mise aux valeurs par défaut des actionneurs
  Servo_rotation.write(Default_angle_rotation);
  Servo_Hauteur.write(angle_hauteur_haut); // Servo HIGH position
  digitalWrite(Actionneur::Pompe1B,LOW);
  digitalWrite(Actionneur::Pompe,LOW);
  digitalWrite(Actionneur::Vanne,HIGH);
  //digitalWrite(A0,HIGH);
  delay(500);
  digitalWrite(Actionneur::Vanne,LOW);
}
/*Gestion accroche des pièces */
void Pompe(bool Pompage, float angle){
  
  switch (Pompage)
  {
  case true:
    //Allumage de la pompe et accroche de la pièce

    // Remise à zéro de la rotation et descente
    //rotation(Default_angle_rotation,angle_hauteur_bas);
    //digitalWrite(Actionneur::Vanne, LOW);
    digitalWrite(Actionneur::Pompe, HIGH);
    delay(2000);
    //digitalWrite(Actionneur::Pompe1B, HIGH);
    // Rotation et mise à l'état haut de la pompe
    rotation(angle,angle_hauteur_haut);
    break;
  case false:
    //Arrêt de la pompe et dépot de la pièce
    rotation(angle,angle_hauteur_bas);
    digitalWrite(Actionneur::Pompe, LOW);
    delay(2000);
    //digitalWrite(Actionneur::Pompe1B, LOW);
    //digitalWrite(Actionneur::Vanne, HIGH);
    //delay(500);
    //digitalWrite(Actionneur::Vanne, LOW);
    // Remise à zéro de la saisie 
    rotation(Default_angle_rotation,angle_hauteur_haut);
    break;
  }
}
/*Gestion rotation des pièces et hauteur de l'actionneur sur la base mobile*/
void rotation(float angle, float hauteur){
  Servo_rotation.write(angle);
  Servo_Hauteur.write(hauteur);
}