//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #5
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

void position1DelRBrasDevant()
{
    bougerBrasDroit(angleBrasDevantD);
    bougerBrasGauche(angleBrasDevantD);
    avance(20.0);
    allumeFermeAvecDelay(1500,rougePin);
}

void position2DelJBrasHaut()
{
    bougerBrasDroit(angleBrasHautD);
    bougerBrasGauche(angleBrasHautD);
    position2();
    allumeFermeAvecDelay(1500,jaunePin);
}

void position3DelVBrasBas()
{
    bougerBrasDroit(angleBrasBasD);
    bougerBrasGauche(angleBrasBasD);
    position3();
    allumeFermeAvecDelay(1500,vertPin);
}

void position4DelBBrasDevant()
{
    bougerBrasDroit(angleBrasDevantD);
    bougerBrasGauche(angleBrasDevantD);
    position4();
    allumeFermeAvecDelay(1500,bleuPin);
}

void position1BrasHaut()
{
    bougerBrasDroit(angleBrasHautD);
    bougerBrasGauche(angleBrasHautG);
    position1();
}

void position2BrasGHautBrasDDevant()
{
    bougerBrasDroit(angleBrasDevantD);
    bougerBrasGauche(angleBrasHautG);
    position2();
}

void position3BrasDevant()
{
    bougerBrasDroit(angleBrasDevantD);
    bougerBrasGauche(angleBrasDevantG);
    position3();
}

void position4BrasGDevantBrasDHaut()
{
    bougerBrasDroit(angleBrasHautD);
    bougerBrasGauche(angleBrasDevantG);
    position4();
}