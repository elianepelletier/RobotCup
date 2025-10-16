#define ROBOTMOVE_H

#include <Arduino.h>
#include <librobus.h>

// vitesse par défaut
extern float vitesse;

// fonctions globales
void avance(float cm);          // avance en cm
void tourne(float angle, int sens); // sens: 1=droite, 0=gauche