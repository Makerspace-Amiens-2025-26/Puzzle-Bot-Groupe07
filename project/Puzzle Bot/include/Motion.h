#include "AccelStepper.h"
#include <Actionneurs.h>

// Y MAX 17.5 (marge pour la base mobile) MAX MAX 18.2
// X MAX 12.3

#define MM_TO_STEP 100.75 // Facteur de conversion pour 1 cm (870 pour 1/16, 435 pour 1/8, 100.75 pour Plein Pas)
#define GRID_CONVERSION 2 // Facteur de conversion par point (distance entre 2 trous sur le plateau)
#define MICRO_STEP_REGULATOR 8 // Facteur de conversion microstepping

#define X_max 1337.625  // (21402 pour 1/16, 10701 pour 1/8 et 1337.625 pour Plein Pas)
#define Y_max -1903.125 // (-30450 pour 1/16, -15225 pour 1/8 et -1903.125 pour Plein Pas)

#define Longueur_piece 4.5 // en cm
#define Largeur_piece 4.5 // en cm

#define X_placement 668.75 // en pas
#define Y_placement -951.5 // en pas

int comptage_piece = 0;

AccelStepper X_Stepper(AccelStepper::DRIVER, Steppers::STEP1, Steppers::DIR1); 
AccelStepper Y_Stepper(AccelStepper::DRIVER, Steppers::STEP2, Steppers::DIR2);

void robot_dep_absolu(float X, float Y, int conversion);
void robot_dep(float X,float Y);
void Run_position();
void Run_Init();
void CheckandRun(float X_distance,float Y_distance);

// INIT
void InitMotors(int vitesse_accel_x, int vitesse_accel_y){
  X_Stepper.setMaxSpeed(vitesse_accel_x);
  X_Stepper.setAcceleration(vitesse_accel_x);
  Y_Stepper.setMaxSpeed(vitesse_accel_y);
  Y_Stepper.setAcceleration(vitesse_accel_y);
}
void Init_Pins(){
  // EN LOW (Motor activation)
  pinMode(Steppers::EN,OUTPUT);
  pinMode(Steppers::EN,HIGH);
  pinMode(Capteur::CapteurY,INPUT_PULLUP);
  pinMode(Capteur::CapteurX,INPUT_PULLUP);
}
void InitPos(){
  // Initialisation des 2 axes en simultanés
  if(digitalRead(Capteur::CapteurX) == HIGH && digitalRead(Capteur::CapteurY) == HIGH){
    robot_dep(-30,-30);
  }

  // Règle les coordonnées des moteurs pas à pas à 0
  X_Stepper.setCurrentPosition(0);
  Y_Stepper.setCurrentPosition(0);
}

// Main Functions

// déplacement des pièces vers la zone d'assemblage puis placement
void Placement_piece(){
  
  float X_placement_Reel = X_placement*MICRO_STEP_REGULATOR;
  float Y_placement_Reel = X_placement*MICRO_STEP_REGULATOR;

  float X_decalage = Longueur_piece*MICRO_STEP_REGULATOR*MM_TO_STEP;
  float Y_decalage = Largeur_piece*MICRO_STEP_REGULATOR*MM_TO_STEP;
  float X_placement_piece = 0, Y_placement_piece = 0;
  /*
  Représentation placement pièces
        =============
          8 | 7 | 6
          5 | 3 | 1
          4 | 2 | 0
        =============
  */
  switch(comptage_piece){
    case 0 : X_placement_piece = X_placement_Reel;
             Y_placement_piece = Y_placement_Reel;
        break;
    case 1 : X_placement_piece = X_placement_Reel;
             Y_placement_piece = Y_placement_Reel-Y_decalage;
        break;
    case 2 : X_placement_piece = X_placement_Reel+X_decalage;
             Y_placement_piece = Y_placement_Reel;
        break;
    case 3 : X_placement_piece = X_placement_Reel+X_decalage;
             Y_placement_piece = Y_placement_Reel-Y_decalage;
        break;
    case 4 : X_placement_piece = X_placement_Reel+2*X_decalage;
             Y_placement_piece = Y_placement_Reel;
        break;
    case 5 : X_placement_piece = X_placement_Reel+2*X_decalage;
             Y_placement_piece = Y_placement_Reel-Y_decalage;
        break;
    case 6 : X_placement_piece = X_placement_Reel;
             Y_placement_piece = Y_placement_Reel-2*Y_decalage;
        break;
    case 7 : X_placement_piece = X_placement_Reel+X_decalage;
             Y_placement_piece = Y_placement_Reel-2*Y_decalage;
        break;
    case 8 : X_placement_piece = X_placement_Reel+2*X_decalage;
             Y_placement_piece = Y_placement_Reel-2*Y_decalage;
        break;
  }
    robot_dep_absolu(X_placement_piece,Y_placement_piece,0);
    delay(500);
    Pompe(false,Default_angle_rotation); 
    
    
    comptage_piece++;
}
void robot_dep_absolu(float X, float Y, int conversion){ // Parameter in nb of grid (1 grid / 20 mm)
  
  // Conversions
    if(conversion == 2){
      // Conversion déplacement en nombre de trou sur le plateau vers nombre de pas
      X = X*GRID_CONVERSION*MICRO_STEP_REGULATOR*MM_TO_STEP;
      Y = -Y*GRID_CONVERSION*MICRO_STEP_REGULATOR*MM_TO_STEP;
    }
    else if(conversion == 1){
      // Conversion mètre vers nombre de pas
      X = X*MICRO_STEP_REGULATOR*MM_TO_STEP;
      Y = -Y*MICRO_STEP_REGULATOR*MM_TO_STEP;
    }
    // Vérifie que le déplacement est possible et enclenche le déplacement
    if(X >= 0 && Y <= 0){
      CheckandRun(X,Y);
    }
   /*X_Stepper.moveTo(X);
   Y_Stepper.moveTo(Y);
   Run_position();*/
}
// Déplacement relatif utilisé à l'initialisation car le point d'origine n'a pas été placé
void robot_dep(float X,float Y){ 
  // Conversion de nb de case en pas
  X = X*GRID_CONVERSION*MICRO_STEP_REGULATOR*MM_TO_STEP;
  Y = -Y*GRID_CONVERSION*MICRO_STEP_REGULATOR*MM_TO_STEP;  
  X_Stepper.move(X);
  Y_Stepper.move(Y);
  Run_Init();
}

