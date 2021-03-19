#include "motor.h"
#include "mcc_generated_files/mcc.h"

motor PID;                              /* Estructura de tipo motot para
                                         * almacenar los datos del PID.       */

/*      Declaración  de parámetros referentes al manejo del motor             */

uint16_t rEnc;                      /* Variable para el tiempo muerto del PWM,
                                     * la finalidad es evitar que dos
                                     * transistores del mismo puente conduzcan
                                     * al mmismo tiempo.                      */
uint16_t tPWM;                      /* Variable para almacenar el período del
                                     * PWM.                                   */
uint16_t dPWM;                      /* Variable para almacenar el ciclo de
                                     * trabajo del PWM.                       */

motorInt mRefInt;

void Motor_Sec(eMotor tEstado)
{
        switch(tEstado)
    {
        case AC:
        {
            OC1_PrimaryValueSet(2*rEnc);
            OC1_SecondaryValueSet(dPWM - 2*rEnc);
            OC2_PrimaryValueSet(0);   
            OC2_SecondaryValueSet(dPWM);
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            OC4_PrimaryValueSet(tPWM +rEnc);
            OC4_SecondaryValueSet(0);  
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            OC9_PrimaryValueSet(tPWM +rEnc);
            OC9_SecondaryValueSet(0);              
        }
        break;
        case BC:
        {              
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            OC2_PrimaryValueSet(2*rEnc);   
            OC2_SecondaryValueSet(dPWM - 2*rEnc);
            OC3_PrimaryValueSet(0);
            OC3_SecondaryValueSet(dPWM);
            OC4_PrimaryValueSet(tPWM +rEnc);
            OC4_SecondaryValueSet(0);  
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            OC9_PrimaryValueSet(tPWM +rEnc);
            OC9_SecondaryValueSet(0);         
        }
        break;
        case BA:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            OC2_PrimaryValueSet(tPWM +rEnc);   
            OC2_SecondaryValueSet(0);
            OC3_PrimaryValueSet(2*rEnc);
            OC3_SecondaryValueSet(dPWM - 2*rEnc);
            OC4_PrimaryValueSet(0);
            OC4_SecondaryValueSet(dPWM);  
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            OC9_PrimaryValueSet(tPWM +rEnc);
            OC9_SecondaryValueSet(0);              
        }
        break;
        case CA:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            OC2_PrimaryValueSet(tPWM +rEnc);   
            OC2_SecondaryValueSet(0);
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            OC4_PrimaryValueSet(2*rEnc);
            OC4_SecondaryValueSet(dPWM - 2*rEnc);  
            OC5_PrimaryValueSet(0);
            OC5_SecondaryValueSet(dPWM);
            OC9_PrimaryValueSet(tPWM +rEnc);
            OC9_SecondaryValueSet(0);           
        }
        break;
        case CB:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            OC2_PrimaryValueSet(tPWM +rEnc);   
            OC2_SecondaryValueSet(0);
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            OC4_PrimaryValueSet(tPWM +rEnc);
            OC4_SecondaryValueSet(0);  
            OC5_PrimaryValueSet(2*rEnc);
            OC5_SecondaryValueSet(dPWM - 2*rEnc);
            OC9_PrimaryValueSet(0);
            OC9_SecondaryValueSet(dPWM); 
        }
        break;
        case AB:
        {
            OC1_PrimaryValueSet(2*rEnc);
            OC1_SecondaryValueSet(dPWM - 2*rEnc);
            OC2_PrimaryValueSet(tPWM +rEnc);   
            OC2_SecondaryValueSet(0);
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            OC4_PrimaryValueSet(tPWM +rEnc);
            OC4_SecondaryValueSet(0);  
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            OC9_PrimaryValueSet(0);
            OC9_SecondaryValueSet(dPWM);             
        }
        break;
        case DD:
        {  
            OC1_Stop();
            OC2_Stop();
            OC3_Stop();
            OC4_Stop();
            OC5_Stop();
            OC9_Stop();          
        }
        break;
        default:
        {
            /* Manejo de errores */
        }
        break;
        OC1_Start();
        OC2_Start();
        OC3_Start();
        OC4_Start();
        OC5_Start();
        OC9_Start();         
    }
}

char* Alma_PID(uint8_t nParam_2,uint8_t dato_2)/* Prototipo de función para el*/
{                                       /* almacenamiento de los datos en     */
    static uint8_t cDato_2 = 0, temp_2 = 1;/* estructuras de configuración del*/
    char *exporta = 0;                  /* PID.                               */
    if(temp_2 != nParam_2)              /* Se reinicia cDato_1 si se cambia   */
    {                                   /* parámetro a llenar en la estructura*/
        cDato_2 = 0;                    /* para configurar el reloj del       */
    }                                   /* sistema.                           */
    switch(nParam_2)                    /* Llema el parámetro en función de la*/
    {                                   /* función seleccionada.              */
        case 1:
        {
            if(cDato_2 <= 3)
            {
                PID.P[cDato_2] = dato_2;
                exporta = (char*) PID.P;
                cDato_2++;
            }
        }
        break;
        case 2:
        {
            if(cDato_2 <= 3)
            {
                PID.I[cDato_2] = dato_2;
                exporta = (char*) PID.I;
                cDato_2++;
            }
        }
        break;
        case 3:
        {
            if(cDato_2 <= 3)
            {
                PID.D[cDato_2] = dato_2;
                exporta = (char*) PID.D;
                cDato_2++;
            }
        }
        break;        
    }
    temp_2 = nParam_2;                  /* Se asigna nParam_1 a temp_2 para
                                         * comparar en la próxima entrada a la
                                         * función.                           */
    return exporta;
}

void Motor_Vel(uint16_t rpm, bool dir)
{
    if(MAX_rpm < rpm)
    {
        return;
    }
}
