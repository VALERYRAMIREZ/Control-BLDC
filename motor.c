#include "motor.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr1.h"
#include <math.h>

const cPID bldcPID =                /* Estructura de tipo motot para          */
{                                   /* almacenar los datos del PID.           */
    .P = 18.782676,                 /* NOTA: Los parámetros aquí introducidos */
    .I = 0.0032101,                 /* fueron calculados usando la aplicación */
    .D = 0.0008025,                 /* creada para calcular el control PID con*/
    .N = 2
};                                  /* Scilab. Se utilizó el método de Ziegler-
                                     * Nichols con el fin de calcular los 
                                     * coeficientes proporcinal, integral y
                                     * derivativo.                            */

/*      Declaración  de parámetros referentes al manejo del motor             */

uint16_t rEnc;                      /* Variable para el tiempo muerto del PWM,
                                     * la finalidad es evitar que dos
                                     * transistores del mismo puente conduzcan
                                     * al mmismo tiempo.                      */
uint16_t tPWM;                      /* Variable para almacenar el período del
                                     * PWM.                                   */
uint16_t dPWM;                      /* Variable para almacenar el ciclo de
                                     * trabajo del PWM.                       */

Motor bldc =
{
    .pPos = 0,
    .sError = 0,
    .initMotor = false,
    .iMotor = false,
    .isRunning = false,
    .vel = 0,
    .sTipo = brushless,
    .S_Init = Motor_PWM_ON_Init,
    .S_DeInit = Motor_PWM_ON_DeInit,
    .S_Sec = Motor_PWM_ON_Sec,
    .S_checkVel = BLDC_Motor_Check_Vel,
    .S_Vel = Motor_Vel,
    .S_invert = Motor_OC_Invert,
};

bool Motor_PWM_ON_Init(uint16_t *retardo, uint16_t *ciclo, uint16_t *periodo)
{
//    HAB1_SetLow();
//    HAB2_SetLow();
//    HAB3_SetLow();
    OC2_SetHigh();
    OC4_SetHigh();
    OC9_SetHigh();
    OC1_PrimaryValueSet(0);
    OC1_SecondaryValueSet(*periodo + *retardo);
    OC3_PrimaryValueSet(0);
    OC3_SecondaryValueSet(*periodo + *retardo);
    OC5_PrimaryValueSet(0);
    OC5_SecondaryValueSet(*periodo+ *retardo);
    TMR2_Start();
    return true;
}
bool Motor_PWM_ON_DeInit(uint16_t *retardo, uint16_t *ciclo, uint16_t *periodo)
{
    HAB1_SetHigh();
    HAB2_SetHigh();    
    HAB3_SetHigh();
    OC2_SetHigh();
    OC4_SetHigh();
    OC9_SetHigh();    
    OC1_PrimaryValueSet(0);
    OC1_SecondaryValueSet(*periodo + *retardo);
    OC3_PrimaryValueSet(0);
    OC3_SecondaryValueSet(*periodo + *retardo);
    OC5_PrimaryValueSet(0);
    OC5_SecondaryValueSet(*periodo + *retardo);
    TMR2_Stop();
    return true;
}

