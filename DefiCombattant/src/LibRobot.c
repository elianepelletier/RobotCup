#include <Arduino.h>
#include <LibRobus.h>

float Q=0;
float K=0;
float H=0;

//d/tecteur infrarouge

void quille(void)
{
    ENCODER_ReadReset(0);
    ENCODER_ReadReset(1);

}

void GAUCHE_360_scan() //  180 du au 90 a droite
{
    
    
    while ( ENCODER_Read(0) < 8124 && ENCODER_Read(1) < 8124) 
    {
    {
        MOTOR_SetSpeed(0, -0.15);
        MOTOR_SetSpeed(1, +0.15);
    
    }
    if( ROBUS_ReadIR(0)> 0 ) // d/tecte qqch stop
    {
       
        MOTOR_SetSpeed(0, 0.0);
        MOTOR_SetSpeed(1, 0.0);
        K=ENCODER_ReadReset(1);
        Q=ENCODER_ReadReset(0);
    }
    }

}

// go foward -> kill the quille :p
void  REACH_the_quille(void )
{
    MOTOR_SetSpeed(0, 0.15);
    MOTOR_SetSpeed(1, 0.15);

        if ( ROBUS_ReadIR(0)> /*plus grand que3 a 4 cm (distance entre robot et qu<ille)*/) 
        {
            MOTOR_SetSpeed(0, 0.15);
            MOTOR_SetSpeed(1, 0.15);
            // on deploi le bras

            SERVO_Enable(0);
            SERVO_SetAngle(0, 90);
            H=(ENCODER_Read(0)+ENCODER_Read(1))/2;
         
        }

         break;
}


// on fait spinner le robot (attack)
void  Kill_the_quille(void )  


    {
       
        ENCODER_Reset(0);
        ENCODER_Reset(1);
        delay(500);

        // on complete la rotation au complet
        for (int i; 8124 > (i + (K+Q)/2); i+=10)
        {

        MOTOR_SetSpeed(1, 0.15);
        MOTOR_SetSpeed(0, -0.15);
        }
        MOTOR_SetSpeed(1, 0);
        MOTOR_SetSpeed(0, 0);
        SERVO_SetAngle(0,90);
        SERVO_Disable(0);
        
    }





void Leave_the_quille(void)
{
    MOTOR_SetSpeed(0, 0.15);
    MOTOR_SetSpeed(1, 0.15);

    if (ENCODER_Read(0) >= H && ENCODER_Read(1) <= H)
        {
        MOTOR_SetSpeed(1, 0);
        MOTOR_SetSpeed(0, 0);
        delay(500);
        }

}






void BACK_ON_TRACK (void)   
{
        if ( )






}


{

   /* // determiner le cadrant cercle trigo
    if (4062=>z>0)
    {
        while (ENCODER_Read(0)> &&)
    MOTOR_SetSpeed(0, 0.15);
    MOTOR_SetSpeed(1. -0.15);
    }
    if (8124=>z>4062)
        






 MOTOR_SetSpeed(0,0)
 MOTOR_SetSpeed(1,0)
 ENCODER_ReadReset(0)
 ENCODER_ReadReset(1)
        

/*
// go foward 12.5 cm 1/4 de 50 cm

    MOTOR_SetSpeed(0, 0.3);
    MOTOR_SetSpeed(1, 0.3);

    if (ENCODER_Read(0) > 848 && ENCODER_Read(1) > 848)
{
    MOTOR_SetSpeed(0, 0);
    MOtOR_SetSpeed(1, 0);
      // suite des fonctions

    //DROITE_90_scan
 ENCODER_ReadReset(0)
 ENCODER_ReadReset(1)
}
*/

/*
void DROITE_90_scan(float vitesse)
{

    while ( ENCODER_Read(0) < 2031 && ENCODER_Read(1) < 2031) 
    {
        MOTOR_SetSpeed(0, 0.15);
        MOTOR_SetSpeed(1, -0.15);
    }
    if(scan=qqch///// on hold) // d/tecte qqch stop
    {
        MOTOR_SetSpeed(0, 0)
        MOTOR_SetSpeed(1, 0)

        
 MOTOR_SetSpeed(0,0)
 MOTOR_SetSpeed(1,0)
 ENCODER_ReadReset(0)
 ENCODER_ReadReset(1)
        
}
*/


int main (void)

{}

 