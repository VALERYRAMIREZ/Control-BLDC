/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ256GA106
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <stdio.h>
#include "mcc_generated_files/system.h"
#include "motor.h"
/*
                         Main application
 */

int main(void) {

    uint16_t i;                     /* Inicialiazación de contador para el
                                     * retardo de visualización, se debe borrar
                                     * al terminar las pruebas.               */
    SYSTEM_Initialize();
    INTERRUPT_Initialize();
    rEnc = 2;
    tPWM = 0x1770;
    dPWM = tPWM + rEnc;
    bldc.S_Init(&rEnc,&dPWM,&tPWM);
    for(i = 0; i < 30000; i++);     /* Retardo simple para visualización. Se    
                                     * debe borrar al terminar las pruebas.   */
    bldc.S_invert(true);
    rEnc = 2;
    tPWM = 0x1770;
    dPWM = 0xbb7;    
    bldc.sDir = true;
    bldc.sMod = false;
    bldc.motorFase = Motor_Hall_Sensor(PORTD, bldc.sDir);
    while(1)
    {
        if(bldc.sMod == true)
        {
            bldc.S_Vel(200, bldc.sDir);            
            bldc.sMod = false;         
        }
    }
    return 0;
}

void TMR2_CallBack(void)
{
    bldc.sMod = true;
}

void CN_CallBack(void)
{
    bldc.motorFase = Motor_Hall_Sensor(PORTD, bldc.sDir);
}