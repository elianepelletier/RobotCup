#ifndef LIBROBOT_H
#define LIBROBOT_H

#include <Arduino.h>
#include <librobus.h>

// ---- CONSTANTES ----
#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1

// ---- VARIABLES externes ----
extern float Vt0;
extern float Vt1;

// ---- FONCTIONS ----
void arret();
void avance(float distanceCm, int direction = 1);            // avance en cm
void tourne(int angleDeg, bool tourneGauche); // tourneGauche = true=gauche, false=droite
void quille(void);

#endif