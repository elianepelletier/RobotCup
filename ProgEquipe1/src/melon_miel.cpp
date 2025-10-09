#include <Arduino.h>
#include <librobus.h>

#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1
#define QUATRE_VINGT_DIX 610
#define CINQUANTE_CENTIMETRE 2695
#define CENT_QUATRE_VINGT_DIX 1220

const float distanceParPulse = 0.000147262;  
float Vt0 = 0.3;   
float Vt1 = 0.3;   
const float KpTristan = 1.2;                 
const unsigned long interval = 50;     


static unsigned long lastTime = 0;
static int32_t pulse0, pulse1;
static float Vp0, Vp1;
static float Erreur0, Erreur1;
static float commande0, commande1;


void arret();



void droit_(unsigned long duree) {
    unsigned long tDebut = millis();
    while (millis() - tDebut < duree) {
        unsigned long now = millis();
        if (now - lastTime >= interval) {
            float deltaT = (now - lastTime) / 1000.0;
            lastTime = now;

            static int32_t lastPulse0 = 0, lastPulse1 = 0;
            pulse0 = ENCODER_Read(MOTEUR_GAUCHE);
            pulse1 = ENCODER_Read(MOTEUR_DROITE);

            Vp0 = (pulse0 - lastPulse0) * distanceParPulse / deltaT;
            Vp1 = (pulse1 - lastPulse1) * distanceParPulse / deltaT;
            lastPulse0 = pulse0;
            lastPulse1 = pulse1;

            Erreur0 = Vt0 - Vp0;
            Erreur1 = Vt1 - Vp1;

            commande0 = constrain(Vt0 + KpTristan * Erreur0, -1.0, 1.0);
            commande1 = constrain(Vt1 + KpTristan * Erreur1, -1.0, 1.0);

            if (fabs(Vt0 - Vt1) < 0.05) {
                if (Vp0 > Vp1) commande0 = commande1;
                else if (Vp1 > Vp0) commande1 = commande0;
            }

            MOTOR_SetSpeed(MOTEUR_GAUCHE, commande0);
            MOTOR_SetSpeed(MOTEUR_DROITE, commande1);
        }
    }
    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0);
}

void gauche(unsigned long duree) {
    unsigned long tDebut = millis();
    while (millis() - tDebut < duree) {
        MOTOR_SetSpeed(MOTEUR_GAUCHE, -0.3);
        MOTOR_SetSpeed(MOTEUR_DROITE, 0.3);
    }
    arret();
}

void droite(unsigned long duree) {
    unsigned long tDebut = millis();
    while (millis() - tDebut < duree) {
        MOTOR_SetSpeed(MOTEUR_GAUCHE, 0.3);
        MOTOR_SetSpeed(MOTEUR_DROITE, -0.3);
    }
    arret();
}

void arret() {
    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0);
}

// void setup() {
//     BoardInit();
//     ENCODER_Reset(MOTEUR_GAUCHE);
//     ENCODER_Reset(MOTEUR_DROITE);
//     delay(50);
// }

// void loop() {
    
//     //droit_(1000);
//     //gauche(620);
//     //droite(620);

//     while (true) { 
//         arret();
//     }
// }
