//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #5
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

void position1DelRBrasDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    avance(20.0);
    allumeFermeAvecDelay(1500,rougePin);
}

void position2DelJBrasHaut()
{
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasHaut);
    position2();
    allumeFermeAvecDelay(1500,jaunePin);
}

void position3DelVBrasBas()
{
    bougerBrasDroit(angleBrasBas);
    bougerBrasGauche(angleBrasBas);
    position3();
    allumeFermeAvecDelay(1500,vertPin);
}

void position4DelBBrasDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    position4();
    allumeFermeAvecDelay(1500,bleuPin);
}

void position1BrasHaut()
{
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasHaut);
    position1();
}

void position2BrasGHautBrasDDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasHaut);
    position2();
}

void position3BrasDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    position3();
}

void position4BrasGDevantBrasDHaut()
{
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasDevant);
    position4();
}