motorInt Motor_PWM_ON_Sec(bldcFases tEstado)
{
    static motorInt mRefInt;
    switch(tEstado)
    {
        case AC:
        {
            OC1_SecondaryValueSet(dPWM - 2*rEnc);            
            OC1_PrimaryValueSet(2*rEnc);
            mRefInt.T2 = true;
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            mRefInt.T4 = false;
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);              
            mRefInt.T6 = false;
            
        }
        break;
        case BC:
        {              
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            mRefInt.T2 = true;
            OC3_PrimaryValueSet(2*rEnc);
            OC3_SecondaryValueSet(dPWM - 2*rEnc);
            mRefInt.T4 = false;
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);      
            mRefInt.T6 = false;
        }
        break;
        case BA:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            mRefInt.T2 = false;
            OC3_PrimaryValueSet(2*rEnc);
            OC3_SecondaryValueSet(dPWM - 2*rEnc);
            mRefInt.T4 = true;
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            mRefInt.T6 = false;
        }
        break;
        case CA:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            mRefInt.T2 = false;
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            mRefInt.T4 = true;
            OC5_PrimaryValueSet(2*rEnc);
            OC5_SecondaryValueSet(dPWM - 2*rEnc);
            mRefInt.T6 = false;
        }
        break;
        case CB:
        {
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            mRefInt.T2 = false;
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0); 
            mRefInt.T4 = false;
            OC5_PrimaryValueSet(2*rEnc);
            OC5_SecondaryValueSet(dPWM - 2*rEnc);
            mRefInt.T6 = true;
        }
        break;
        case AB:
        {
            OC1_PrimaryValueSet(2*rEnc);
            OC1_SecondaryValueSet(dPWM - 2*rEnc);
            mRefInt.T2 = false;
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            mRefInt.T4 = false;
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            mRefInt.T6 = true;
        }
        break;
        case DD:
        {  
            OC1_PrimaryValueSet(tPWM +rEnc);
            OC1_SecondaryValueSet(0);
            OC3_PrimaryValueSet(tPWM +rEnc);
            OC3_SecondaryValueSet(0);
            OC5_PrimaryValueSet(tPWM +rEnc);
            OC5_SecondaryValueSet(0);
            OC2_SetHigh();
            OC4_SetHigh();
            OC9_SetHigh();            
        }
        break;
        default:
        {
            /* Manejo de errores */
        }
        break;
    }
    return mRefInt;
}

