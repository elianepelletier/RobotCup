#include <Arduino.h>
#include <LibRobus.h>
#include <math.h>
#include <stdio.h>

float Q=0; // encodeur gauhce
float K=0; // encodeur droit
float H=0;
float pulse_scan=0;
int   PULSE_90=1932; // virage de 90 degre
int   PULSE_360=7728;
int   PULSE_180=3864;
int   PULSE_270=5796;
float V=0.35;

void TournerDroite90_PROVISOIRE()
{
    
    ENCODER_Reset(0);
    ENCODER_Reset(1);

    
    MOTOR_SetSpeed(0, V);   
    MOTOR_SetSpeed(1, -V);  

    while (fabs(ENCODER_Read(0)) < PULSE_90 && fabs(ENCODER_Read(1)) < PULSE_90)
    {
       
    }

    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
}


void TournerGauche90_PROVISOIRE()
{
    
    ENCODER_Reset(0);
    ENCODER_Reset(1);

    MOTOR_SetSpeed(0, -V);  
    MOTOR_SetSpeed(1, V);  

    while (fabs(ENCODER_Read(0)) < PULSE_90 && fabs(ENCODER_Read(1)) < PULSE_90)
    {
       
    }

    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);


}
void GAUCHE_360_scan(void) // on scan ou est la quille
{

  while ((((fabs(ENCODER_Read(0))) + (fabs(ENCODER_Read(1))))/2) < PULSE_360)
  {
      
    MOTOR_SetSpeed(0, -V);
    MOTOR_SetSpeed(1, V);
       
    
    if (ROBUS_ReadIR(0) > 150) //  A CALIBRER detecte qqch stop lorsque le capteur donne une valeur plus haute que 0.6V !!conversion volt en bits maybe!!
    {
      MOTOR_SetSpeed(0, 0.0);
      MOTOR_SetSpeed(1, 0.0);
      K =fabs(ENCODER_Read(1));
      Q =fabs(ENCODER_Read(0)); 
      pulse_scan = ((K+Q)/2);
      break;
    }
  }
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}

// go foward pour fair tomber la quille
void  REACH_the_quille(void)
{
    ENCODER_Reset(0);
    ENCODER_Reset(1);

  while( (fabs(ENCODER_Read(0))+fabs(ENCODER_Read(1)))/2 < 3500 ) 
  {
  MOTOR_SetSpeed(0, V);
  MOTOR_SetSpeed(1, V);
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);

}


// on fait spinner le robot (attack)
void  Kill_the_quille(void )           
{
       
   ENCODER_Reset(0);
   ENCODER_Reset(1);
   delay(50);
   float reste_pour_X;

    // On calcule la distance la plus courte vers l'axe X (0 ou 8124/2)
    if (pulse_scan < PULSE_360 / 2.0)
    {
        reste_pour_X = (PULSE_360 / 2.0) - pulse_scan;
    }
    else
    {
        reste_pour_X = PULSE_360 - pulse_scan; // tourner dans l'autre sens
    }
    while (((fabs(ENCODER_Read(0)) + fabs(ENCODER_Read(1)))/2) < reste_pour_X)
    {

        MOTOR_SetSpeed(1, V);
        MOTOR_SetSpeed(0, -V);
    }


    MOTOR_SetSpeed(1, 0);
    MOTOR_SetSpeed(0, 0);
    TournerGauche90_PROVISOIRE();
}


void Leave_the_quille(void)   
{
    MOTOR_SetSpeed(0, V);
    MOTOR_SetSpeed(1, V);
    delay(2500);
        while (((fabs(ENCODER_Read(0)) + fabs(ENCODER_Read(1))) / 2.0) < 3200) ///////modifier pour detecteur de ligne
    {
        MOTOR_SetSpeed(0, V);
        MOTOR_SetSpeed(1, V);
    }


    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
    delay(250);

    float angle_actuel = (Q + K) / 2.0; 
    if (angle_actuel >= 0 && angle_actuel <= PULSE_180)  
    {
        TournerGauche90_PROVISOIRE();
    }
    
    else
    {
        TournerDroite90_PROVISOIRE();
    }

}


void BACK_ON_TRACK (void)   
{

    if (((K+Q)/2) < PULSE_180)  // gauche du cercle trigo -> virage vers la gauche pour continuer dans le bon sens

        {
            TournerGauche90_PROVISOIRE();
        }

    if (((K+Q)/2) > PULSE_180) // droite du cercle trigo -> virage vers la droite pour continuer dans le bon sens

        {
           TournerDroite90_PROVISOIRE();
        }
}



void TOURCOMPLET_CALIBRATION(void)
/* En théorie un tour complet d'evrait être 8124 pulse cependant, en pratique c pas la même ces fonction sera utiliser pour calibrer le code sera ajusté après*/
{

    while (((fabs(ENCODER_Read(0)))+(fabs(ENCODER_Read(1)))/2) <PULSE_360)
    {
        MOTOR_SetSpeed(1, V);
        MOTOR_SetSpeed(0, -V);
    }
}




void quille(void)
{

    ENCODER_Reset(0);
    ENCODER_Reset(1);

    delay(500);

    GAUCHE_360_scan();

    delay(500);

    REACH_the_quille();

    delay(500);

    Kill_the_quille();

    delay(500);

    Leave_the_quille();

    delay(500);

}




