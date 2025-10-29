//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #1
#include "fonctionsChansons.h"
#include <mouvementsBase.h>
#include <Arduino.h>

void brasGHaut()
{
    bougerBrasGauche(angleBrasHautG);   //va appeler la fonction (dans le fichier mouvementsDeBase.c)
    delay(15);             //qui fait bouger le bras gauche en haut (où jusqu'à un certain angle)(delay à définir)                          
}

void brasDHaut()
{
    bougerBrasDroit(angleBrasHautD);
    delay(15);
}

void brasGBas()
{
    bougerBrasGauche(angleBrasBasG);
    delay(15);
}

void brasDBas()
{
    bougerBrasDroit(angleBrasBasD);
    delay(15);
}

void initComposantsRobot(){
    initBras();
    initDel();
    // allumeDELRouge();
    // delay(1000);
    // fermeDELRouge();
    // allumeDELJaune();
    // delay(1000);
    // fermeDELJaune();
    // allumeDELVert();
    // delay(1000);
    // fermeDELVert();
    // allumeDELBleu();
    // delay(1000);
    // fermeDELBleu();
    
}