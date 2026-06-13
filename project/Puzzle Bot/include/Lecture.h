#include <Arduino.h>

#define nb_pieces 4

// [ X , Y , rotation]
float Coordonnees_deplacement[3*nb_pieces];


String input = "";

void parseData(String data);

void Coordonnees_Tags(){
    /*Récupération des coordonnées des tags sur le port série*/
    
    while (Serial.available()){
        char c = Serial.read();
        input.concat(c);
        /*if (c == '\n') {
            parseData(input);
            input = "";
        } else {
            input += c;
        }*/
    }
    parseData(input);
}

void parseData(String data) {
    /* 
       Stockage des valeurs reçu sur le port série dans le tableau
       Sont récupéré pour chaque pièces les coordonnées (x,y) et l'angle de rotation à effectuer
       Enregistré dans le format suivant : [x,y,rotation] (ces 3 éléments sont stockés sont stockés les uns à la suite des autres)
       exemple : [x1, y1, rotation pièce 1, x2, y2, rotation pièce 2,..., rotation pièce n]
    */

    int count = 0;

    int start = 0;
    while (true) {
        int comma = data.indexOf(',', start);

        if (comma == -1) {
            Coordonnees_deplacement[count++] = data.substring(start).toInt();
            break;
        }

        Coordonnees_deplacement[count++] = data.substring(start, comma).toInt();
        start = comma + 1;

        if (count >= nb_pieces*2) break;
    }

    // debug
    for (int i = 0; i < count; i++) {
        Serial.println(Coordonnees_deplacement[i]);
    }
}