//void Motor_PWM_Sec(bldcFases tEstado)
//{
//        switch(tEstado)
//    {
//        case AC:
//        {
//            OC1_PrimaryValueSet(2*rEnc);
//            OC1_SecondaryValueSet(dPWM - 2*rEnc);
//            OC2_PrimaryValueSet(0);   
//            OC2_SecondaryValueSet(dPWM);
//            OC3_PrimaryValueSet(tPWM +rEnc);
//            OC3_SecondaryValueSet(0);
//            OC4_PrimaryValueSet(tPWM +rEnc);
//            OC4_SecondaryValueSet(0);  
//            OC5_PrimaryValueSet(tPWM +rEnc);
//            OC5_SecondaryValueSet(0);
//            OC9_PrimaryValueSet(tPWM +rEnc);
//            OC9_SecondaryValueSet(0);              
//        }
//        break;
//        case BC:
//        {              
//            OC1_PrimaryValueSet(tPWM +rEnc);
//            OC1_SecondaryValueSet(0);
//            OC2_PrimaryValueSet(2*rEnc);   
//            OC2_SecondaryValueSet(dPWM - 2*rEnc);
//            OC3_PrimaryValueSet(0);
//            OC3_SecondaryValueSet(dPWM);
//            OC4_PrimaryValueSet(tPWM +rEnc);
//            OC4_SecondaryValueSet(0);  
//            OC5_PrimaryValueSet(tPWM +rEnc);
//            OC5_SecondaryValueSet(0);
//            OC9_PrimaryValueSet(tPWM +rEnc);
//            OC9_SecondaryValueSet(0);         
//        }
//        break;
//        case BA:
//        {
//            OC1_PrimaryValueSet(tPWM +rEnc);
//            OC1_SecondaryValueSet(0);
//            OC2_PrimaryValueSet(tPWM +rEnc);   
//            OC2_SecondaryValueSet(0);
//            OC3_PrimaryValueSet(2*rEnc);
//            OC3_SecondaryValueSet(dPWM - 2*rEnc);
//            OC4_PrimaryValueSet(0);
//            OC4_SecondaryValueSet(dPWM);  
//            OC5_PrimaryValueSet(tPWM +rEnc);
//            OC5_SecondaryValueSet(0);
//            OC9_PrimaryValueSet(tPWM +rEnc);
//            OC9_SecondaryValueSet(0);              
//        }
//        break;
//        case CA:
//        {
//            OC1_PrimaryValueSet(tPWM +rEnc);
//            OC1_SecondaryValueSet(0);
//            OC2_PrimaryValueSet(tPWM +rEnc);   
//            OC2_SecondaryValueSet(0);
//            OC3_PrimaryValueSet(tPWM +rEnc);
//            OC3_SecondaryValueSet(0);
//            OC4_PrimaryValueSet(2*rEnc);
//            OC4_SecondaryValueSet(dPWM - 2*rEnc);  
//            OC5_PrimaryValueSet(0);
//            OC5_SecondaryValueSet(dPWM);
//            OC9_PrimaryValueSet(tPWM +rEnc);
//            OC9_SecondaryValueSet(0);           
//        }
//        break;
//        case CB:
//        {
//            OC1_PrimaryValueSet(tPWM +rEnc);
//            OC1_SecondaryValueSet(0);
//            OC2_PrimaryValueSet(tPWM +rEnc);   
//            OC2_SecondaryValueSet(0);
//            OC3_PrimaryValueSet(tPWM +rEnc);
//            OC3_SecondaryValueSet(0);
//            OC4_PrimaryValueSet(tPWM +rEnc);
//            OC4_SecondaryValueSet(0);  
//            OC5_PrimaryValueSet(2*rEnc);
//            OC5_SecondaryValueSet(dPWM - 2*rEnc);
//            OC9_PrimaryValueSet(0);
//            OC9_SecondaryValueSet(dPWM); 
//        }
//        break;
//        case AB:
//        {
//            OC1_PrimaryValueSet(2*rEnc);
//            OC1_SecondaryValueSet(dPWM - 2*rEnc);
//            OC2_PrimaryValueSet(tPWM +rEnc);   
//            OC2_SecondaryValueSet(0);
//            OC3_PrimaryValueSet(tPWM +rEnc);
//            OC3_SecondaryValueSet(0);
//            OC4_PrimaryValueSet(tPWM +rEnc);
//            OC4_SecondaryValueSet(0);  
//            OC5_PrimaryValueSet(tPWM +rEnc);
//            OC5_SecondaryValueSet(0);
//            OC9_PrimaryValueSet(0);
//            OC9_SecondaryValueSet(dPWM);             
//        }
//        break;
//        case DD:
//        {  
//            OC1_Stop();
//            OC2_Stop();
//            OC3_Stop();
//            OC4_Stop();
//            OC5_Stop();
//            OC9_Stop();          
//        }
//        break;
//        default:
//        {
//            /* Manejo de errores */
//        }
//        break;
//        OC1_Start();
//        OC2_Start();
//        OC3_Start();
//        OC4_Start();
//        OC5_Start();
//        OC9_Start();         
//    }
//}
//char* Alma_PID(uint8_t nParam_2,uint8_t dato_2)/* Prototipo de función para el*/
//{                                       /* almacenamiento de los datos en     */
//    static uint8_t cDato_2 = 0;
//    static uint8_t temp_2 = 1;/* estructuras de configuración del*/
//    char *exporta = 0;                  /* PID.                               */
//    if(temp_2 != nParam_2)              /* Se reinicia cDato_1 si se cambia   */
//    {                                   /* parámetro a llenar en la estructura*/
//        cDato_2 = 0;                    /* para configurar el reloj del       */
//    }                                   /* sistema.                           */
//    switch(nParam_2)                    /* Llema el parámetro en función de la*/
//    {                                   /* función seleccionada.              */
//        case 1:
//        {
//            if(cDato_2 <= 3)
//            {
//                PID.P[cDato_2] = dato_2;
//                exporta = (char*) PID.P;
//                cDato_2++;
//            }
//        }
//        break;
//        case 2:
//        {
//            if(cDato_2 <= 3)
//            {
//                PID.I[cDato_2] = dato_2;
//                exporta = (char*) PID.I;
//                cDato_2++;
//            }
//        }
//        break;
//        case 3:
//        {
//            if(cDato_2 <= 3)
//            {
//                PID.D[cDato_2] = dato_2;
//                exporta = (char*) PID.D;
//                cDato_2++;
//            }
//        }
//        break;
//        default:
//        {
//
//        }
//        break;        
//    }
//    temp_2 = nParam_2;                  /* Se asigna nParam_1 a temp_2 para
//                                         * comparar en la próxima entrada a la
//                                         * función.                           */
//    return exporta;
//}

float BLDC_Motor_Check_Vel(uint32_t vel)
{
    uint16_t prescalador = 0;
    float revTiempo = 0.0, rpmProm = 0.0;
    switch(T1CONbits.TCKPS)
    {
        case 0:
        {
            prescalador = 1;
        }
        break;
        case 1:
        {
            prescalador = 8;
        }
        break;
        case 2:
        {
            prescalador = 64;
        }
        break;
        case 3:
        {
            prescalador = 256;
        }
        break;
        default:
        {
            //No debe existir, ERROR.
        }
        break;
    }
    revTiempo = 100.0*vel*prescalador*HALL_nPos*2
            /((uint32_t) CLOCK_SystemFrequencyGet());
    rpmProm = (100*tRevCount)/revTiempo;
    return rpmProm;
}

