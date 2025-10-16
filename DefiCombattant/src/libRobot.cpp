#include "libRobot.h"

float vitesse = 0.4; // vitesse par défaut

// conversion cm -> ticks encodeur
int cmToTicks(float cm) {
  return cm * 13581; // ajuster selon roue
}

// conversion angle -> ticks encodeur
int angleToTicks(float angle) {
  float distance = (angle / 360.0) * 0.195 * PI; // circonférence roue = 0.195 m
  return distance * 13581;
}

void avance(float cm) {
  int distanceTicks = cmToTicks(cm);
  int pv_left = ENCODER_Read(LEFT);
  int pv_right = ENCODER_Read(RIGHT);

  MOTOR_SetSpeed(LEFT, vitesse);
  MOTOR_SetSpeed(RIGHT, vitesse);

  while ((ENCODER_Read(LEFT) - pv_left < distanceTicks) && 
         (ENCODER_Read(RIGHT) - pv_right < distanceTicks)) {
    delay(10);
  }

  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
}

void tourne(float angle, int sens) {
  int distanceTicks = angleToTicks(angle);
  int pv_left = ENCODER_Read(LEFT);
  int pv_right = ENCODER_Read(RIGHT);

  if (sens == 1) { // droite
    MOTOR_SetSpeed(LEFT, vitesse);
    MOTOR_SetSpeed(RIGHT, -vitesse);
    while ((ENCODER_Read(LEFT) - pv_left < distanceTicks) &&
           (pv_right - ENCODER_Read(RIGHT) < distanceTicks)) {
      delay(10);
    }
  } else { // gauche
    MOTOR_SetSpeed(LEFT, -vitesse);
    MOTOR_SetSpeed(RIGHT, vitesse);
    while ((pv_left - ENCODER_Read(LEFT) < distanceTicks) &&
           (ENCODER_Read(RIGHT) - pv_right < distanceTicks)) {
      delay(10);
    }
  }

  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
}