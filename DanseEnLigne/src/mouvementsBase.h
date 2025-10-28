#ifndef MOUVEMENTS_BASE_
#define MOUVEMENTS_BASE_

//mettre les prototypes des fonctions du fichier mouvementsDeBase.c

extern int rougePin;
extern int jaunePin;
extern int vertPin; 
extern int bleuPin; 

void initBras();
void initDel();
void bougerBrasGauche(int angle);
void bougerBrasDroit(int angle);
void allumeDELRouge(void);
void fermeDELRouge(void);
void allumeDELJaune(void);
void fermeDELJaune(void);
void allumeDELVert(void);
void fermeDELVert(void);
void allumeDELBleu(void);
void fermeDELBleu(void);
void allumeFermeAvecDelay(int d, int pin);


#endif