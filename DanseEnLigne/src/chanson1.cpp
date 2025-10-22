//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #1
#include "fonctionsChansons.h"
#include <mouvementsBase.h>
#include <Arduino.h>

void brasGHaut()
{
    bougerBrasGauche(180);   //va appeler la fonction (dans le fichier mouvementsDeBase.c)
    delay(int);             //qui fait bouger le bras gauche en haut (où jusqu'à un certain angle)                           
}

void brasDHaut()
{
    bougerBrasDroit(180);
    delay(int)
}

void brasGBas()
{
    bougerBrasGauche(0)
    delay(int)
}

void brasDBas()
{
    bougerBrasDroit(0)
    delay(int)
}