// Lance les déplacement et vérifie si les mouvements sont finie sur l'axe X et l'axe Y
void Run_position(){
  bool XRun = true;
  bool YRun = true;
  // IF pour vérif que le mouvement est possible (ex : si on est dans la zone de déplacement)
  while (XRun || YRun){
    // mouvement en cours sur les 2 axes
    if(XRun && YRun){
      XRun = X_Stepper.run();
      YRun = Y_Stepper.run();
    }else if(XRun || YRun){ // mouvement en cours sur l'un des 2 axes
      if(XRun){ // mouvement en cours sur l'axe X
        XRun = X_Stepper.run();
      }else if(YRun){ // mouvement en cours sur l'axe Y
        YRun = Y_Stepper.run();
      }
    }
  }
}
// Run position pour Init (chacun des axes s'initialise tant que son capteur n'est pas enclenché)
void Run_Init(){
  // IF pour vérif que le mouvement est possible (ex : si on est dans la zone de déplacement)
  while (digitalRead(Capteur::CapteurX) == HIGH || digitalRead(Capteur::CapteurY) == HIGH){
    // mouvement en cours sur les 2 axes
    if(digitalRead(Capteur::CapteurX) == HIGH && digitalRead(Capteur::CapteurY) == HIGH){
      X_Stepper.run();
      Y_Stepper.run();
    }else if(digitalRead(Capteur::CapteurX) == HIGH || digitalRead(Capteur::CapteurY) == HIGH){ // mouvement en cours sur l'un des 2 axes
      if(digitalRead(Capteur::CapteurX) == HIGH){ // mouvement en cours sur l'axe X
        X_Stepper.run();
      }else if (digitalRead(Capteur::CapteurX) == LOW){
        X_Stepper.stop();
      }
      if(digitalRead(Capteur::CapteurY) == HIGH){ // mouvement en cours sur l'axe Y
        Y_Stepper.run();
      }else if (digitalRead(Capteur::CapteurY) == LOW){
        Y_Stepper.stop();
      }
    }
  }
}
// Fait en sorte que le déplacement ne sorte pas de la zone définie
void CheckandRun(float X_distance,float Y_distance){
  // Déplacement par coordonnées
  if(X_distance <= X_max*MICRO_STEP_REGULATOR && X_distance >= 0){ // regarde si : 0 =< X_distance =< X_max
    X_Stepper.moveTo(X_distance);
  }else if(X_distance > X_max*MICRO_STEP_REGULATOR){
    X_Stepper.moveTo(X_max*MICRO_STEP_REGULATOR);
  }else if(Y_distance < 0){
    X_Stepper.moveTo(0);
  }
  if(Y_distance >= Y_max*MICRO_STEP_REGULATOR && Y_distance <= 0){ // regarde si : Y_max =< Y_distance =< 0 (car Y_max négatif)
    Y_Stepper.moveTo(Y_distance);
  }else if(Y_distance < Y_max*MICRO_STEP_REGULATOR){
    Y_Stepper.moveTo(Y_max*MICRO_STEP_REGULATOR);
  }else if(Y_distance > 0){
    Y_Stepper.moveTo(0);
  }
  Run_position();
}