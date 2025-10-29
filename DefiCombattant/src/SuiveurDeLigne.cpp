#include <Arduino.h>
#include <LibRobus.h>
#include <libRobot.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Capteur.h>
#include "SuiveurDeLigne.h"

int Etat;

void Suislaligne() {
    float vitesse = 0.5;
    float pajust = 0.8;
    float gajust =0.5;
    if (Etat == 1) {//continue tout droit
        MOTOR_SetSpeed(MOTEUR_GAUCHE, vitesse);
        MOTOR_SetSpeed(MOTEUR_DROITE, vitesse);
    }
    if (Etat == 4) {//petit ajustement vers la gauche
        MOTOR_SetSpeed(MOTEUR_GAUCHE, pajust*vitesse);
        MOTOR_SetSpeed(MOTEUR_DROITE, vitesse);
    }
    if (Etat == 5) {//petit ajustement vers la droite
        MOTOR_SetSpeed(MOTEUR_GAUCHE, vitesse);
        MOTOR_SetSpeed(MOTEUR_DROITE, pajust*vitesse);
    }
    if (Etat == 2) {//grand ajustement vers la gauche
        MOTOR_SetSpeed(MOTEUR_GAUCHE, gajust*vitesse);
        MOTOR_SetSpeed(MOTEUR_DROITE, vitesse);
    }
    if (Etat == 3) {//petit ajustement vers la droite
        MOTOR_SetSpeed(MOTEUR_GAUCHE, vitesse);
        MOTOR_SetSpeed(MOTEUR_DROITE, gajust*vitesse);
    }
    else {
        MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
        MOTOR_SetSpeed(MOTEUR_DROITE, 0);
    }
}

void Loop(){
    Etat = suiveurligne();
    Suislaligne();
}
