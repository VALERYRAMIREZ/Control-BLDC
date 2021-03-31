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
    SYSTEM_Initialize();
    INTERRUPT_Initialize();
    Keyboard_Previous_State(&keys);
    while(1)
    {
        if(bldc.sMod)
        {
            if(!bldc.initMotor)
            {
                /* Deshabilitar motor.                                        */
                bldc.S_DeInit();
                if(bldc.isRunning)
                {
                    bldc.S_invert(false);
                    bldc.isRunning = false;
                    bldc.iMotor = false;
                }
            }
//            if(bldc.initMotor && !bldc.iMotor && bldc.isRunning)
//            {
//                bldc.S_Vel(0, bldc.sDir);
//                bldc.isRunning = false;
//            }
            if(bldc.initMotor && bldc.iMotor)
            {
                bldc.S_invert(true);        
                rEnc = 2;
                tPWM = 0x176f;
                dPWM = 0xbb7;    
//                bldc.sDir = true;
                bldc.nextFase = Motor_Next_Sec(bldc.pPos, bldc.sDir);
                bldc.S_Vel(200, bldc.sDir);
                bldc.isRunning = true;
            }
            if(bldc.initMotor && !bldc.iMotor)
                
            {
                rEnc = 2;
                tPWM = 0x176f;
                dPWM = tPWM + rEnc;
                bldc.pPos = Motor_Hall_Read((uint16_t *) &PORTD); 
                bldc.S_Init(&rEnc,&dPWM,&tPWM);
                if(bldc.isRunning)
                {
                    bldc.S_invert(false);
                    bldc.isRunning = false;
                }
            }
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
    /* Determina si hubo un cambio de estado en la posici�n del motor.        */
    
    if((Motor_Hall_Read((uint16_t *) &PORTD)) != (bldc.pPos)
            && bldc.initMotor && bldc.iMotor)/* Determina si la interrupci�n  */
    {                               /* fue debido a cambio en los sensores de
                                     * efecto Hall.                           */
        bldc.pPos = Motor_Hall_Read((uint16_t *) &PORTD);
        bldc.nextFase = Motor_Next_Sec(bldc.pPos, bldc.sDir);
        bldc.S_Vel(200, bldc.sDir);        
    }
    
    /* Determina si se presion� un bot�n del teclado.                         */
    
    Keyboard_Actual_State(&keys);
    if((keys.t1PrevState && !keys.t1ActState) 
            || (keys.t2PrevState && !keys.t2ActState)
            || (keys.t3PrevState && !keys.t3ActState)
            || (keys.t4PrevState && !keys.t4ActState))
    {
        Keyboard_Previous_State(&keys);
    }
    else if((!keys.t1PrevState && keys.t1ActState) 
            || (!keys.t2PrevState && keys.t2ActState)
            || (!keys.t3PrevState && keys.t3ActState)
            || (!keys.t4PrevState && keys.t4ActState))
    {
        Keyboard_Update_Button(&keys);
        Keyboard_Previous_State(&keys);
        bldc.sMod = true;
    }
}