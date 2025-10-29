//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #3
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

//à partir de pos 0
void position1BrasBas()
{
    bougerBrasDroit(angleBrasBasD);
    bougerBrasGauche(angleBrasBasG);
    avance(20.0);
}

//à partir de pos 1
void position2()
{
    tourne(45, false);
    avance(hypothenuse, -1); 
    tourne(45, true);
}

//à partir de pos 2
void position3()
{
    tourne(45, true);
    avance(hypothenuse, -1);
    tourne(45, false);
}

//à partir de pos 3
void position4()
{
    tourne(45, false);
    avance(hypothenuse);
    tourne(45, true);
}

//à partir de pos 4
void position1()
{
    tourne(45, true);
    avance(hypothenuse);
    tourne(45, false);
}