void Motor_Vel(uint16_t rpm, bool dir)
{
    if(MAX_rpm < rpm)
    {
        /* Se debe hacer una función para mostrar en pantalla que se alcanzó la
         * velocidad máxima permitida para el motor.                          */
        rpm = MAX_rpm;
    }
    else if(rpm < 0)
    {
        /* Se debe hacer una función para mostrar en pantalla que se alcanzó la
         * velocidad mínima permitida.                                        */
        rpm = 0;
    }
    if(rpm == 0)
    {
        Motor_Fase_Act((bldcFases *) DD, &dir);        
    }
    else if((rpm > 0) && (rpm <= MAX_rpm))
    {
        if(!bldc.isRunning)
        {
            HAB1_SetLow();
            HAB2_SetLow();
            HAB3_SetLow();
        }        
        Motor_Fase_Act(&bldc.nFase, &dir);
    }
}

float Motor_PIPD(uint16_t pRpm, uint16_t lRpm, uint32_t h)/* Función basada*/
{                                   /* en un control PIPD la cual calcula el  */
                                    /* ciclo de trabajo del PWM para alcanzar */
                                    /* la velocidad establecida.              */

/*******************Estos parámetros se calculan una sola vez******************/
    
    /*static float ki = bldcPID.P/bldcPID.I;
    static float Tt = -sqrt(bldcPID.I*bldcPID.D);
    static float aI = (1-Tt)/Tt;
    static float bI = 1/Tt;
    static float aD = bldcPID.D/(bldcPID.N*h+bldcPID.D);
    static float bD = bldcPID.P*bldcPID.D*bldcPID.N/(bldcPID.N*h+bldcPID.D);*/
    
/***Estos parámetros se inicializan en cero y se actualizan en el apartado de***
 ********************proceso de la función del controlador*********************/
    
    static float yktMenos = 0.0;
    static float PDtk = 0.0;
    static float itk = 0.0;
    static float vtk = 0.0;
    
/***********Estos parámetros se destruyen al finalizar la función**************/
    
    float etk = 0.0;
    float eitk = 0.0;
    float PItk = 0.0;
    
/******Este es el apartado de proceso de la función del controlador PIPD*******/
    
    etk = pRpm - lRpm;
    eitk = lRpm - vtk;

/*******Los macros aD y bD utilizan el intervalo de muestreo del sistema,
        razón por la cual debe establecerse dicha frecuencia antes de aplicar
        estas operaciones.*****************************************************/
    
    itk = itk + ki*h*(pRpm + aI*lRpm - bI*vtk);
    PItk = itk + etk*bldcPID.P;/* Controlador PI.          */
    PDtk = lRpm + aD*PDtk + bD*(lRpm - yktMenos);/* Controlador PD.           */
    vtk = PItk + PDtk;              /* Salida del controlador PIPD.           */
    yktMenos = lRpm;
    return vtk;
}

bool Motor_OC_Invert(bool invert)
{
    OC1CON2bits.OCINV = invert;
    OC3CON2bits.OCINV = invert;    
    OC5CON2bits.OCINV = invert;
    return true;
}

bool Motor_Fase_Act(bldcFases *edo, bool *dir)
{
    static motorInt actualT;
    bldc.S_Sec(*edo);
    
    actualT = bldc.S_Sec(*edo); 
    (actualT.T2 == true) ? OC2_SetLow() : OC2_SetHigh();
    (actualT.T4 == true) ? OC4_SetLow() : OC4_SetHigh();        
    (actualT.T6 == true) ? OC9_SetLow() : OC9_SetHigh();
    *dir ? ((*edo > AB) ? 
                               (*edo = AC) : *edo) :
                ((*edo < AC) ? 
                               (*edo = AB) : *edo);  
    return true;
}

uint8_t Motor_Hall_Read(uint16_t *port)
{
    uint16_t hall = 0;
//    hall = *port;
//    hall = hall & 0x700;
    hall = ((*port & ((uint16_t) 0x700)) >> 8);
    return hall;
//    return (*port & ((uint16_t) 0x700)) >> 8;
}

