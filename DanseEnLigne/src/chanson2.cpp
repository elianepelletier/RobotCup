//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #2
#include <mouvementsBase.h>
#include "fonctionsChansons.h"
#include <libRobot.h>

void delRouge()
{
    allumeFermeAvecDelay(1500,rougePin);
}

void delJaune()
{
    allumeFermeAvecDelay(1500,jaunePin);
}

void delVerte()
{
    allumeFermeAvecDelay(1500,vertPin);
}

void delBleue()
{
    allumeFermeAvecDelay(1500,bleuPin);
}

void delRBrasDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    allumeFermeAvecDelay(1500,rougePin);
    
}

void delJBrasHaut()
{
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasHaut);
    allumeFermeAvecDelay(1500,jaunePin);
}

void delVBrasDevant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    allumeFermeAvecDelay(1500,vertPin);
}

void delBBrasBas()
{
    bougerBrasDroit(angleBrasBas);
    bougerBrasGauche(angleBrasBas);
    allumeFermeAvecDelay(1500,bleuPin);
}

void _360HoraireDelAleatoiresBrasHaut()
{
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasHaut);
    tourne(360, false);
    allumeDELaleatoire(500);
    allumeDELaleatoire(500);
}

void delREtJAlternBrasBas()
{
    bougerBrasDroit(angleBrasBas);
    bougerBrasGauche(angleBrasBas);
    allumeFermeAvecDelay(600,rougePin);
    allumeFermeAvecDelay(600,jaunePin);
    allumeFermeAvecDelay(600,rougePin);
    allumeFermeAvecDelay(600,jaunePin);
}

void delJEtVAltern()
{
    allumeFermeAvecDelay(600,jaunePin);
    allumeFermeAvecDelay(600,vertPin);
    allumeFermeAvecDelay(600,jaunePin);
    allumeFermeAvecDelay(600,vertPin);
}

void delBEtRAltern()
{
    allumeFermeAvecDelay(600,bleuPin);
    allumeFermeAvecDelay(600,rougePin);
    allumeFermeAvecDelay(600,bleuPin);
    allumeFermeAvecDelay(600,rougePin);
}

void _360AntiHoraireDelAleatoiresBrasAvant()
{
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
    tourne(360, true);
    allumeDELaleatoire(500);
    allumeDELaleatoire(500);
}