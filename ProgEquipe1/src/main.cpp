#include <Arduino.h>
#include <librobus.h>
#define RANGEE_FIN 9
#define RANGEE_DEBUT 0

bool vraiSiPasCommence = true;

int numRangee = 0; //valeurs possibles : 0 à 9
int numColonne = 1; //valeurs possibles : 0, 1, ou 2

int directionRobot = 1; //gauche = 0, fin = 1, droite = 2 et début = 3
int directionVoulue = 1; //vers la fin
int tourneGaucheDroite = 1; //tourne droite = 1 (90), tourne gauche = 0 (180)
bool bumperArr;
int vertpin = 48;
int rougepin = 49;
bool vert = false;
bool rouge = false;



void priseDecisionRobot();
bool verifieCapteurs();
bool verifieMursExt();
void tourner();
void avancer();

void setup() {
  BoardInit();
  
  //initialisation
  pinMode(vertpin, INPUT);
  pinMode(rougepin, INPUT);
  delay(100);
 //pin mode à setter

  //mettre dans loop
  priseDecisionRobot();
}

void loop() {
  // ajout du if pour détection 5Khz
  
  
}

void priseDecisionRobot(){

  while (numRangee < RANGEE_FIN)
  {
    if (verifieCapteurs())
    {
      if (verifieMursExt())
      {
        tourner();
        //tourne (update direction robot)
      }
       else {
        //avance 1 case (update num rangee ou colonne) 
        avancer();
      }
      

    } else {
      //tourne (update direction robot)
      tourner();
    }
    
    
  }
  

}

//vrai si pas de murs, faux si murs
bool verifieCapteurs(){
  vert = digitalRead(vertpin);
  rouge = digitalRead(rougepin);

  if(vert && rouge){
    return true;
  }
  else{
    return false;
  }
}

//numMur = soit 0 ou 2
//vrai si mur noir devant robot (tape)
bool verifieMursExt(){
  if(numColonne==directionRobot){
  return true;
  }
  else{
    return false;
  }
}

//vérifie quel sens tourner
//appel fct moteurs (fct)
//changer var direction
void tourner(){
  if(tourneGaucheDroite==1){
    //appelle fct moteur tourne droite
    directionRobot=directionRobot+1;
    tourneGaucheDroite=0;
  }
  else if(tourneGaucheDroite==0){
    //appelle fct moteur tourne gauche
    directionRobot=directionRobot-1;
    tourneGaucheDroite=1;
  }
}

//appel fct moteur avancer
//change var rangée et colonne dépendant orientation
void avancer(){
  //appeller fct moteur avancer
  if(directionRobot==0){
    numColonne = numColonne-1;
  }
  if(directionRobot==1){
    numRangee = numRangee+1;
  }
  if(directionRobot==2){
    numColonne = numColonne+1;
  }
  if(directionRobot==3){
    numRangee = numRangee-1;
  }
}