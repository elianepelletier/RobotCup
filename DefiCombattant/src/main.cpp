#include <Arduino.h>
#include <libRobot.h>

void departMurJaune();
void departRetrouverLigneVert();

void setup() {
  //initialize board
  BoardInit();
}

void loop() {
  departMurJaune();
  while (true);  
  //faire un while (autant et aussi longtemps que détecte pas de lumière, suive la ligne et avance)
  //quand sort du while, check quelle couleur (ou absence/couleur plancher?) et appel bonne méthode
  
}

//fonction de départ lorsqu'il y a le carton bleu (petite danse)
void departDanseBleu(){
  //Départ
  tourne (45, 1);
  delay(50);
 
  avance (30);
  delay(50);
 
  tourne (90, 0);
  delay(50);
  
  avance (30);
  delay(50);
 
  tourne (90, 0);
  delay(50);
  
  avance (30);
  delay(50);
  
  tourne (90, 0);
  delay(50);

  avance (30);
  
  delay(200);
  //fin 

  // Retour sur la ligne 
  tourne (135, 0);
  

}

//fonction de départ lorsqu'il y a le carton rose (renverser la quille)
void departQuilleRose(){

}

//fonction de départ pour lorsqu'il y a le carton jaune (contourner mur)
void departMurJaune()
{
     // Avance 50 cm
  avance(10);

  // Tourne 90° à droite
  tourne(90, 1);

  // Avance 25 cm
  avance(25);

  // Tourne 90° à gauche
  tourne(90, 0);

  // Avance 25 cm pour contourner le mur
  avance(10);

   // Tourne 90° à gauche
  tourne(90, 0);

  // Avance 25 cm pour contourner le mur
  avance(10);

    // Tourne 90° à droite
  tourne(90, 1);
}

//fonction de départ lorsqu'il y a le carton vert (pour quand il n'y a plus de ligne)
void departRetrouverLigneVert(){

  int etat = 0; //Temporaire, Remplacer par les états de la fonction à Xavier

//etat = Lire etat de la fonction a xavier
//Suivre la ligne et réajuster jusqu'à ce que les trois capteurs allument
  while (etat != 7){//7 etat tout allume
    avance(1);//ou appeler la fonction suivre la ligne
    //etat = Lire etat de la fonction a xavier
  }

  //Salligner avec ligne perpendiculaire T
  while (etat == 7){
    avance(1);
  }
  while (etat != 0){
    switch (etat){
      case 0://tous eteints
        break;

      case 1://centre allumé
        avance(1);
        break;

      case 2://gauche allumé
        while(etat != 7){
          //recule en tournant droite
           // MOTOR_SetSpeed(RIGHT, 0);
          // MOTOR_SetSpeed(LEFT, 0.5*vitesse);
        }
      case 3://droite allumé
            while(etat != 7){
          //recule en tournant gauche
          // MOTOR_SetSpeed(RIGHT, 0.5*vitesse));
          // MOTOR_SetSpeed(LEFT, 0);
        }

      case 4://centre et gauche allumés
        tourne(1,1);//Tourne a droite
        break;

      case 5://centre et droite allumés
        tourne(1,0);//Tourne a gauche
        break;

      case 6://droite et gauche allumés
        break;

      case 7://tous allumés
        avance(1);
        break;
    }
    //etat = appeler fonction de Xavier pour les etats
  }

    //Avancer sans ligne
    avance(70);//Modifier cette valeur selon les tests

//Retrouver la ligne apres avoir traverse le trou
}
