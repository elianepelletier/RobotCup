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

//fonction de départ lorsqu'il y a le carton vert (quand il n'y a plus de ligne)
void departRetrouverLigneVert(){

  int etat = 0; //Temporaire, Remplacer par les états de la fonction à Xavier
//etat = Lire etat de la fonction a xavier

//Suivre la ligne jusqu'à ce qu'on arrive à la ligne perpendiculaire de départ
  while (etat != 7){//etat tout allumés
    avance(1);//ou appeler la fonction suivre la ligne
    //etat = Lire etat de la fonction a xavier
  }

  //Traverser la ligne perpendiculaire de départ
  while (etat == 7){//avance tant que les trois capteurs détectent la ligne
    avance(1);
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
          break;
        }

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 0){
           tourne(1,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'éteignent
           break;
        }

      case 6://droite et gauche allumés
        avance(1);
        break;

      case 7://tous allumés
        avance(1);
        break;
    }
    //etat = appeler fonction de Xavier pour les etats
  }

    //Avancer longue distance sans ligne
    avance(70);//Modifier cette valeur selon les tests

  //Retrouver la ligne perpendiculaire d'arrivée apres avoir traversé le trou
  while(etat == 0){//Tous éteintes, n'a pas encore retrouvé la ligne
    avance(1);
    //etat = appeler fonction de Xavier pour les etats
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
          break;
        }

      case 3://droite allumé
      case 5://centre et droite allumés
        while(etat != 7){
           tourne(1,0);//Tourne vers la gauche jusqu'à ce que les trois capteurs s'allument
           break;
        }

    case 6://droite et gauche allumés
      avance(1);
      break;

    case 7://tous allumés
      avance(1);
      break;

    }
     //etat = appeler fonction de Xavier pour les etats
  }

  //Traverser la ligne perpendiculaire d'arrivée
  while (etat == 7){
    avance(1);
    //etat = appeler fonction de Xavier pour les etats
  }

  //Suivre la ligne ou retrouver la ligne si perdue
  if (etat !=0){
    //Appeler la fonction suivre la ligne de Xavier
  }

  else{
    //Essayer de chercher et trouver la ligne
  }
}
