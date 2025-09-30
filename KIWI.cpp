#include <Arduino.h>
#include <LibRobus.h>

#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1

const float distanceParPulse = 0.000147262;  
float Vt0 = 0.6;   
float Vt1 = 0.6;   
const float Kp = 1.2;                 
const unsigned long interval = 50;     

unsigned long lastTime = 0;
int32_t pulse0, pulse1;
float Vp0, Vp1;
float Erreur0, Erreur1;
float commande0, commande1;


void droit_() {
    unsigned long now = millis();
    if (now - lastTime >= interval) {
        float deltaT = (now - lastTime) / 1000.0;
        lastTime = now;

        pulse0 = ENCODER_ReadReset(MOTEUR_GAUCHE);
        pulse1 = ENCODER_ReadReset(MOTEUR_DROITE);

        Vp0 = pulse0 * distanceParPulse / deltaT;
        Vp1 = pulse1 * distanceParPulse / deltaT;

        Erreur0 = Vt0 - Vp0;
        Erreur1 = Vt1 - Vp1;

        commande0 = Vt0 + Kp * Erreur0;
        commande1 = Vt1 + Kp * Erreur1;

        if (fabs(Vt0 - Vt1) < 0.05) {
            if (Vp0 > Vp1) commande0 = commande1;
            else if (Vp1 > Vp0) commande1 = commande0;
        }

        MOTOR_SetSpeed(MOTEUR_GAUCHE, commande0);
        MOTOR_SetSpeed(MOTEUR_DROITE, commande1);
    }
}

void gauche() {
    MOTOR_SetSpeed(MOTEUR_GAUCHE, -0.3);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0.3);
}

void droite() {
    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0.3);
    MOTOR_SetSpeed(MOTEUR_DROITE, -0.3);
}

void arret() {
    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0);
}


void setup() {
    BoardInit();
    ENCODER_Reset(MOTEUR_GAUCHE);
    ENCODER_Reset(MOTEUR_DROITE);
    delay(50);
}


enum Action {ALLER_DROIT, TOURNE_GAUCHE, TOURNE_DROITE, TOURNE_GAUCHE2};
Action sequence[] = {ALLER_DROIT, TOURNE_GAUCHE, TOURNE_DROITE, TOURNE_GAUCHE2};
unsigned long duree[] = {1000, 620, 620, 620};
int indexAction = 0;
unsigned long tDebut = 0;


void loop() {
    if (indexAction >= sizeof(sequence)/sizeof(sequence[0])) {
        arret(); // tout fini
        return;
    }

    unsigned long maintenant = millis();

    if (tDebut == 0) tDebut = maintenant;

    // exécuter l’action courante
    switch (sequence[indexAction]) {
        case ALLER_DROIT: droit_(); break;
        case TOURNE_GAUCHE: gauche(); break;
        case TOURNE_DROITE: droite(); break;
        case TOURNE_GAUCHE2: gauche(); break;
    }

    // vérifier si durée écoulée
    if (maintenant - tDebut >= duree[indexAction]) {
        arret();
        indexAction++;
        tDebut = maintenant;
    }
}
