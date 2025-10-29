#include <Arduino.h>
#include <librobus.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Capteur avec 700ms d’intégration et gain 4x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_700MS,
  TCS34725_GAIN_4X);

uint16_t r, g, b, c;

void getrgb() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("R: ");
  Serial.print(r);
  Serial.print("  G: ");
  Serial.print(g);
  Serial.print("  B: ");
  Serial.print(b);
  Serial.print("  C: ");
  Serial.println(c);
}
   
int detectcouleur(){
  //Normalisation pour éviter les différences dues à la luminosité
  float somme = r + g + b;
  float rn = (r / somme) * 255;
  float gn = (g / somme) * 255;
  float bn = (b / somme) * 255;

    //Comparaisons
  if (rn > 180 && gn < 100 && bn < 100) {
    return 0; //Rouge
  } 
  else if (gn > 160 && rn < 120 && bn < 120) {
    return 1; //Vert
  } 
  else if (bn > 160 && rn < 120 && gn < 120) {
    return 2; //Bleu
  } 
  else if (rn > 180 && gn > 160 && bn < 80) {
    return 3; //Jaune
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialisation du capteur TCS34725...");

  if (tcs.begin()) {
    Serial.println("Capteur détecté !");
  } else {
    Serial.println("Capteur non détecté. Vérifie le câblage SDA/SCL.");
    while (1);
  }
}

void loop() {
  getrgb();

  if (c < 500) {
    Serial.println("Aucune couleur détectée (trop sombre)");
    delay(1000);
    return;
  }
  else {
    int couleur = detectcouleur();
    Serial.print("Couleur : ");
    Serial.print(couleur);
    switch (couleur)
    {
    case 0: //
      /* code */
      break;
    
    case 1: //
      /* code */
      break;

    case 2: //
      /* code */
      break;
  
  case 3: //
      /* code */
      break;
     
    default:
      break;
    }
  }
}