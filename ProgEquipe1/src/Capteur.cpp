#include <Arduino.h>
#include <librobus.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

float VA10;

// Capteur avec 700ms d’intégration et gain 4x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_700MS,
  TCS34725_GAIN_4X
);

// --- Conversion RGB -> HSV ---
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

// --- Détection de la couleur dominante ---
String detectColor(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
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

  // Affinage selon la teinte
  if (h >= 180 && h <= 250 && s > 0.3) return "BLEU";          // 180°–250°
  if (h >= 40 && h <= 70 && s > 0.4) return "JAUNE";           // 40°–70°
  if ((h >= 300 || h <= 350) && s > 0.2) return "ROSE";        // 300°–350° ou proche de 0°
  
  return "Inconnu";
}

//etat du capteur de suiveur de ligne
int suiveurligne() {
    float Vout = VA10;
    if ( Vout < 1.675046505 && Vout > 1.175046505) {
        return 1;
    }
    if (Vout < 3.100109773 && Vout > 2.600109773) {
        return 2;
    }
    if (Vout < 0.980750083 && Vout > 0.480750083) {
        return 3;
    }
    if (Vout < 4.525156278 && Vout > 4.025156278) {
        return 4;
    }
    if (Vout < 2.405796588 && Vout > 1.905796588) {
        return 5;
    }
    if (Vout < 3.830859856 && Vout > 3.330859856) {
        return 6;
    }
    if (Vout > 4.755906361) {
        return 7;
    }
    else {
        return 0;    
    }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialisation du capteur TCS34725...");
  
  pinMode(A10,INPUT);

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

  VA10 = analogRead(A10);
  int etat = suiveurligne();

  delay(1000);
}
