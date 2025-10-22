//va contenir toutes les fonctions qui représentent les mouvements de base (allumer la del rouge, avancer, tourner, ...)
//doit faire le header file pour avoir accès à ces fonctions-là dans les fichiers des chansons
//les fonctions qui ont besoin des données qui sont pris dans le main devraient avoir des arguments pour
//pouvoir y avoir accès

#include "mouvementsBase.h"
#include <Servo.h>

Servo brasGauche;
Servo brasDroit;

void initBras() {
    brasGauche.attach(int);   // Pin du bras gauche (À DÉFINIR)
    brasDroit.attach(int);    // Pin du bras droit (À DÉFINIR)
}

void bougerBrasGauche(int angle) {
    brasGauche.write(angle);
}

void bougerBrasDroit(int angle) {
    brasDroit.write(angle);
}