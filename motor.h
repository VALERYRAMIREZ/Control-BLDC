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

typedef enum                        /* Enumerador para asignar las fases que  */
{                                   /* estarán encendidas segun la secuencia  */
    AC = 0x03,                      /* necesaria. El motor girando en sentido */
    BC = 0x06,                      /* contrario a las agujas del reloj, la   */
    BA = 0x0c,                      /* letra de la derecha en las definiciones*/
    CA = 0x18,                      /* del enumerador son la referencia actual*/
    CB = 0x30,                      /* para esa secuencia. Para hacer girar el*/
    AB = 0x21,                      /* motor en el sentido de las agujas del  */
} motorFases;                       /* reloj cargar en sentido contrario.     */

typedef union __attribute((packed)) /* Estructura declaración para los        */
{                                   /* transistores de potencia.              */
    struct
    {
        uint8_t restantes:2;
        uint8_t T6:1;
        uint8_t T5:1;
        uint8_t T4:1;
        uint8_t T3:1;
        uint8_t T2:1;
        uint8_t T1:1;
    };
    uint8_t Ts;
} motorInt;
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
 void Motor_Vel(uint16_t rpm);
 
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_MOTOR_H */

