#include <Arduino.h>
#include <LibRobus.h>
#include <math.h>
#include <stdio.h>

float Q=0; // encodeur gauhce
float K=0; // encodeur droit
float H=0;
float pulse_scan=0;
int   PULSE_90=1932; // virage de 90 degre
int   PULSE_360=7728;
int   PULSE_180=3864;
int   PULSE_270=5796;
float V=0.35;

/*
********************************************************************************
                         FONCTIONS DE ROMAN + BENJAMIN
********************************************************************************
*/

#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1

// ---- CONSTANTES ----
const float distanceParPulse = 0.000147262 ; // roue 3 pouces, encodeur 3200 pulses
const float Kp = 1.2;                     // gain PID
const unsigned long interval = 50;        // ms
const float vitesseAvance = 0.3;
const float vitesseRotation = 0.25;

// ---- VARIABLES PID ----
float Vt0 = vitesseAvance;
float Vt1 = vitesseAvance;
static unsigned long lastTime = 0;



float vitesse = 0.4; // vitesse par défaut

// conversion cm -> ticks encodeur
int cmToTicks(float cm) {
  return cm * 13581; // ajuster selon roue
}

// conversion angle -> ticks encodeur
int angleToTicks(float angle) {
  float distance = (angle / 360.0) * 0.195 * PI; // circonférence roue = 0.195 m
  return distance * 13581;
}

// ====================================================================
// AVANCER D’UNE DISTANCE DONNÉE (cm)
// ====================================================================
void avance(float distanceCm) {
    ENCODER_Reset(MOTEUR_GAUCHE);
    ENCODER_Reset(MOTEUR_DROITE);

    // ← CHANGEMENT ICI
    int32_t lastPulse0 = ENCODER_Read(MOTEUR_GAUCHE);
    int32_t lastPulse1 = ENCODER_Read(MOTEUR_DROITE);

    lastTime = millis();
    float distanceM = distanceCm / 100.0 * 2.067;

    Vt0 = vitesseAvance;
    Vt1 = vitesseAvance;

    while (true) {
        unsigned long now = millis();
        if (now - lastTime >= interval) {
            float deltaT = (now - lastTime) / 1000.0;
            lastTime = now;

            int32_t pulse0 = ENCODER_Read(MOTEUR_GAUCHE);
            int32_t pulse1 = ENCODER_Read(MOTEUR_DROITE);

            float Vp0 = (pulse0 - lastPulse0) * distanceParPulse / deltaT;
            float Vp1 = (pulse1 - lastPulse1) * distanceParPulse / deltaT;

            lastPulse0 = pulse0;
            lastPulse1 = pulse1;

            float Erreur0 = Vt0 - Vp0;
            float Erreur1 = Vt1 - Vp1;

            float commande0 = constrain(Vt0 + Kp * Erreur0, -1.0, 1.0);
            float commande1 = constrain(Vt1 + Kp * Erreur1, -1.0, 1.0);

            MOTOR_SetSpeed(MOTEUR_GAUCHE, commande0);
            MOTOR_SetSpeed(MOTEUR_DROITE, commande1);

            float distG = pulse0 * distanceParPulse;
            float distD = pulse1 * distanceParPulse;
            if ((distG + distD) / 2.0 >= distanceM) break;
        }
    }

    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0);
}

// ====================================================================
// TOURNER D’UN ANGLE DONNÉ (°)
// gauche = true → gauche, false → droite
// ====================================================================
void tourne(int angleDeg, bool tourneGauche) {
    ENCODER_Reset(MOTEUR_GAUCHE);
    ENCODER_Reset(MOTEUR_DROITE);

    int32_t lastPulse0 = ENCODER_Read(MOTEUR_GAUCHE);
    int32_t lastPulse1 = ENCODER_Read(MOTEUR_DROITE);

    lastTime = millis();
    const float pulsesParDegre = 22.1;  // à calibrer selon ton robot
    float cible = angleDeg * pulsesParDegre;

    // Consignes de vitesse
    float consigne = vitesseRotation;

    while (true) {
        unsigned long now = millis();
        if (now - lastTime >= interval) {
            float deltaT = (now - lastTime) / 1000.0;
            lastTime = now;

            int32_t pulse0 = ENCODER_Read(MOTEUR_GAUCHE);
            int32_t pulse1 = ENCODER_Read(MOTEUR_DROITE);

            float Vp0 = (pulse0 - lastPulse0) * distanceParPulse / deltaT;
            float Vp1 = (pulse1 - lastPulse1) * distanceParPulse / deltaT;

            lastPulse0 = pulse0;
            lastPulse1 = pulse1;

            // ---- Définir les consignes selon le sens de rotation ----
            if (tourneGauche) {
                Vt0 = -consigne;
                Vt1 = consigne;
            } else {
                Vt0 = consigne;
                Vt1 = -consigne;
            }

            // ---- PID proportionnel ----
            float Erreur0 = Vt0 - Vp0;
            float Erreur1 = Vt1 - Vp1;

            float commande0 = constrain(Vt0 + Kp * Erreur0, -1.0, 1.0);
            float commande1 = constrain(Vt1 + Kp * Erreur1, -1.0, 1.0);
            
            MOTOR_SetSpeed(MOTEUR_GAUCHE, commande0);
            MOTOR_SetSpeed(MOTEUR_DROITE, commande1);
        }

        // ---- Condition de fin : vérifier si l'angle visé est atteint ----
        int32_t absG = abs(ENCODER_Read(MOTEUR_GAUCHE));
        int32_t absD = abs(ENCODER_Read(MOTEUR_DROITE));
        if ((absG + absD) / 2.0 >= cible) break;
    }

    MOTOR_SetSpeed(MOTEUR_GAUCHE, 0);
    MOTOR_SetSpeed(MOTEUR_DROITE, 0);
}



