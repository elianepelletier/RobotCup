/*
Projet: Labyrinth
Equipe: RobotCUP
Auteurs: Xavier Boutet
Description: moteur vers l'avant
Date: 2025-09-25
*/

#include <LibRobus.h>
#include <math.h>

bool bumperArr;
int vertpin = 48;
int rougepin = 49;
bool vert = false;
bool rouge = false;
int etat = 0; // = 0 arrêt 1 = avance 2 = recule 3 = TourneDroit 4 = TourneGauche
int etatPast = 0;
float CO1; // Output du controleur pour le moteur de gauche
float CO2; // Output du controleur pour le moteur de droite
int PV_1;      // mesure
float error1;   // erreur instantanée
float integral1 = 0; // mémoire de l'erreur
double Kp=0.00000001, Ki=0.0000000000001; //Kp=0.0000001, Ki=0.000000000001;Kp=0.0001, Ki=0.0000001; 
float dt = 0.001; // période d'échantillonnage en secondes
int PV_2;      // mesure
float error2;   // erreur instantanée
float integral2 = 0; // mémoire de l'erreur
float P_gauche;
float P_max_gauche;
float P_droite;
float P_max_droite;
float distance;
float distance1;
float distance2;
int Pos1;
float erreurDiff;
static float integralDiff;
float Kp_sync = 0.000125; 
float Ki_sync = 0.00005;
float Cor_CO;
float CO1_prev;
float CO2_prev;
float ramp_max;
float angle;

void P_RST_encodeur_1(){
  ENCODER_ReadReset(LEFT);
}

int P_PV_encodeur_1(void){
  return ENCODER_Read(LEFT);
}

void P_RST_encodeur_2(){
  ENCODER_ReadReset(RIGHT);
}

int P_PV_encodeur_2(void){
  return ENCODER_Read(RIGHT);
}

void startMove() {
    // Reset encodeurs au début du mouvement
    P_RST_encodeur_1();
    P_RST_encodeur_2();
    delay(10);

    // Reset intégrales PID si besoin
    integral1 = 0;
    integral2 = 0;
    integralDiff = 0;
}

void PIDposition1(float SetPoint1,int PV1, float ramp_max){
  error1 = (SetPoint1 * 13581) - PV1;
  integral1 += error1 * dt;
  CO1 = ((Kp * error1 + Ki * integral1))/((Kp * SetPoint1 * 13581 + Ki * SetPoint1 * 13581));
  if(CO1 < 0.05 ) {
    CO1 = 0;
  }
  if(CO1 > 1) {
    CO1 = 1;
  }
  if( 0.05 <= CO1 && CO1 < 0.1 ) {
    CO1 = 0.1;
  }
  if (CO1 - CO1_prev > ramp_max) {
    CO1 = CO1_prev + ramp_max;
  }

  CO1_prev = CO1;
}

void PIDposition2(float SetPoint2, int PV2, float ramp_max){
  error2 = (SetPoint2 * 13581) - PV2;
  integral2 += error2 * dt;
  CO2 = ((Kp * error2 + Ki * integral2))/((Kp * SetPoint2 * 13581 + Ki * SetPoint2 * 13581));
  if(CO2 < 0.05 ) {
    CO2 = 0;
  }
  if(CO2 > 1) {
    CO2 = 1;
  }
  if( 0.05 <= CO2 && CO2 < 0.1 ) {
    CO2 = 0.1;
  }
  if (CO2 - CO2_prev > ramp_max) {
    CO2 = CO2_prev + ramp_max;
  }

  CO2_prev = CO2;
}

void beep(int count){
  for(int i=0;i<count;i++){
    AX_BuzzerON();
    delay(100);
    AX_BuzzerOFF();
    delay(100);  
  }
  delay(400);
}

void avance(){
  distance = 0.5;
  distance2 = distance * 13581;
  PV_1 = P_PV_encodeur_1();
  PV_2 = P_PV_encodeur_2();
  ramp_max = 0.75;
  while (distance2 > PV_2)
  {
    delay(10);
    PIDposition1(distance,PV_1,ramp_max);
    PIDposition2(distance,PV_2,ramp_max);
    delay(10);
    MOTOR_SetSpeed(RIGHT, CO2);
    MOTOR_SetSpeed(LEFT, CO1);
    PV_1 = ENCODER_Read(LEFT);
    PV_2 = ENCODER_Read(RIGHT);
  } 
}

void arret(){
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
}

/*void recule(){
  distance = 0.5;
  ramp_max = 0.75;
  P_RST_encodeur_1();
  P_RST_encodeur_2();
  PV_1 = P_PV_encodeur_1();
  PV_2 = P_PV_encodeur_2();
  PIDposition1(distance,PV_1,ramp_max);
  PIDposition2(distance,PV_2,ramp_max);
  MOTOR_SetSpeed(RIGHT, -CO2);
  MOTOR_SetSpeed(LEFT, -CO1);
}*/

void tourneGauche(){
  angle = 90.0;
  distance = (angle/360.0)*0.195*PI;
  distance2 = distance * 13581;
  P_RST_encodeur_1();
  P_RST_encodeur_2();
  PV_1 = 0;
  PV_2 = 0;
  ramp_max = 0.15;
  while (distance2 >= PV_2)
  {
    delay(10);
    PIDposition1(distance,-1*PV_1,ramp_max);
    PIDposition2(distance,PV_2,ramp_max);
    delay(10);
    MOTOR_SetSpeed(RIGHT, 1*CO2);
    MOTOR_SetSpeed(LEFT, -1*CO1);
    PV_1 = ENCODER_Read(LEFT);
    PV_2 = ENCODER_Read(RIGHT);
  } 
}

void tournedroit(){
  angle = 90.0;
  distance = (angle/360.0)*0.195*PI;
  distance2 = distance * 13581;
  P_RST_encodeur_1();
  P_RST_encodeur_2();
  PV_1 = 0;
  PV_2 = 0;
  ramp_max = 0.15;
  while (distance2 >= PV_1)
  {
    delay(10);
    PIDposition2(distance,-1*PV_2,ramp_max);
    PIDposition1(distance,PV_1,ramp_max);
    delay(10);
    MOTOR_SetSpeed(LEFT, CO1);
    MOTOR_SetSpeed(RIGHT, -1*CO2);
    PV_2 = ENCODER_Read(RIGHT);
    PV_1 = ENCODER_Read(LEFT);
  } 
}

void tournedemilune(){
  angle = 192;
  distance = (angle/360.0)*0.195*PI;
  distance2 = distance * 13581;
  P_RST_encodeur_1();
  P_RST_encodeur_2();
  PV_1 = 0;
  PV_2 = 0;
  ramp_max = 0.15;
  while (distance2 >= PV_2)
  {
    delay(10);
    PIDposition1(distance,-1*PV_1,ramp_max);
    PIDposition2(distance,PV_2,ramp_max);
    delay(10);
    MOTOR_SetSpeed(RIGHT, CO2);
    MOTOR_SetSpeed(LEFT, -1*CO1);
    PV_1 = ENCODER_Read(LEFT);
    PV_2 = ENCODER_Read(RIGHT);
  }
}

void setup(){
  BoardInit();

  Serial.begin(9600);

  //initialisation
  pinMode(vertpin, INPUT);
  pinMode(rougepin, INPUT);
  delay(100);
  
}

void loop() {
  delay(1000);
  startMove();
  tournedemilune();
  delay(10000);
  startMove();
  tournedemilune();
  delay(1000000000);
}