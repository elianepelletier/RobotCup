//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #3
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

//à partir de pos 0
void position1BrasBas()
{
    bougerBrasDroit(angleBrasBas);
    bougerBrasGauche(angleBrasBas);
    avance(20.0);
}

//à partir de pos 1
void position2()
{
    avance(20, -1);
    tourne(90, true);
    avance(20); 
    tourne(90, false);
}

//à partir de pos 2
void position3()
{
    tourne(90, false);
    avance(20);
    tourne(90, true);
    avance(20, -1);
}

//à partir de pos 3
void position4()
{
    avance(20);
    tourne(90, false);
    avance(20);
    tourne(90, true);
}

//à partir de pos 4
void position1()
{
    tourne(90, true);
    avance(20);
    tourne(90, false);
    avance(20);
}