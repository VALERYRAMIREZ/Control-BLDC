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
#include "teclado.h"
/*
                         Main application
 */

int main(void) {
    uint8_t i = 0;
    SYSTEM_Initialize();
    INTERRUPT_Initialize();
    Keyboard_Previous_State(&keys);         
    while(1)
    {
//        if(!bldc.initMotor && bldc.iMotor && bldc.sMod)
//        {
//            bldc.iMotor = false;
//            /* Deshabilitar motor.                                        */
//            bldc.sMod = false; 
//        }
        if(!bldc.initMotor && bldc.iMotor && bldc.sMod)
        {
            bldc.S_invert(true);        
            rEnc = 2;
            tPWM = 0x176f;
            dPWM = 0xbb7;    
            bldc.sDir = false;
            bldc.sMod = true;
            bldc.motorFase = Motor_Next_Sec(Motor_Hall_Read((uint16_t *) &PORTD), bldc.sDir);
            bldc.S_Vel(200, bldc.sDir); 
            bldc.sMod = false;                 
        }
        if(bldc.initMotor && !bldc.iMotor && bldc.sMod)
        {
            rEnc = 2;
            tPWM = 0x176f;
            dPWM = tPWM + rEnc;
            bldc.pState = Motor_Hall_Read((uint16_t *) &PORTD); 
            bldc.S_Init(&rEnc,&dPWM,&tPWM);             
            bldc.iMotor = true;
            bldc.sMod = false;                 
        }        
    }
    return 0;
}

void TMR2_CallBack(void)
{
    
}

void CN_CallBack(void)
{
    if(Motor_Hall_Read((uint16_t *) &PORTD) != bldc.pState)/* Determina si la */
    {                               /* interrupción fue debido a cambio en los
                                     * sensores de efecto Hall.               */
        bldc.motorFase = Motor_Next_Sec(Motor_Hall_Read((uint16_t *) PORTD),
                bldc.sDir);        
    }
    if((keys.aK & 0x000f) != ((keys.aK & 0x0f00) >> 8))
    {
        Keyboard_Check_State(&keys);
        bldc.sMod = true;
    }
}