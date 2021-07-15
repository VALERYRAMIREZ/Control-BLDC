/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:                motor.h
 * Author:              Valery Ramirez
 * Comments:            Aquí se definen las funciones para el control del motor
 *                      BLDC.
 * Revision history:    10/13/2021
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_MOTOR_H
#define	XC_MOTOR_H

// TODO Insert appropriate #include <>
#include  "mcc_generated_files/system.h"
// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations
#define MAX_rpm             420     /* Velocidad nominal en r.p.m. del motor.
                                     * Esta se convierte en la velocidad máxima
                                     * a la que puede girar el motor.         */
#define MAX_corriente       2       /* Corriente máxima de fase permitida.    */
#define MAX_tension_pot     24      /* Tensión máxima de trabajo de la etapa de
                                     * potencia.                              */
#define MAX_tension_log     15      /* Tensión máxima de trabajo de la etapa de
                                     * lógica de control en la etapa de
                                     * potencia.                              */
#define MAX_tension_cont    3.3     /* Máxima tensión permitida en la etapa de
                                     * control.                               */
#define HALL_nPos           12      /* Cantidad de posiciones posibles en las 
                                     * que puede estar el motor.              */
#define tRevCount           60      /* Cantidad de segundos para contar las
                                     * revoluciones dadas por el motor.       */
#define vRefConv            0.47    /* Tasa de conversión de la velocidad de 
                                     * referencia para la función del control
                                     * PIPD.                                  
                                     * NOTA: por el momento tiene un valor de
                                     * conversión arbitrario.                 */
#define ki                  bldcPID.P/bldcPID.I
#define Tt                  -sqrt(bldcPID.I*bldcPID.D)
#define aI                  (1-Tt)/Tt
#define bI                  1/Tt
#define aD                  bldcPID.D/(bldcPID.N*h+bldcPID.D)
#define bD                  bldcPID.P*bldcPID.D*bldcPID.N/(bldcPID.N*h+bldcPID.D)

typedef enum
{
    brushless = 1,
    dc = 2,
    paso = 3,
} tMotor;

typedef enum                
{
    AA = 0,
    AC = 1,
    BC = 2,
    BA = 3,
    CA = 4,
    CB = 5,
    AB = 6,
    DD = 7,
} bldcFases;                        /* reloj cargar en sentido contrario.     */

typedef enum
{
    P1 = 3,
    P2 = 2,
    P3 = 6,
    P4 = 4,
    P5 = 5,
    P6 = 1,
    Pinv0 = 0,
    Pinv1 = 7,
//    P1 = 3,
//    P2 = 7,
//    P3 = 6,
//    P4 = 4,
//    P5 = 0,
//    P6 = 1,
} bldcPos;

typedef union __attribute((packed)) /* Estructura declaración para los        */
{                                   /* transistores de potencia.              */
    struct
    {
        uint8_t T1:1;
        uint8_t T2:1;
        uint8_t T3:1;
        uint8_t T4:1;
        uint8_t T5:1;
        uint8_t T6:1;
        uint8_t restantes:2;
    };
    uint8_t Ts;
} motorInt;

typedef struct
{
    uint8_t sTipo;                  /* Tipo de motor: futura implementación.  */
    uint8_t mId;                    /* Identificación: futura implementación. */
    uint8_t rMax;                   /* Velocidad de giro máxima del motor.    */
    uint8_t vMax;                   /* Tensión máxima o nominal del motor.    */
    uint8_t cMax;                   /* Corriente máxima o nominal del motor.  */
    uint8_t sError;                 /* Código de error del último error.      */
    bldcPos pPos;                   /* estado previo de los sensores Hall.    */
    bldcPos aPos;                   /* Estado actual de los sensores Hall.    */
    bldcFases aFase;                /* Fase actualmente funcionando.          */
    bldcFases nFase;                /* Próxima fase a activar.                */
    bool sDir;                      /* Sentido de giro del motor.             */
    bool sMod;                      /* Bandera para modificar las rutinas del
                                     * motor.                                 */
    bool initMotor;
    bool iMotor;                    /* Bandera para iniciar o detener el
                                     * movimiento del motor.                  */
    bool isRunning;
    uint32_t vel;
    uint32_t tPrev;
    uint32_t tActual;
    bool (*S_Init) (uint16_t *, uint16_t *, uint16_t *);
    bool (*S_DeInit) (uint16_t *, uint16_t *, uint16_t *);
    motorInt (*S_Sec) (bldcFases);
    float (*S_checkVel) (uint32_t);
    void (*S_Vel) (uint16_t, bool); /* Puntero a función para 
                                     * establecer la velocidad del motor.     */
    void (*S_Pos) (uint8_t *, bool *dir);/* Puntero a función para
                                     * establecer la posición del motor.      */
    bool (*S_invert) (bool);
} Motor;

