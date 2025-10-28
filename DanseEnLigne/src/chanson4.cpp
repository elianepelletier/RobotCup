//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #4
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

//à partir de pos 4
void position0()
{
    tourne(90, true);
    avance(20);
    tourne(90, false);
}

void changementPlaceMoins1()
{
    avance(20.0, -1);
    tourne(90, true);
    avance(80.0);
    tourne(90, false);
    avance(20.0);
}

void position1DelR()
{
//à partir position 0
}

void position2DelJ()
{
    //réutiliser fonctions
}

void position3DelV()
{
}

void position4DelB()
{
}

void position0ToutesDel()
{
}

void _720HoraireDelAleatoires()
{
}

void changementPlacePlus1()
{
    avance(20.0);
    tourne(90, false);
    avance(80.0);
    tourne(90, true);
    avance(20.0, -1);
}

void position0DelAleatoires()
{
}