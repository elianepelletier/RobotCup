#include <Arduino.h>
#include <libRobot.h>

void departMurJaune();

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

  //DEL eteintes
 /* int rouge = 0;
  int jaune = 0;
  int bleu = 0;
  if (rouge == 0 && jaune == 0 && bleu == 0 ){
    //En train de tester le push
  }*/
}