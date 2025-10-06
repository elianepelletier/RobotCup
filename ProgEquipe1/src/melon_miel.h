#pragma once

#include <Arduino.h>
#include <librobus.h>

// --- Définitions des moteurs et distances ---
#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1
#define QUATRE_VINGT_DIX 610
#define CINQUANTE_CENTIMETRE 2800
#define CENT_QUATRE_VINGT_DIX 1220

// --- Constantes pour régulation vitesse ---
const float distanceParPulse = 0.000147262;  
extern float Vt0;   
extern float Vt1;   
const float Kp = 1.2;                 
const unsigned long interval = 50;     

// --- Variables globales ---
extern unsigned long lastTime;
extern int32_t pulse0, pulse1;
extern float Vp0, Vp1;
extern float Erreur0, Erreur1;
extern float commande0, commande1;

// --- Prototypes de fonctions ---
void arret();
void droit_(unsigned long duree);
void gauche(unsigned long duree);
void droite(unsigned long duree);
