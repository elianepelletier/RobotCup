#include <Arduino.h>
#include <LibRobus.h>
#include <libRobot.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Capteur.h>
#include <SuiveurDeLigne.h>

#define PIN_ROUGE 40
#define PIN_JAUNE 41
#define PIN_VERT 42
#define PIN_BLEUE 43
int Etat;

void departDanseBleu();
void departMurJaune();
void departQuilleRose();
void allumeDel(int pin);
void setup() {
  //initialize board
  Serial.begin(9600);
  BoardInit();
  CapteurInit();
  if (CapteurInit()) {
    Serial.println("Capteur détecté !");
    while(1);
  }
  else Serial.println("Capteur non détecté. Vérifie le câblage SDA/SCL.");
}

void loop()
{

  //departMurJaune();
  //delay(5000);
  //departDanseBleu();
  //delay(5000);
  //String couleur = detectColorHSV(true);
  //Etat = detecteLigne();
  //Suislaligne(Etat);
 
  delay(2000);

  //departQuilleRose();
  //quille();
  //faire un while (autant et aussi longtemps que détecte pas de lumière, suive la ligne et avance)
  //quand sort du while, check quelle couleur (ou absence/couleur plancher?) et appel bonne méthode
  
}

//fonction de départ lorsqu'il y a le carton bleu (petite danse)
void departDanseBleu(){
  allumeDel(PIN_BLEUE);
  //Départ
  tourne (45, 1);
  delay(300);
 
  avance (30);
  delay(150);
 
  tourne (90, 0);
  delay(150);
  
  avance (30);
  delay(150);
 
  tourne (90, 0);
  delay(150);
  
  avance (30);
  delay(150);
  
  tourne (90, 0);
  delay(150);

  avance (30);
  
  delay(150);
  //fin 

  // Retour sur la ligne 
  tourne (135, 0);

}

//fonction de départ lorsqu'il y a le carton rose (renverser la quille)
void departQuilleRose()
{
  allumeDel(PIN_ROUGE);
  ENCODER_Reset(1);
  ENCODER_Reset(0);
  quille();
}

//fonction de départ pour lorsqu'il y a le carton jaune (contourner mur)
void departMurJaune() {
    allumeDel(PIN_JAUNE);
    avance(10);
    delay(150);

    tourne(90, true);   // droite = true ?
    delay(150);

    avance(45);
    delay(150);

    tourne(90, false);  // gauche
    delay(150);

    avance(40);
    delay(150);

    tourne(90, false);  // gauche
    delay(150);

    avance(45);
    delay(150);

    tourne(90, true);   // droite
    delay(150);
}


//fonction de départ pour quand il n'y a plus de ligne (pas de couleur détectée)
void departRetrouverLigne(){
  allumeDel(PIN_VERT);

  int etat = 0; //Temporaire, Remplacer par les états de la fonction à Xavier
//etat = Lire etat de la fonction a xavier*********************************************************

//Suivre la ligne jusqu'à ce qu'on arrive à la ligne perpendiculaire de départ
  while (etat != 7){//etat tout allumés
    avance(1);//ou appeler la fonction suivre la ligne*********************************************
    //etat = Lire etat de la fonction a xavier*****************************************************
  }

  //Traverser la ligne perpendiculaire de départ
  while (etat == 7){//avance tant que les trois capteurs détectent la ligne
    avance(1);
    //etat = Lire etat de la fonction a xavier*****************************************************
  }

  //Ajuster la direction du robot avant d'avancer de 75cm
  while (etat != 0){//avancer jusqu'à ce qu'on perd la ligne perpendiculaire complètement
    switch (etat){

      case 0://tous eteints
        avance(1);
        break;

      case 1://centre allumé
        avance(1);
        break;

      case 2://gauche allumé
      case 4://centre et gauche allumés
        while(etat != 0){
          tourne(10,1);//Tourne vers la droite jusqu'à ce que les trois capteurs s'éteignent
          //etat = Lire etat de la fonction a xavier**************************************************
        }
        break;

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 0){
           tourne(10,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'éteignent
           //etat = Lire etat de la fonction a xavier**************************************************
        }
        break;

      case 6://droite et gauche allumés
        avance(1);
        break;

      case 7://tous allumés
        avance(1);
        break;
    }
    //etat = appeler fonction de Xavier pour les etats**************************************************
  }

  //Avancer longue distance sans ligne
  avance(140);//Modifier cette valeur selon les tests
  delay(50);

  //Retrouver la ligne perpendiculaire d'arrivée apres avoir traversé le trou
  while(etat == 0){//Tous éteintes, n'a pas encore retrouvé la ligne
    avance(1);
    //etat = appeler fonction de Xavier pour les etats**************************************************
  }

  //Ajuster la direction du robot avec la ligne perpendiculaire d'arrivée
  while(etat != 7){
    switch (etat){
      
      case 0://tous éteints
        avance(1);
        break;

      case 1://centre allumé
        avance(1);
        break;
      
      case 2://gauche allumé
      case 4://centre et gauche allumés
        while(etat != 7){
          tourne(10,1);//Tourne vers la droite jusqu'à ce que les trois capteurs s'allument
          //etat = appeler fonction de Xavier pour les etats**************************************************
        }
        break;

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 7){
           tourne(10,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'allument
           //etat = appeler fonction de Xavier pour les etats**************************************************
        }
        break;

    case 6://droite et gauche allumés
      avance(1);
      break;

    case 7://tous allumés
      avance(1);
      break;

    }
     //etat = appeler fonction de Xavier pour les etats****************************************************************
  }

  //Traverser la ligne perpendiculaire d'arrivée
  while (etat == 7){
    avance(1);
    //etat = appeler fonction de Xavier pour les etats******************************************************************
  }

  //Suivre la ligne ou retrouver la ligne si perdue
  if (etat !=0){
    //Appeler la fonction suivre la ligne de Xavier********************************************************************
  }

  else{
    //Essayer de chercher et trouver la ligne
  }
}

void readcapteurSLL(){
  // Lire l'état des capteurs
  int test = suiveurligne();

  // Affichage des informations
  Serial.print("Etat du suiveur de ligne : ");
  Serial.println(test);

  // Optionnel : détail des capteurs
  Serial.print("Capteur Gauche: ");
  Serial.print(digitalRead(39));
  Serial.print("  Milieu: ");
  Serial.print(digitalRead(40));
  Serial.print("  Droite: ");
  Serial.println(digitalRead(41));

  /*// Ajustement moteur (si tu veux tester le suivi en même temps)
  Etat = etat;       // mettre à jour la variable globale
  Suislaligne();     // ajuste les moteurs selon l'état*/

  delay(500); // un petit délai pour lecture lisible
}

void allumeDel(int pin){
  digitalWrite(pin, HIGH);
  delay(2000);
  digitalWrite(pin, LOW);
}