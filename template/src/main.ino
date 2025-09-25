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
  // while(true){
    
  //   delay(1000);

  //   vert = digitalRead(vertpin);
  //   rouge = digitalRead(rougepin);

  //   Serial.print("Vert = ");
  //   Serial.println(vert);

  //   Serial.print("Rouge = ");
  //   Serial.println(rouge);
  //   if(vert == 1)
  //     avance();
  //   else
  //     arret();
  // }
    
  etatPast = etat;
  bumperArr = ROBUS_IsBumper(3);
  if (bumperArr){
    if (etat == 0){
      beep(1);
      etat = 1;
    } 
    else{
      beep(1);
      etat = 0;
    }
  }
  
  vert = digitalRead(vertpin);
  rouge = digitalRead(rougepin);
  if (etat > 0){
    if (vert && rouge){ // aucun obstacle => avance
      etat = 1;
      tourne2f = 0;
      // if (direction == 0){
      //   rangee ++;
      //   etat = 1;
      // }
      // else if(direction == 1){
      //   if(colonne!=2){
      //     colonne++;
      //     etat = 1;
      //   }
      //   else etat = 4;
      // }
      // else if(direction == 2){
      //   rangee--;
      // }
      // else if(direction == 3){
      //   if(colonne!=0){
      //     colonne--;
      //     etat = 1;
      //   }
      //   else etat = 3;
      // }

    }
    if (!vert && !rouge){  // obstacle devant 
      if(direction == 0 || direction == 3) //tourne droite lorsque N ou W
      {
        etat = 3;
        tourne2f = 1;
      }
      else if(direction == 1 || direction == 2) //tourne gauche lorsque S ou E
      {
        etat = 4;
        tourne2f = 1;
      }
    }
    
  }

  if (etatPast != etat){
    arret();
    delay(50);
  }
  else{
    switch (etat)
    {
    case 0:
      arret();
      break;
    case 1:
      avance();
      break;
    case 2:
      recule();
      break;
    case 3:
      tourneDroit(); 
      delay(1200);
      if(direction != 3)
        direction++;
      else 
        direction = 0;
      
      if(tourne2f == 1){
          tourneDroit(); 
        delay(1200);
        if(direction != 3)
          direction++;
        else 
          direction = 0;
      }
      break;

    case 4:
      tourneGauche();
      delay(1200);
      if(direction != 0)
        direction--;
      else 
        direction = 3;
      if(tourne2f == 1){
        tourneGauche(); 
        delay(1200);
        if(direction != 3)
          direction++;
        else 
          direction = 0;
      }
      break;            
    default:
      avance();
      etat = 1;
    
    break;
    }
  }
  delay(200);
}
