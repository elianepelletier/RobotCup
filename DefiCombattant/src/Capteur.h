//Capteur.h

#ifndef Capteur_h
#define Capteur_h

#include <Arduino.h>

int suiveurligne();
String detectColorHSV(bool afficher = true);
bool CapteurInit();

#endif