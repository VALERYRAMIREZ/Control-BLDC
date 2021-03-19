
/**
  OC9 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc9.c

  @Summary
    This is the generated source file for the OC9 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for OC9.
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

#include "oc9.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC9Mode;

/**
  Section: Driver Interface
*/


void OC9_Initialize (void)
{
    // ENFLT0 disabled; OCSIDL disabled; OCM Center-Aligned PWM mode; OCFLT0 disabled; OCTSEL FOSC/2; TRIGMODE Only Software; 
    OC9CON1 = 0x1C07;
    // SYNCSEL TMR2; TRIGSTAT disabled; OCINV enabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC9CON2 = 0x100C;
    // CMP2B 0; 
    OC9RS = 0x00;
    // CMP1B 0; 
    OC9R = 0x00;
    // OC9TMR 0; 
    OC9TMR = 0x00;
	
    gOC9Mode = OC9CON1bits.OCM;
}

void __attribute__ ((weak)) OC9_CallBack(void)
{
    // Add your custom callback code here
}

void OC9_Tasks( void )
{	
    if(IFS5bits.OC9IF)
    {
		// OC9 callback function 
		OC9_CallBack();
        IFS5bits.OC9IF = 0;
    }
}



void OC9_Start( void )
{
    OC9CON1bits.OCM = gOC9Mode;
}


void OC9_Stop( void )
{
    OC9CON1bits.OCM = 0;
}

void OC9_SecondaryValueSet( uint16_t secVal )
{
   
    OC9RS = secVal;
}


void OC9_PrimaryValueSet( uint16_t priVal )
{
   
    OC9R = priVal;
}

bool OC9_IsCompareCycleComplete( void )
{
    return(IFS5bits.OC9IF);
}


bool OC9_FaultStatusGet( OC9_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC9_FAULT0:
			status = OC9CON1bits.OCFLT0;
            break;
        default :
            break;

    }
    return(status);
}


void OC9_FaultStatusClear( OC9_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC9_FAULT0:
			OC9CON1bits.OCFLT0 = 0;
                break;
        default :
                break;
    }    
}


void OC9_ManualTriggerSet( void )
{
    OC9CON2bits.TRIGSTAT= true; 
}

bool OC9_TriggerStatusGet( void )
{
    return( OC9CON2bits.TRIGSTAT );
}


void OC9_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC9CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/
