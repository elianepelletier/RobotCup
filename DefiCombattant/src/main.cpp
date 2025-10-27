#include <Arduino.h>
#include <LibRobus.h>
#include <libRobot.h>
void setup() {
  //initialize board
}

void loop()
{

 BoardInit();
 ENCODER_Reset(0);
 ENCODER_Reset(1);
 quille();
  //faire un while (autant et aussi longtemps que détecte pas de lumière, suive la ligne et avance)
  //quand sort du while, check quelle couleur (ou absence/couleur plancher?) et appel bonne méthode
  
}
/*
//fonction de départ lorsqu'il y a le carton bleu (petite danse)
void departDanseBleu(){

}

//fonction de départ lorsqu'il y a le carton rose (renverser la quille)
void departQuilleRose(){

}

//fonction de départ pour lorsqu'il y a le carton jaune (contourner mur)
void departMurJaune(){
    
}

//fonction de départ pour quand il n'y a plus de ligne (pas de couleur détectée)
void departRetrouverLigne(){

<<<<<<< Updated upstream
  int etat = 0; //Temporaire, Remplacer par les états de la fonction à Xavier
//etat = Lire etat de la fonction a xavier*********************************************************

//Suivre la ligne jusqu'à ce qu'on arrive à la ligne perpendiculaire de départ
  while (etat != 7){//etat tout allumés
    avance(1);//ou appeler la fonction suivre la ligne
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
          tourne(1,1);//Tourne vers la droite jusqu'à ce que les trois capteurs s'éteignent
          //etat = Lire etat de la fonction a xavier**************************************************
        }
        break;

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 0){
           tourne(1,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'éteignent
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
  avance(70);//Modifier cette valeur selon les tests

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
          tourne(1,1);//Tourne vers la droite jusqu'à ce que les trois capteurs s'allument
          //etat = appeler fonction de Xavier pour les etats**************************************************
        }
        break;

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 7){
           tourne(1,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'allument
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
=======
>>>>>>> Stashed changes
}
*/