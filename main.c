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
#include "mcc_generated_files/mcc.h"
#include "motor.h"
/*
                         Main application
 */
eMotor motorFase;

bool sMotor = 0;
bool aMotor = 0;

int main(void) {
    motorInt actualT;
    uint16_t i;
    actualT.Ts = 0;
    SYSTEM_Initialize();
    INTERRUPT_Initialize();
    rEnc = 2;
    tPWM = 0x1770;
    dPWM = tPWM +rEnc;
    HAB1_SetHigh();
    HAB2_SetHigh();
    HAB3_SetHigh();
    OC2_SetHigh();
    OC4_SetHigh();
    OC9_SetHigh();
    OC1_PrimaryValueSet(0);
    OC1_SecondaryValueSet(tPWM + rEnc);
    OC3_PrimaryValueSet(0xbb7);
    OC3_SecondaryValueSet(tPWM);
    OC5_PrimaryValueSet(0);
    OC5_SecondaryValueSet(tPWM + rEnc);
    TMR2_Start();
    for(i = 0; i < 30000; i++);
    OC_Motor_Invert(true);
    rEnc = 2;
    tPWM = 0x1770;
    dPWM = 0xbb7;    
    motorFase = DD;
    sMotor = true;
    aMotor = false;
    while(1)
    {
        if(aMotor == true)
        {
            (actualT.T2 == true) ? OC2_SetLow() : OC2_SetHigh();
            (actualT.T4 == true) ? OC4_SetLow() : OC4_SetHigh();        
            (actualT.T6 == true) ? OC9_SetLow() : OC9_SetHigh();
            actualT = Motor_PWM_ON_Sec(motorFase); 
            sMotor ? ((++motorFase > AB) ? (motorFase = AC) : motorFase) :
                     ((--motorFase < AC) ? (motorFase = AB) : motorFase);               
            aMotor = false;         
        }
    }
    return 0;
}

void TMR2_CallBack(void)
{
    aMotor = true;
    IFS0bits.T2IF = false;
    HAB3_Toggle();
}