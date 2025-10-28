//va contenir toutes les fonctions qui représentent les mouvements de base (allumer la del rouge, avancer, tourner, ...)
//doit faire le header file pour avoir accès à ces fonctions-là dans les fichiers des chansons
//les fonctions qui ont besoin des données qui sont pris dans le main devraient avoir des arguments pour
//pouvoir y avoir accès

#include "mouvementsBase.h"
// #include <Servo.h>
#include <Arduino.h>
#include <LibRobus.h>
#include <stdlib.h>


// Servo brasGauche;
// Servo brasDroite;
int rougePin = 40; 
int jaunePin = 41;
int vertPin = 42;
int bleuPin = 43;

int angleBrasBas = 0;
int angleBrasHaut = 180;
int angleBrasDevant = 90;

void initBras() {
    //brasGauche.attach(4);   // Pin du bras gauche (À DÉFINIR)
    //brasDroit.attach(7);    // Pin du bras droit (À DÉFINIR)
    SERVO_Enable(RIGHT);
    SERVO_Enable(LEFT);
}

void initDel(){
    pinMode(rougePin, OUTPUT); 
    pinMode(jaunePin, OUTPUT);
    pinMode(vertPin, OUTPUT);
    pinMode(bleuPin, OUTPUT);
}

void bougerBrasGauche(int angle) {
    //brasGauche.write(angle);
    SERVO_SetAngle(LEFT, angle);
}

void bougerBrasDroit(int angle) {
    // brasDroit.write(angle);
    SERVO_SetAngle(RIGHT, angle);
}

void allumeDELRouge() {
    digitalWrite(rougePin, HIGH);
}

void fermeDELRouge() {
    digitalWrite(rougePin, LOW);
}

void allumeDELJaune() {
    digitalWrite(jaunePin, HIGH);
}

void fermeDELJaune() {
    digitalWrite(jaunePin, LOW);
}

void allumeDELVert() {
    digitalWrite(vertPin, HIGH);
}

void fermeDELVert() {
    digitalWrite(vertPin, LOW);
}

void allumeDELBleu() {
    digitalWrite(bleuPin, HIGH);
}

void fermeDELBleu() {
    digitalWrite(bleuPin, LOW);
}

void allumeFermeAvecDelay(int d, int pin){
    digitalWrite(pin, HIGH);
    delay(d);
    digitalWrite(pin, LOW);
}

void allumeDELaleatoire(int d){
    int randomPin = rand() % (bleuPin - rougePin + 1) + rougePin;
    allumeFermeAvecDelay(d, randomPin);
}