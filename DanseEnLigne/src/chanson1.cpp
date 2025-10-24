//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #1
#include "fonctionsChansons.h"
#include <mouvementsBase.h>
#include <Arduino.h>

void brasGHaut()
{
    bougerBrasGauche(180);   //va appeler la fonction (dans le fichier mouvementsDeBase.c)
    delay(15);             //qui fait bouger le bras gauche en haut (où jusqu'à un certain angle)(delay à définir)                          
}

void brasDHaut()
{
    bougerBrasDroit(180);
    delay(15);
}

void brasGBas()
{
    bougerBrasGauche(0);
    delay(15);
}

void brasDBas()
{
    bougerBrasDroit(0);
    delay(15);
}

void initComposantsRobot(){
    initBras();
    initDel();
}