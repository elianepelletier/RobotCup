//va contenir toutes les fonctions décrivant les mouvements qui se produiront pendant la chanson #2
#include <mouvementsBase.h>
#include "fonctionsChansons.h"

void delRouge()
{
    allumeFermeAvecDelay(3500,rougePin);
}

void delJaune()
{
    allumeFermeAvecDelay(3500,jaunePin);
}

void delVerte()
{
    allumeFermeAvecDelay(3500,vertPin);
}

void delBleue()
{
    allumeFermeAvecDelay(3500,bleuPin);
}

void delRBrasDevant()
{
    allumeFermeAvecDelay(3500,rougePin);
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
}

void delJBrasHaut()
{
    allumeFermeAvecDelay(3500,jaunePin);
    bougerBrasDroit(angleBrasHaut);
    bougerBrasGauche(angleBrasHaut);
}

void delVBrasDevant()
{
    allumeFermeAvecDelay(3500,vertPin);
    bougerBrasDroit(angleBrasDevant);
    bougerBrasGauche(angleBrasDevant);
}

void delBBrasBas()
{
    allumeFermeAvecDelay(3500,bleuPin);
    bougerBrasDroit(angleBrasBas);
    bougerBrasGauche(angleBrasBas);
}

void _360HoraireDelAleatoiresBrasHaut()
{
    
}

void delREtJAlternBrasBas()
{
}

void delJEtVAltern()
{
}

void delBEtRAltern()
{
}

void _360AntiHoraireDelAleatoiresBrasAvant()
{
}