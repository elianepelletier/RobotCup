#include <Arduino.h>
#include <librobus.h>
#define RANGEE_FIN 9
#define RANGEE_DEBUT 0

bool vraiSiPasCommence = true;

int numRangee = 0; //valeurs possibles : 0 à 9
int numColonne = 1; //valeurs possibles : 0, 1, ou 2

int directionRobot = 1; //gauche = 0, fin = 1, droite = 2 et début = 3 (après modulo 4)
int directionVoulue = 1; //vers la fin
int tourneGaucheDroite = 1; //tourne droite = 1 (90), tourne gauche = 0 (180)

bool bumperArr;
float vitesse = 0.40;

int vertpin = 48;
int rougepin = 49;
bool vert = false;
bool rouge = false;


void priseDecisionRobot();
bool vraiSiPasMursCapteurs();
bool vraiSiMursExt();
void tourner();
void avancer();
void avance();
void arret();
void tourneDroit();
void tourneGauche();

void setup() {
  BoardInit();
  
  pinMode(vertpin, INPUT);
  pinMode(rougepin, INPUT);
  delay(100);

}

void loop() {
  // ajout du if pour détection 5Khz
   bumperArr = ROBUS_IsBumper(3);
   
   if (bumperArr)
   {
    priseDecisionRobot();
   }
}

void priseDecisionRobot(){

  while (numRangee < RANGEE_FIN)
  {
    if (vraiSiPasMursCapteurs())
    {
      if (vraiSiMursExt())
      {
        tourner();
      }
      else 
      {
        avancer();
      }
      
    } 
    else 
    {
      tourner();
    }
  }
}

//vrai si pas de murs, faux si murs
bool vraiSiPasMursCapteurs(){
  vert = digitalRead(vertpin);
  rouge = digitalRead(rougepin);

  if(vert && rouge){
    return true;
  }
  else{
    return false;
  }
}

//vrai si mur noir devant robot (tape)
bool vraiSiMursExt(){
  if(numColonne == (directionRobot % 4) && numColonne != 1){
  return true;
  } 
  else if (numRangee == 0 && (directionRobot % 4) == 3)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//vérifie quel sens tourner
//appel fct moteurs (fct)
//changer var direction
void tourner(){
  if(tourneGaucheDroite == 1){
    //appelle fct moteur tourne droite
    tourneDroit();
    delay(1000); //pour tourner 90 degrés
    arret();

    directionRobot=directionRobot+1;
    tourneGaucheDroite=0;
  }
  else if(tourneGaucheDroite == 0){
    //appelle fct moteur tourne gauche
    tourneGauche();
    delay(2000); //pour tourner 90 degrés
    arret();

    directionRobot=directionRobot-2;
    tourneGaucheDroite=1;
  }
}

//appel fct moteur avancer
//change var rangée et colonne dépendant orientation
void avancer(){
  //appeller fct moteur avancer
  avance();
  delay(1600); //pour avancer environ 50 cm
  arret();


  if((directionRobot % 4) == 0){
    numColonne = numColonne-1;
  }
  else if((directionRobot % 4) == 1){
    numRangee = numRangee+1;
  }
  else if((directionRobot % 4) == 2){
    numColonne = numColonne+1;
  }
  else if((directionRobot % 4) == 3){
    numRangee = numRangee-1;
  }
  tourneGaucheDroite = 1;
}

void arret(){
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
};

void avance(){
  MOTOR_SetSpeed(RIGHT,vitesse);
  MOTOR_SetSpeed(LEFT, vitesse);
};

void tourneDroit(){
  //MOTOR_SetSpeed(RIGHT, 0.5*vitesse);
  //MOTOR_SetSpeed(LEFT, -0.5*vitesse);
  MOTOR_SetSpeed(RIGHT, -0.5*vitesse);
  MOTOR_SetSpeed(LEFT, 0.5*vitesse);
  
};

void tourneGauche(){
  //MOTOR_SetSpeed(RIGHT, -0.5*vitesse);
  //MOTOR_SetSpeed(LEFT, 0.5*vitesse);
  MOTOR_SetSpeed(RIGHT, 0.5*vitesse);
  MOTOR_SetSpeed(LEFT, -0.5*vitesse);
};