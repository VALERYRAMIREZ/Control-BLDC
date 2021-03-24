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
#define MAX_rpm             1800    /* Velocidad nominal en r.p.m. del motor.
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

typedef enum
{
    brushless = 1,
    dc = 2,
    paso = 3,
} tMotor;

typedef enum                
{
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
    p1 = 3,
    p2 = 7,
    p3 = 6,
    p4 = 4,
    p5 = 0,
    p6 = 1,
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
    uint8_t aPos;                   /* Posición actual del motor.             */
    bldcFases motorFase;
    bool sDir;                      /* Sentido de giro del motor.             */
    bool sMod;
    bool iMotor;                    /* Bandera para iniciar o detener el
                                     * movimiento del motor.                  */
    bool (*S_Init) (uint16_t *, uint16_t *, uint16_t *);
    bool (*S_DeInit) (void);
    motorInt (*S_Sec) (bldcFases);  /* OJO: Esta función se va a quitar ya que
                                     * va dentro de la función S_Vel.         */
    void (*S_Vel) (uint16_t, bool); /* Puntero a función para 
                                     * establecer la velocidad del motor.     */
    void (*S_Pos) (uint8_t *, bool *dir);/* Puntero a función para
                                     * establecer la posición del motor.      */
    bool (*S_invert) (bool);
} Motor;

typedef struct
{
    uint8_t P[5];
    uint8_t I[5];
    uint8_t D[5];
} motor;

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

bool Motor_PWM_ON_DeInit(void);

motorInt Motor_PWM_ON_Sec(bldcFases tEstado);

void Motor_PWM_Sec(bldcFases tEstado);

char* Alma_PID(uint8_t nParam_2,uint8_t dato_2);/* Prototipo de función para el
                                             * almacenamiento de los datos en
                                             * las estructuras de configuración
                                             * del PID.                       */

void Motor_Vel(uint16_t rpm, bool dir); /* Prototipo de función para establecer
                                         * la velocidad de giro y el sentido de
                                         * giro del motor.                    */
 
void Motor_Pos(uint8_t pos, bool dir);  /* Prototipo de función para establecer
                                         * la posición que debe alcanzar la 
                                         * flecha del motor.                  */

bool Motor_OC_Invert(bool invert);

bool Motor_Fase_Act(bldcFases *edo, bool *dir);
 
bldcFases Motor_Hall_Sensor(uint16_t port, bool dir);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_MOTOR_H */

