
/**
  OC5 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc5.c

  @Summary
    This is the generated source file for the OC5 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for OC5.
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

#include "oc5.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC5Mode;

/**
  Section: Driver Interface
*/


void OC5_Initialize (void)
{
    // ENFLT0 disabled; OCSIDL disabled; OCM Center-Aligned PWM mode; OCFLT0 disabled; OCTSEL FOSC/2; TRIGMODE Hardware or Software; 
    OC5CON1 = 0x1C0F;
    // SYNCSEL TMR2; TRIGSTAT disabled; OCINV enabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC5CON2 = 0x100C;
    // CMP2B 0; 
    OC5RS = 0x00;
    // CMP1B 0; 
    OC5R = 0x00;
    // OC5TMR 0; 
    OC5TMR = 0x00;
	
    gOC5Mode = OC5CON1bits.OCM;
}

void __attribute__ ((weak)) OC5_CallBack(void)
{
    // Add your custom callback code here
}

void OC5_Tasks( void )
{	
    if(IFS2bits.OC5IF)
    {
		// OC5 callback function 
		OC5_CallBack();
        IFS2bits.OC5IF = 0;
    }
}



void OC5_Start( void )
{
    OC5CON1bits.OCM = gOC5Mode;
}


void OC5_Stop( void )
{
    OC5CON1bits.OCM = 0;
}

void OC5_SecondaryValueSet( uint16_t secVal )
{
   
    OC5RS = secVal;
}


void OC5_PrimaryValueSet( uint16_t priVal )
{
   
    OC5R = priVal;
}

bool OC5_IsCompareCycleComplete( void )
{
    return(IFS2bits.OC5IF);
}


bool OC5_FaultStatusGet( OC5_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC5_FAULT0:
			status = OC5CON1bits.OCFLT0;
            break;
        default :
            break;

    }
    return(status);
}


void OC5_FaultStatusClear( OC5_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC5_FAULT0:
			OC5CON1bits.OCFLT0 = 0;
                break;
        default :
                break;
    }    
}


void OC5_ManualTriggerSet( void )
{
    OC5CON2bits.TRIGSTAT= true; 
}

bool OC5_TriggerStatusGet( void )
{
    return( OC5CON2bits.TRIGSTAT );
}


void OC5_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC5CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/