typedef struct                      /* Estructura para almacenar los          */
{                                   /* coeficientes calculador con método Z-N,*/
    float P;                        /* para luego calcular los coeficientes   */
    float I;                        /* del controlador PIPD a utilizar en la  */
    float D;                        /* respectiva función.                    */
    uint16_t N;                     /* Orden del filtro derivativo.           */
} cPID;

/*     Definción de parámetros globales para manejo del motor.                */

extern uint16_t rEnc;               /* Variable para el tiempo muerto del PWM,
                                     * la finalidad es evitar que dos
                                     * transistores del mismo puente conduzcan
                                     * al mmismo tiempo.                      */
extern uint16_t tPWM;               /* Variable para almacenar el período del
                                     * PWM.                                   */
extern uint16_t dPWM;               /* Variable para almacenar el ciclo de
                                     * trabajo del PWM.                       */
extern Motor bldc;

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype: Establece la velocidad del motor. </b></p>

    <p><b>Summary: </b></p>

    <p><b>Description:</b></p>
    Esta función se encarga de establecer la velocidad del motor con la
 *  velocidad en r.p.m. como parámetro de ingreso.
 
    <p><b>Precondition:</b></p>
    Velocidad en r.p.m. entre 1 y 1800.
    
    <p><b>Parameters:</b></p>
    rpm: entero sin signo de 16 bits como velocidad de giro deseada.
    
    <p><b>Returns:</b></p>
    0 o 1.
    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation


bool Motor_PWM_ON_Init(uint16_t *retardo, uint16_t *ciclo, uint16_t *periodo);

bool Motor_PWM_ON_DeInit(uint16_t *retardo, uint16_t *ciclo, uint16_t *periodo);

motorInt Motor_PWM_ON_Sec(bldcFases tEstado);

void Motor_PWM_Sec(bldcFases tEstado);

char* Alma_PID(uint8_t nParam_2,uint8_t dato_2);/* Prototipo de función para el
                                             * almacenamiento de los datos en
                                             * las estructuras de configuración
                                             * del PID.                       */

float BLDC_Motor_Check_Vel(uint32_t vel);/* Prototipo de función para medir la
                                         * velocidad de giro del motor.       */

void Motor_Vel(uint16_t rpm, bool dir); /* Prototipo de función para establecer
                                         * la velocidad de giro y el sentido de
                                         * giro del motor.                    */

float Motor_PIPD(uint16_t pRpm, uint16_t lRpm, uint32_t h);/* Prototipo de 
                                     * función basada en un control PIPD la cual
                                     * calcula el ciclo de trabajo del PWM para
                                     * alcanzar la velocidad establecida.     */
bool Motor_OC_Invert(bool invert);

bool Motor_Fase_Act(bldcFases *edo, bool *dir);

uint8_t Motor_Hall_Read(uint16_t *port);

bldcFases Motor_Next_Sec(uint8_t hallPos, bool dir);

bool Motor_Error_Sec(bldcFases *fase, bool *dir);

bool Motor_Error_Pos(bldcPos *pos, bool *dir);/* Prototipo de función para
                                         * establecer si la posición del motor
                                         * es correcta de acuerdo a la dirección
                                         * del movimieno.                     */

void Motor_Error(void);
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_MOTOR_H */

