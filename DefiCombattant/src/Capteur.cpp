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

uint16_t r, g, b, c;

/*void getrgb() {
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("R: ");
  Serial.print(r);
  Serial.print("  G: ");
  Serial.print(g);
  Serial.print("  B: ");
  Serial.print(b);
  Serial.print("  C: ");
  Serial.println(c);
}*/

int detectcouleur() {
  // Lire les données du capteur
  tcs.getRawData(&r, &g, &b, &c);  // utilise les variables globales

  // Affichage pour debug
  /*Serial.print("  R: "); Serial.print(r);
  Serial.print("  G: "); Serial.print(g);
  Serial.print("  B: "); Serial.print(b);
  Serial.print("  C: "); Serial.println(c);*/

  // Normalisation
  float somme = r + g + b;
  if (somme == 0) return -1; // éviter division par zéro

  float rn = (r / somme) * 255;
  float gn = (g / somme) * 255;
  float bn = (b / somme) * 255;

  Serial.print("  Rn: "); Serial.print(rn);
  Serial.print("  Gn: "); Serial.print(gn);
  Serial.print("  Bn: "); Serial.println(bn);
  
  // Comparaisons
  if (c > 500) {
    if (rn > 89.5 && gn < 89 && bn < 77) {
      Serial.println("Rouge");
      return 0; // Rouge
    } 
    else if (gn > 100 && rn < 78 && bn < 77) {
      Serial.println("Vert");
      return 1; // Vert
    } 
    else if (bn > 78.5 && rn < 79.75 && gn < 97) {
      Serial.println("Bleu");
      return 2; // Bleu
    } 
    else if (rn > 80 && gn > 95 && bn < 76) {
      Serial.println("Jaune");
      return 3; // Jaune
    }
    Serial.println("inconnu");
    return -1; // Inconnu
  }
  else {
    Serial.println("pas assez de lumiere");
    return -1; // Inconnu
  }
  return-1; // Inconnu
}

/*void rgbToHsv(int r, int g, int b, float *h, float *s, float *v) {
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
String detectColor(bool afficher) {
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

String detectColorHSV(bool afficher) {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    if (c < 500) {
        Serial.println("Trop sombre");
        return "Aucune couleur";
    }

    // Normalisation RGB
    float redNorm = (float)r / c;
    float greenNorm = (float)g / c;
    float blueNorm = (float)b / c;

    // Mise à l’échelle pour conversion HSV
    float R = redNorm * 255.0f;
    float G = greenNorm * 255.0f;
    float B = blueNorm * 255.0f;

    // Conversion en HSV
    float h, s, v;
    rgbToHsv(R, G, B, &h, &s, &v);

    // Affiche seulement HSV
    Serial.print("Hue: ");
    Serial.print(h, 1);
    Serial.print("  Sat: ");
    Serial.print(s * 100.0f, 1);
    Serial.print("%  Val: ");
    Serial.print(v * 100.0f, 1);
    Serial.println("%");

    return "";
}*/

//etat du capteur de suiveur de ligne
int detecteLigne() {
    // --- Lecture analogique des capteurs ---
    int gauche = analogRead(A2);
    int milieu = analogRead(A3);
    int droite = analogRead(A4);

    // --- Seuils de détection (à ajuster selon ton capteur et ton sol) ---
    int seuilNoir = 100;   // Valeur à ajuster : plus bas = plus sensible au noir

    // --- Détermination des états logiques (1 = blanc, 0 = ligne noire) ---
    bool Etatgauche = (gauche > seuilNoir);
    bool Etatmilieu = (milieu > seuilNoir);
    bool Etatdroite = (droite > seuilNoir);

    // --- Debug : affichage des valeurs ---
    Serial.print("G: "); Serial.print(gauche);
    Serial.print(" ("); Serial.print(Etatgauche); Serial.print(") ");
    Serial.print("M: "); Serial.print(milieu);
    Serial.print(" ("); Serial.print(Etatmilieu); Serial.print(") ");
    Serial.print("D: "); Serial.print(droite);
    Serial.print(" ("); Serial.println(Etatdroite); Serial.print(") ");

    // --- Logique de détection ---
    if (Etatmilieu == 0) {
        if (Etatdroite == 1 && Etatgauche == 1) return 1;
        if (Etatdroite == 0 && Etatgauche == 1) return 5;
        if (Etatdroite == 1 && Etatgauche == 0) return 4;
        if (Etatdroite == 0 && Etatgauche == 0) return 7;
    }

    if (Etatmilieu == 1) {
        if (Etatdroite == 1 && Etatgauche == 1) return 0;
        if (Etatdroite == 0 && Etatgauche == 1) return 3;
        if (Etatdroite == 1 && Etatgauche == 0) return 2;
        if (Etatdroite == 0 && Etatgauche == 0) return 6;
    }

    return -1; // aucun cas détecté
}

bool CapteurInit() {
  Serial.begin(9600);
  Serial.println("Initialisation du capteur TCS34725...");
  
  pinMode(47, INPUT);
  pinMode(48, INPUT);
  pinMode(49, INPUT);

  if (tcs.begin()) return true;
    /*Serial.println("Capteur détecté !");*/
    else return false;
    /*Serial.println("Capteur non détecté. Vérifie le câblage SDA/SCL.");*/
}
/*
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