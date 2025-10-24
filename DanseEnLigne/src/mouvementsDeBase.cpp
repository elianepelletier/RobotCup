//va contenir toutes les fonctions qui représentent les mouvements de base (allumer la del rouge, avancer, tourner, ...)
//doit faire le header file pour avoir accès à ces fonctions-là dans les fichiers des chansons
//les fonctions qui ont besoin des données qui sont pris dans le main devraient avoir des arguments pour
//pouvoir y avoir accès

#include "mouvementsBase.h"
#include <Servo.h>
#include <Arduino.h>

Servo brasGauche;
Servo brasDroit;
int rougePin;
int jaunePin;
int vertPin;
int bleuPin;

void initBras() {
    brasGauche.attach(4);   // Pin du bras gauche (À DÉFINIR)
    brasDroit.attach(7);    // Pin du bras droit (À DÉFINIR)
}

void initDel(){
    pinMode(rougePin, 0); //CHANGER LES PINS DES DEL POUR LES BONS
    pinMode(jaunePin, 1);
    pinMode(vertPin, 2);
    pinMode(bleuPin, 3);
}

void bougerBrasGauche(int angle) {
    brasGauche.write(angle);
}

void bougerBrasDroit(int angle) {
    brasDroit.write(angle);
}