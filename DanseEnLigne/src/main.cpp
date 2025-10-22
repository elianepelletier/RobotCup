#include <Arduino.h>
#include <LibRobus.h>
#include <fonctionsChansons.h>

<<<<<<< Updated upstream
#define LONG_TAB 47 //manque dernière chanson

enum mouvements {
BRAS_G_HAUT,
BRAS_D_HAUT,
BRAS_G_BAS,
BRAS_D_BAS,

DEL_ROUGE,
DEL_JAUNE,
DEL_VERTE,
DEL_BLEUE,
DEL_R_BRAS_DEVANT,
DEL_J_BRAS_HAUT,
DEL_V_BRAS_DEVANT,
DEL_B_BRAS_BAS,
_360_HORAIRE_DEL_ALEATOIRES_BRAS_HAUT,
DEL_R_ET_J_ALTERN_BRAS_BAS,
DEL_J_ET_V_ALTERN,
DEL_B_ET_R_ALTERN,
_360_ANTI_HORAIRE_DEL_ALEATOIRES_BRAS_AVANT,

POSITION_1_BRAS_BAS,
POSITION_2,
POSITION_3,
POSITION_4,
POSITION_1,

POSITION_0,
CHANGEMENT_PLACE_MOINS_1,
POSITION_1_DEL_R,
POSITION_2_DEL_J,
POSITION_3_DEL_V,
POSITION_4_DEL_B,
POSITION_0_TOUTES_DEL,
_720_HORAIRE_DEL_ALEATOIRES,
CHANGEMENT_PLACE_PLUS_1,
POSITION_0_DEL_ALEATOIRES,

POSITION_1_DEL_R_BRAS_DEVANT,
POSITION_2_DEL_J_BRAS_HAUT,
POSITION_3_DEL_V_BRAS_BAS,
POSITION_4_DEL_B_BRAS_DEVANT,
POSITION_1_BRAS_HAUT,
POSITION_2_BRAS_G_HAUT_BRAS_D_DEVANT,
POSITION_3_BRAS_DEVANT,
POSITION_4_BRAS_G_DEVANT_BRAS_D_HAUT
}; //manque dernière chanson

typedef struct 
{
    long temps; //temps auquel le mouvement doit être executer si le temps de départ est de 0 (donc doit additionner à tempsDepart) 
    enum mouvements mouv; //mouvement à effectuer de l'énum

} Action;

//variables globales
long tempsDepart;
Action tabActions[LONG_TAB]; //manque la dernière chanson

//prototypes de fonctions
void remplissageTabActions();
void appelFonctionMouvement(enum mouvements mouv);

void setup() {
    BoardInit();
    //mettre les pin mode pour les 4 del

    remplissageTabActions();
}

void loop() {
    bool bumperArr = ROBUS_IsBumper(3);

    if (bumperArr)
    {
        tempsDepart = millis();

        //parcours le tableau
        for (int i = 0; i < LONG_TAB; i++)
        {
            Action action = tabActions[i]; 
            int difference = (action.temps + tempsDepart) - millis();
            
            if (difference > 0)
            {
                delay(difference);
                i--;
            } else {
                appelFonctionMouvement(action.mouv);
            }
            
        }
        
    }
}

void appelFonctionMouvement(enum mouvements mouv){
    //manque les cases pour les chansons 3, 4, 5 et 6
    //manque l'appel des fonctions pour la 2e chanson

	switch (mouv)
	{
		case 0:
            brasGHaut();
			break;

		case 1:
            brasDHaut();
			break;

		case 2:
            brasGBas();
			break;

		case 3:
            brasDBas();
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		case 9:
			break;

		case 10:
			break;

		case 11:
			break;

		case 12:
			break;

		case 13:
            break;
            
		case 14:
			break;

		case 15:
			break;

		case 16:
			break;

		case 17:
			break;

		case 18:
			break;

		case 19:
			break;

		case 20:
			break;

		case 21:
			break;

		case 22:
			break;

		case 23:
			break;

		case 24:
			break;

		case 25:
			break;

		case 26:
			break;

		case 27:
			break;

		case 28:
			break;

		case 29:
			break;

		case 30:
			break;

		case 31:
			break;

		case 32:
			break;

		case 33:
			break;

		case 34:
			break;

		case 35:
			break;

		case 36:
			break;

		case 37:
			break;

		case 38:
			break;

		case 39:
			break;

		default:
			break;

    }
}

//le tableau est juste rempli pour les 2 premières chansons
void remplissageTabActions(){
    Action action0;
    action0.temps = 16000;
    action0.mouv = BRAS_G_HAUT;
    tabActions[0] = action0;

    Action action1;
    action1.temps = 18000;
    action1.mouv = BRAS_D_HAUT;
    tabActions[1] = action1;

    Action action2;
    action2.temps = 20000;
    action2.mouv = BRAS_G_BAS;
    tabActions[2] = action2;

    Action action3;
    action3.temps = 22000;
    action3.mouv = BRAS_D_BAS;
    tabActions[3] = action3;

    Action action4;
    action4.temps = 32000;
    action4.mouv = DEL_ROUGE;
    tabActions[4] = action4;

    Action action5;
    action5.temps = 34000;
    action5.mouv = DEL_JAUNE;
    tabActions[5] = action5;

    Action action6;
    action6.temps = 36000;
    action6.mouv = DEL_VERTE;
    tabActions[6] = action6;

    Action action7;
    action7.temps = 38000;
    action7.mouv = DEL_BLEUE;
    tabActions[7] = action7;

    Action action8;
    action8.temps = 40000;
    action8.mouv = DEL_R_BRAS_DEVANT;
    tabActions[8] = action8;

    Action action9;
    action9.temps = 42000;
    action9.mouv = DEL_J_BRAS_HAUT;
    tabActions[9] = action9;

    Action action10;
    action10.temps = 44000;
    action10.mouv = DEL_V_BRAS_DEVANT;
    tabActions[10] = action10;

    Action action11;
    action11.temps = 46000;
    action11.mouv = DEL_B_BRAS_BAS;
    tabActions[11] = action11;

    Action action12;
    action12.temps = 48000;
    action12.mouv = _360_HORAIRE_DEL_ALEATOIRES_BRAS_HAUT;
    tabActions[12] = action12;

    Action action13;
    action13.temps = 52000;
    action13.mouv = DEL_R_ET_J_ALTERN_BRAS_BAS;
    tabActions[13] = action13;

    Action action14;
    action14.temps = 54000;
    action14.mouv = DEL_J_ET_V_ALTERN;
    tabActions[14] = action14;

    Action action15;
    action15.temps = 58000;
    action15.mouv = DEL_B_ET_R_ALTERN;
    tabActions[15] = action15;

    Action action16;
    action16.temps = 60000;
    action16.mouv = _360_ANTI_HORAIRE_DEL_ALEATOIRES_BRAS_AVANT;
    tabActions[16] = action16;

<<<<<<< Updated upstream
}

=======
=======
//go crazy danse en ligne

void setup() {
 

}

void loop() {

  
>>>>>>> Stashed changes
}
>>>>>>> Stashed changes
