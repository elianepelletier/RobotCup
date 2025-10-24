#include <Arduino.h>
#include <LibRobus.h>
#include <fonctionsChansons.h>

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
    initComposantsRobot();
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
            delRouge();
			break;

		case 5:
            delJaune();
			break;

		case 6:
            delVerte();
			break;

		case 7:
            delBleue();
			break;

		case 8:
            delRBrasDevant();
			break;

		case 9:
            delJBrasHaut();
			break;

		case 10:
            delVBrasDevant();
			break;

		case 11:
            delBBrasBas();
			break;

		case 12:
            _360HoraireDelAleatoiresBrasHaut();
			break;

		case 13:
            delREtJAlternBrasBas();
            break;
            
		case 14:
            delJEtVAltern();
			break;

		case 15:
            delBEtRAltern();
			break;

		case 16:
            _360AntiHoraireDelAleatoiresBrasAvant();
			break;

		case 17:
            position1BrasBas();
			break;

		case 18:
            position2();
			break;

		case 19:
            position3();
			break;

		case 20:
            position4();
			break;

		case 21:
            position1();
			break;

		case 22:
            position0();
			break;

		case 23:
            changementPlaceMoins1();
			break;

		case 24:
            position1DelR();
			break;

		case 25:
            position2DelJ();
			break;

		case 26:
            position3DelV();
			break;

		case 27:
            position4DelB();
			break;

		case 28:
            position0ToutesDel();
			break;

		case 29:
            _720HoraireDelAleatoires();
			break;

		case 30:
            changementPlacePlus1();
			break;

		case 31:
            position0DelAleatoires();
			break;

		case 32:
            position1DelRBrasDevant();
			break;

		case 33:
            position2DelJBrasHaut();
			break;

		case 34:
            position3DelVBrasBas();
			break;

		case 35:
            position4DelBBrasDevant();
			break;

		case 36:
            position1BrasHaut();
			break;

		case 37:
            position2BrasGHautBrasDDevant();
			break;

		case 38:
            position3BrasDevant();
			break;

		case 39:
            position4BrasGDevantBrasDHaut();
			break;

		default:
			break;

    }
}

//le tableau est juste rempli pour les 5 premières chansons (manque la 6e)
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

    Action action17;
    action17.temps =  64000;
    action17.mouv =  POSITION_1_BRAS_BAS;
    tabActions[17] = action17;

    Action action18;
    action18.temps =  68000;
    action18.mouv =  POSITION_2;
    tabActions[18] = action18;

    Action action19;
    action19.temps =  72000;
    action19.mouv =  POSITION_3;
    tabActions[19] = action19;

    Action action20;
    action20.temps =  76000;
    action20.mouv =  POSITION_4;
    tabActions[20] = action20;

    Action action21;
    action21.temps =  80000;
    action21.mouv =  POSITION_1;
    tabActions[21] = action21;

    Action action22;
    action22.temps =  84000;
    action22.mouv =  POSITION_2;
    tabActions[22] = action22;

    Action action23;
    action23.temps =  88000;
    action23.mouv =  POSITION_3;
    tabActions[23] = action23;

    Action action24;
    action24.temps =  92000;
    action24.mouv =  POSITION_4;
    tabActions[24] = action24;

    Action action25;
    action25.temps =  96000;
    action25.mouv =  POSITION_0;
    tabActions[25] = action25;

    Action action26;
    action26.temps =  100000;
    action26.mouv =  CHANGEMENT_PLACE_MOINS_1;
    tabActions[26] = action26;

    Action action27;
    action27.temps =  108000;
    action27.mouv =  POSITION_1_DEL_R;
    tabActions[27] = action27;

    Action action28;
    action28.temps =  112000;
    action28.mouv =  POSITION_2_DEL_J;
    tabActions[28] = action28;

    Action action29;
    action29.temps =  116000;
    action29.mouv =  POSITION_3_DEL_V;
    tabActions[29] = action29;

    Action action30;
    action30.temps =  120000;
    action30.mouv =  POSITION_4_DEL_B;
    tabActions[30] = action30;

    Action action31;
    action31.temps =  124000;
    action31.mouv =  POSITION_0_TOUTES_DEL;
    tabActions[31] = action31;

    Action action32;
    action32.temps =  128000;
    action32.mouv =  _720_HORAIRE_DEL_ALEATOIRES;
    tabActions[32] = action32;

    Action action33;
    action33.temps =  132000;
    action33.mouv =  CHANGEMENT_PLACE_PLUS_1;
    tabActions[33] = action33;

    Action action34;
    action34.temps =  140000;
    action34.mouv =  POSITION_1_DEL_R;
    tabActions[34] = action34;

    Action action35;
    action35.temps =  144000;
    action35.mouv =  POSITION_2_DEL_J;
    tabActions[35] = action35;

    Action action36;
    action36.temps =  148000;
    action36.mouv =  POSITION_3_DEL_V;
    tabActions[36] = action36;

    Action action37;
    action37.temps = 152000;  
    action37.mouv =  POSITION_4_DEL_B;
    tabActions[37] = action37;

    Action action38;
    action38.temps =  156000;
    action38.mouv =  POSITION_0_DEL_ALEATOIRES;
    tabActions[38] = action38;

    Action action39;
    action39.temps =  160000;
    action39.mouv =  POSITION_1_DEL_R_BRAS_DEVANT;
    tabActions[39] = action39;

    Action action40;
    action40.temps =  164000;
    action40.mouv =  POSITION_2_DEL_J_BRAS_HAUT;
    tabActions[40] = action40;

    Action action41;
    action41.temps =  168000;
    action41.mouv =  POSITION_3_DEL_V_BRAS_BAS;
    tabActions[41] = action41;

    Action action42;
    action42.temps =  172000;
    action42.mouv =  POSITION_4_DEL_B_BRAS_DEVANT;
    tabActions[42] = action42;

    Action action43;
    action43.temps =  176000;
    action43.mouv =  POSITION_1_BRAS_HAUT;
    tabActions[43] = action43;

    Action action44;
    action44.temps =  180000;
    action44.mouv =  POSITION_2_BRAS_G_HAUT_BRAS_D_DEVANT;
    tabActions[44] = action44;

    Action action45;
    action45.temps =  184000;
    action45.mouv =  POSITION_3_BRAS_DEVANT;
    tabActions[45] = action45;

    Action action46;
    action46.temps =  188000;
    action46.mouv =  POSITION_4_BRAS_G_DEVANT_BRAS_D_HAUT;
    tabActions[46] = action46;
}

