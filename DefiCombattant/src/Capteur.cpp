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
    else if (bn > 78.5 && rn < 79.75 && gn < 97) {//(rn >= 77.0 && rn <= 77.5 && gn >= 96.9 && gn <= 97.1 && bn >= 78.5 && bn <= 81.1)
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

void SuivreLigneContinu()
{
    int g = analogRead(A2);
    int m = analogRead(A3);
    int d = analogRead(A4);

    // Seuils adaptés à tes mesures
    int seuilGauche = 300;
    int seuilMilieu = 300;
    int seuilDroite = 500;

    // États logiques : 0 = noir détecté, 1 = blanc
    bool EtatG = (g > seuilGauche);
    bool EtatM = (m > seuilMilieu);
    bool EtatD = (d > seuilDroite);

    // ---- DEBUG ----
    Serial.print("G: "); Serial.print(g); 
    Serial.print(" ("); Serial.print(EtatG); Serial.print(") ");
    Serial.print("M: "); Serial.print(m); 
    Serial.print(" ("); Serial.print(EtatM); Serial.print(") ");
    Serial.print("D: "); Serial.print(d); 
    Serial.print(" ("); Serial.print(EtatD); Serial.print(") ");

    // Calcul de l'état global
    int etat = -1;

    if (EtatM == 0) {
        if (EtatD == 1 && EtatG == 1) etat = 1;  // Milieu seulement
        if (EtatD == 0 && EtatG == 1) etat = 5;  // Milieu + Droite
        if (EtatD == 1 && EtatG == 0) etat = 4;  // Milieu + Gauche
        if (EtatD == 0 && EtatG == 0) etat = 7;  // Tous sur la ligne
    } 
    else if (EtatM == 1) {
        if (EtatD == 1 && EtatG == 1) etat = 0;  // Rien détecté
        if (EtatD == 0 && EtatG == 1) etat = 3;  // Droite seulement - LÉGÈREMENT OFF
        if (EtatD == 1 && EtatG == 0) etat = 2;  // Gauche seulement - LÉGÈREMENT OFF
        if (EtatD == 0 && EtatG == 0) etat = 6;  // Gauche + Droite seulement
    }

    Serial.print(" -> État global : ");
    Serial.println(etat);

    // ---- CONTRÔLE DES MOTEURS ----
    float vitesseBase = 0.15;
    float correctionLegere = 0.03;
    float correctionForte = 0.10;  // Correction plus agressive pour cas extrêmes

    // Démarrage ou rien détecté → avance droit
    if (etat == -1 || etat == 0 || etat == 1) {
        MOTOR_SetSpeed(0, vitesseBase);
        MOTOR_SetSpeed(1, vitesseBase);
    }
    // --- CAS EXTRÊMES: Ligne très à gauche (seulement droite détecte) ---
    else if (etat == 3) {
        // Tourne fort à gauche pour rattraper
        MOTOR_SetSpeed(0, vitesseBase - correctionForte);
        MOTOR_SetSpeed(1, vitesseBase + correctionForte);
    }
    // --- CAS EXTRÊMES: Ligne très à droite (seulement gauche détecte) ---
    else if (etat == 2) {
        // Tourne fort à droite pour rattraper
        MOTOR_SetSpeed(0, vitesseBase + correctionForte);
        MOTOR_SetSpeed(1, vitesseBase - correctionForte);
    }
    // Légèrement à gauche (milieu + droite)
    else if (etat == 5) {
        MOTOR_SetSpeed(0, vitesseBase - correctionLegere);
        MOTOR_SetSpeed(1, vitesseBase + correctionLegere);
    }
    // Légèrement à droite (milieu + gauche)
    else if (etat == 4) {
        MOTOR_SetSpeed(0, vitesseBase + correctionLegere);
        MOTOR_SetSpeed(1, vitesseBase - correctionLegere);
    }
    // Tout noir ou tout blanc → avance lentement (stabilisation)
    else if (etat == 6 || etat == 7) {
        MOTOR_SetSpeed(0, 0.20);
        MOTOR_SetSpeed(1, 0.20);
    }
}

int lireEtatLigne() {
    int g = analogRead(A2);
    int m = analogRead(A3);
    int d = analogRead(A4);

    // seuils ajustables
    int seuilG = 200;
    int seuilM = 300;
    int seuilD = 700;

    bool EtatG = (g > seuilG);
    bool EtatM = (m > seuilM);
    bool EtatD = (d > seuilD);

    int etat = -1;

    if (EtatM == 0) {
        if (EtatD == 1 && EtatG == 1) etat = 1;
        if (EtatD == 0 && EtatG == 1) etat = 5;
        if (EtatD == 1 && EtatG == 0) etat = 4;
        if (EtatD == 0 && EtatG == 0) etat = 7;
    } 
    else if (EtatM == 1) {
        if (EtatD == 1 && EtatG == 1) etat = 0;
        if (EtatD == 0 && EtatG == 1) etat = 3;
        if (EtatD == 1 && EtatG == 0) etat = 2;
        if (EtatD == 0 && EtatG == 0) etat = 6;
    }

    return etat;
}