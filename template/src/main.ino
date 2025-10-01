/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/*
Inclure les librairies de functions que vous voulez utiliser
*/
#include <LibRobus.h>

/*
Variables globales et defines
 -> defines...
 -> L'ensemble des fonctions y ont acces
*/ 

bool bumperArr;
int vertpin = 48;
int rougepin = 49;
bool vert = false;
bool rouge = false;
int etat = 0; // = 0 arrêt 1 = avance 2 = recule 3 = TourneDroit 4 = TourneGauche
int etatPast = 0;
float vitesse = 0.30;
int colonne = 1; //0 a 2 colonnes
int rangee = 0; //0 a 9 rangees
int direction = 0;
bool tourne2f = 0;

/*
Vos propres fonctions sont creees ici
*/

void beep(int count){
  for(int i=0;i<count;i++){
    AX_BuzzerON();
    delay(100);
    AX_BuzzerOFF();
    delay(100);  
  }
  delay(400);
}

void arret(){
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
};

void avance(){
  MOTOR_SetSpeed(RIGHT,vitesse);
  MOTOR_SetSpeed(LEFT, vitesse);
  
};

void recule(){
  MOTOR_SetSpeed(RIGHT, -0.5*vitesse);
  MOTOR_SetSpeed(LEFT, -vitesse);
  
};

void tourneDroit(){
  MOTOR_SetSpeed(RIGHT, 0.5*vitesse);
  MOTOR_SetSpeed(LEFT, -0.5*vitesse);
};

void tourneGauche(){
  MOTOR_SetSpeed(RIGHT, -0.5*vitesse);
  MOTOR_SetSpeed(LEFT, 0.5*vitesse);
};

/*
Fonctions d'initialisation (setup)
 -> Se fait appeler au debut du programme
 -> Se fait appeler seulement un fois
 -> Generalement on y initilise les varibbles globales
*/
void setup(){
  BoardInit();
  
  //initialisation
  pinMode(vertpin, INPUT);
  pinMode(rougepin, INPUT);
  Serial.begin(115200);   
  delay(100);
  beep(1);
}

/*
Fonctions de boucle infini
 -> Se fait appeler perpetuellement suite au "setup"
*/
void loop() {
  etatPast = etat;
  bumperArr = ROBUS_IsBumper(3);

  // --- Bouton arrière pour start/stop ---
  if (bumperArr) {
    if (etat == 0) {
      beep(1);
      etat = 1; // démarre en avant
    } else {
      beep(1);
      etat = 0; // stop
    }
  }

  // --- Lecture capteurs ---
  vert = digitalRead(vertpin);
  rouge = digitalRead(rougepin);

  // --- Décision capteurs ---
  if (etat > 0) {
    if (vert) {               // si vert = libre
      etat = 1;               // avance
    } else {                  
      // sinon obstacle → décider gauche ou droite
      if (colonne % 2 == 0) { // si colonne paire → tourner à droite
        etat = 3; 
      } else {                // si colonne impaire → tourner à gauche
        etat = 4; 
      }
    }
  }

  // --- Transition d’état ---
  if (etatPast != etat) {
    arret();
    delay(50);
  }

  // --- Actions ---
  switch (etat) {
    case 0: // arrêt
      arret();
      break;

    case 1: // avance
      avance();

      // Mise à jour position toutes les 2s (ajuste selon ta vitesse réelle)
      static unsigned long lastUpdate = 0;
      if (millis() - lastUpdate > 2000) {
        if (direction == 0) rangee++;       // Nord
        else if (direction == 2) rangee--;  // Sud
        else if (direction == 1) colonne++; // Est
        else if (direction == 3) colonne--; // Ouest
        lastUpdate = millis();

        Serial.print("Position: Colonne=");
        Serial.print(colonne);
        Serial.print(" Rangee=");
        Serial.println(rangee);
      }
      break;

    case 3: // tourne droite
      tourneDroit();
      delay(1200); // ajuste pour 90°
      direction = (direction + 1) % 4;
      etat = 1; // après avoir tourné → avance
      break;

    case 4: // tourne gauche
      tourneGauche();
      delay(1200); // ajuste pour 90°
      direction = (direction + 3) % 4; // équivaut à -1 mod 4
      etat = 1; // après avoir tourné → avance
      break;

    default:
      arret();
      etat = 0;
      break;
  }

  delay(100);
}
