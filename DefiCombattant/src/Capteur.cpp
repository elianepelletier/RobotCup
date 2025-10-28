#include <Arduino.h>
#include <librobus.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "Capteur.h"

// Capteur avec 700ms d’intégration et gain 4x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_700MS,
  TCS34725_GAIN_4X
);

// Conversion RGB to HSV
void rgbToHsv(int r, int g, int b, float *h, float *s, float *v) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    float cmax = max(rf, max(gf, bf));
    float cmin = min(rf, min(gf, bf));
    float delta = cmax - cmin;

    // Calcul de la teinte (Hue)
    if (delta == 0)
        *h = 0;
    else if (cmax == rf)
        *h = fmod(((gf - bf) / delta), 6.0);
    else if (cmax == gf)
        *h = ((bf - rf) / delta) + 2.0;
    else
        *h = ((rf - gf) / delta) + 4.0;

    *h *= 60;
    if (*h < 0) *h += 360;

    // Saturation et valeur
    *s = (cmax == 0) ? 0 : delta / cmax;
    *v = cmax;
}

// Détection de la couleur dominante
String detectColor(bool afficher = 0) {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    
    if (c < 500) return "Aucune couleur (trop sombre)";

    // Normalisation RGB
    float redNorm = (float)r / c;
    float greenNorm = (float)g / c;
    float blueNorm = (float)b / c;

    int R = redNorm * 255;
    int G = greenNorm * 255;
    int B = blueNorm * 255;

    // Conversion en HSV
    float h, s, v;
    rgbToHsv(R, G, B, &h, &s, &v);

    if (afficher) {
        Serial.print("R: "); Serial.print(r);
        Serial.print(" G: "); Serial.print(g);
        Serial.print(" B: "); Serial.print(b);
        Serial.print(" C: "); Serial.println(c);

        Serial.print("Hue: "); Serial.print(h);
        Serial.print(" Sat: "); Serial.print(s);
        Serial.print(" Val: "); Serial.println(v);
    }

    // Affinage selon la teinte
    if (h >= 180 && h <= 250 && s > 0.3) return "BLEU";          // 180°–250°
    if (h >= 40 && h <= 70 && s > 0.4) return "JAUNE";           // 40°–70°
    if ((h >= 300 || h <= 350) && s > 0.2) return "ROSE";        // 300°–350° ou proche de 0°
    
    return "Inconnu";
}

//etat du capteur de suiveur de ligne
int suiveurligne() {
    bool Etatgauche = digitalRead(39);
    bool Etatmilieu = digitalRead(40);
    bool Etatdroite = digitalRead(41);

    if ( Etatmilieu == 0) {
        if (Etatdroite == 1 && Etatgauche == 1) {
        return 1;
        }

        if (Etatdroite == 0 && Etatgauche == 1) {
        return 5;
        }
        
        if (Etatdroite == 1 && Etatgauche == 0) {
        return 4;
        }

        if (Etatdroite == 0 && Etatgauche == 0) {
        return 7;
        }

    }

    if ( Etatmilieu == 1) {
        if (Etatdroite == 1 && Etatgauche == 1) {
        return 0;
        }
        if (Etatdroite == 0 && Etatgauche == 1) {
        return 3;
        }
        if (Etatdroite == 1 && Etatgauche == 0) {
        return 2;
        }
        if (Etatdroite == 0 && Etatgauche == 0) {
        return 6;
        }

    }

  return -1;
}
/*
void setup() {
  Serial.begin(9600);
  Serial.println("Initialisation du capteur TCS34725...");
  
  pinMode(39, INPUT);
  pinMode(40, INPUT);
  pinMode(41, INPUT);

  if (tcs.begin()) {
    Serial.println("Capteur détecté !");
  } else {
    Serial.println("Capteur non détecté. Vérifie le câblage SDA/SCL.");
    while (1);
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  String couleur = detectColor(r, g, b, c);

  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" C: "); Serial.print(c);
  Serial.print("  => Couleur détectée : ");
  Serial.println(couleur);

  Etat = suiveurligne();

  delay(1000);
}
*/