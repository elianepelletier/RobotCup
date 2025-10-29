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
    avance(60.0);
    tourne(90, false);
    avance(20.0);
}

void position1DelR()
{
//à partir position 0
    avance(20);
    allumeFermeAvecDelay(2000, rougePin);
}

void position2DelJ()
{
    position2();
    allumeFermeAvecDelay(2000, jaunePin);    
}

void position3DelV()
{
    position3();
    allumeFermeAvecDelay(2000, vertPin);
}

void position4DelB()
{
    position4();
    allumeFermeAvecDelay(2000, bleuPin);
}

void position0ToutesDel()
{
    position0();

    allumeDELRouge();
    allumeDELJaune();
    allumeDELVert();
    allumeDELBleu();

    fermeDELRouge();
    fermeDELJaune();
    fermeDELVert();
    fermeDELBleu();
}

void _720HoraireDelAleatoires()
{
    tourne(720, false);
    allumeDELaleatoire(500);
    allumeDELaleatoire(500);
}

void changementPlacePlus1()
{
    avance(20.0);
    tourne(90, false);
    avance(60.0);
    tourne(90, true);
    avance(20.0, -1);
}

void position0DelAleatoires()
{
    position0();
    allumeDELaleatoire(500);
    allumeDELaleatoire(500);
    allumeDELaleatoire(500);
}