bldcFases Motor_Next_Sec(uint8_t hallPos, bool dir)
{
    bldcFases sec = 0;
//    bldc.pPos = hallPos;
    switch(hallPos)
    {
        case P1:
        {
            sec = dir ? AB : AC;
        }
        break;
        case P2:
        {
            sec = dir ? AC : BC;
        }
        break;
        case P3:
        {
            sec = dir ? BC : BA;          
        }
        break;
        case P4:
        {
            sec = dir ? BA : CA;          
        }
        break;
        case P5:
        {
            sec = dir ? CA : CB;          
        }
        break;
        case P6:
        {
            sec = dir ? CB : AB;        
        }
        break;        
        default:
        {
            __asm("nop");
        }
        break;
    }
//        if((dir) && (sec >= AC) && (sec <= AB) && (bldc.pPos != 0))
//    {
//        ((sec) != (bldc.pPos + 1)) ? (bldc.sError = ERROR_SEC) :
//                (bldc.sError = NO_ERROR);
//    }
//        else if(!(dir) && (sec >= AC) && (sec <= AB) && (bldc.pPos != 0))
//    {
//        (!(sec) != (bldc.pPos - 1)) ? (bldc.sError = ERROR_SEC) :
//                (bldc.sError = NO_ERROR);        
//    }
//        else if((sec >= AC) && (sec <= AB) && (bldc.pPos = 0))
//    {
//        bldc.sError = ERROR_SEC;
//    }
//    if(bldc.sError != NO_ERROR)
//    {
//        Motor_Error();
//    }
    return sec;
}

bool Motor_Error_Sec(bldcFases *fase, bool *dir)
{
    bool error = 0;
    switch(*dir)
    {
        case true:
        {
           if(((*fase == AC) && (bldc.aFase != AB)) 
                    || ((*fase == BC) && (bldc.aFase != AC))
                    || ((*fase == BA) && (bldc.aFase!= BC))
                    || ((*fase == CA) && (bldc.aFase != BA))
                    || ((*fase == CB) && (bldc.aFase != CA))
                    || ((*fase == AB) && (bldc.aFase != CB))
                    || (*fase == AA) || (*fase == DD))
            {
                error = true;
            }            
        }
        break;
        case false:
        {
           if(((*fase == BC) && (bldc.aFase != AC)) 
                    || ((*fase == BA) && (bldc.aFase != BC))
                    || ((*fase == CA) && (bldc.aFase != BA))
                    || ((*fase == CB) && (bldc.aFase != CA))
                    || ((*fase == AB) && (bldc.aFase != CB))
                    || ((*fase == AC) && (bldc.aFase != AB))
                    || (*fase == AA) || (*fase == DD))
            {
                error = true;
            }                      
        }
        break;
        default:
        {
            
        }
        break;
    }
    return error;
}

bool Motor_Error_Pos(bldcPos *pos, bool *dir)
{
    bool error = 0;
    switch(*dir)
    {
        case true:
        {
            if(((*pos == P2) && (bldc.pPos != P1)) 
                    || ((*pos == P3) && (bldc.pPos != P2))
                    || ((*pos == P4) && (bldc.pPos != P3))
                    || ((*pos == P5) && (bldc.pPos != P4))
                    || ((*pos == P6) && (bldc.pPos != P5))
                    || ((*pos == P1) && (bldc.pPos != P6))
                    || (*pos == Pinv0) || (*pos == Pinv1))
            {
                error = true;
            }
        }
        break;
        case false:
        {
            if(((*pos == P6) && (bldc.pPos != P1)) 
                    || ((*pos == P5) && (bldc.pPos != P6))
                    || ((*pos == P4) && (bldc.pPos != P5))
                    || ((*pos == P3) && (bldc.pPos != P4))
                    || ((*pos == P2) && (bldc.pPos != P3))
                    || ((*pos == P1) && (bldc.pPos != P2))
                    || (*pos == Pinv0) || (*pos == Pinv1))
            {
                error = true;
            }            
        }
        break;
        default:
        {
            __asm("nop");
        }
        break;
    }
    return error;
}

void Motor_Error(void)
{
    bldc.S_DeInit(&rEnc,&dPWM,&tPWM);
    if(bldc.isRunning)
    {
        bldc.S_invert(false);
        bldc.isRunning = false;
        bldc.iMotor = false;
        bldc.initMotor = false;
    }
    /* Encender LED de error y enviar mensaje a pantalla.                     */
}