/*
******************************************************************
                         FONCTIONS DE TRISTAN

******************************************************************
*/
void TournerDroite90_PROVISOIRE()
{
    
    ENCODER_Reset(0);
    ENCODER_Reset(1);

    
    MOTOR_SetSpeed(0, V);   
    MOTOR_SetSpeed(1, -V);  

    while (fabs(ENCODER_Read(0)) < PULSE_90 && fabs(ENCODER_Read(1)) > (-1)*PULSE_90)
    {
       
    }

    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
}


void TournerGauche90_PROVISOIRE()
{
    
    ENCODER_Reset(0);
    ENCODER_Reset(1);

    MOTOR_SetSpeed(0, -V);  
    MOTOR_SetSpeed(1, V);  

    while (fabs(ENCODER_Read(0)) < PULSE_90 && fabs(ENCODER_Read(1)) < PULSE_90)
    {
       
    }

    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);


}
void GAUCHE_360_scan(void) // on scan ou est la quille
{

  while ((((fabs(ENCODER_Read(0))) + (fabs(ENCODER_Read(1))))/2) < PULSE_360)
  {
      
    MOTOR_SetSpeed(0, -V);
    MOTOR_SetSpeed(1, V);
       
    
    if (ROBUS_ReadIR(0) >= 268) //  A CALIBRER detecte qqch stop lorsque le capteur donne une valeur plus haute que 0.6V !!conversion volt en bits maybe!!
    {
      MOTOR_SetSpeed(0, 0.0);
      MOTOR_SetSpeed(1, 0.0);
      K =fabs(ENCODER_Read(1));
      Q =fabs(ENCODER_Read(0)); 
      pulse_scan = ((K+Q)/2);
      break;
    }
  }
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}

// go foward pour fair tomber la quille
void  REACH_the_quille(void)
{
    ENCODER_Reset(0);
    ENCODER_Reset(1);

  while( (fabs(ENCODER_Read(0))+fabs(ENCODER_Read(1)))/2 < 3500 ) 
  {
  MOTOR_SetSpeed(0, V);
  MOTOR_SetSpeed(1, V);
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);

}


// on fait spinner le robot (attack)
void  Kill_the_quille(void )           
{
       
   ENCODER_Reset(0);
   ENCODER_Reset(1);
   delay(50);
   float reste_pour_X;

    // On calcule la distance la plus courte vers l'axe X (0 ou 8124/2)
    if (pulse_scan < PULSE_360 / 2.0)
    {
        reste_pour_X = (PULSE_360 / 2.0) - pulse_scan;
    }
    else
    {
        reste_pour_X = PULSE_360 - pulse_scan; // tourner dans l'autre sens
    }
    while (((fabs(ENCODER_Read(0)) + fabs(ENCODER_Read(1)))/2) < reste_pour_X)
    {

        MOTOR_SetSpeed(1, V);
        MOTOR_SetSpeed(0, -V);
    }


    MOTOR_SetSpeed(1, 0);
    MOTOR_SetSpeed(0, 0);
    TournerGauche90_PROVISOIRE();
}


void Leave_the_quille(void)   
{
    MOTOR_SetSpeed(0, V);
    MOTOR_SetSpeed(1, V);
    delay(2500);
        while (((fabs(ENCODER_Read(0)) + fabs(ENCODER_Read(1))) / 2.0) < 3200) ///////modifier pour detecteur de ligne
    {
        MOTOR_SetSpeed(0, V);
        MOTOR_SetSpeed(1, V);
    }


    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
    delay(250);

    float angle_actuel = (Q + K) / 2.0; 
    if (angle_actuel >= 0 && angle_actuel <= PULSE_180)  
    {
        TournerGauche90_PROVISOIRE(); 
    }
    
    else
    {
        TournerDroite90_PROVISOIRE();
    }

}


void BACK_ON_TRACK (void)   
{

    if (((K+Q)/2) < PULSE_180)  // gauche du cercle trigo -> virage vers la gauche pour continuer dans le bon sens

        {
            TournerGauche90_PROVISOIRE(); 
        }

    if (((K+Q)/2) > PULSE_180) // droite du cercle trigo -> virage vers la droite pour continuer dans le bon sens

        {
           TournerDroite90_PROVISOIRE();
        }
}



void TOURCOMPLET_CALIBRATION(void)
/* En théorie un tour complet d'evrait être 8124 pulse cependant, en pratique c pas la même ces fonction sera utiliser pour calibrer le code sera ajusté après*/
{

    while (((fabs(ENCODER_Read(0)))+(fabs(ENCODER_Read(1)))/2) <PULSE_360)
    {
        MOTOR_SetSpeed(1, V);
        MOTOR_SetSpeed(0, -V);
    }
}




void quille(void)
{

    ENCODER_Reset(0);
    ENCODER_Reset(1);

    delay(500);

    GAUCHE_360_scan();

    delay(500);

    REACH_the_quille();

    delay(500);

    Kill_the_quille();

    delay(500);

    Leave_the_quille();

    delay(500);

}




  

