
/**
  OC6 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc6.c

  @Summary
    This is the generated source file for the OC6 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for OC6.
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

#include "oc6.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC6Mode;

/**
  Section: Driver Interface
*/


void OC6_Initialize (void)
{
    // ENFLT0 disabled; OCSIDL disabled; OCM Off; OCFLT0 disabled; OCTSEL FOSC/2; TRIGMODE Only Software; 
    OC6CON1 = 0x1C00;
    // SYNCSEL TMR2; TRIGSTAT disabled; OCINV disabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC6CON2 = 0x0C;
    // CMP2B 0; 
    OC6RS = 0x00;
    // CMP1B 0; 
    OC6R = 0x00;
    // OC6TMR 0; 
    OC6TMR = 0x00;
	
    gOC6Mode = OC6CON1bits.OCM;
}

void __attribute__ ((weak)) OC6_CallBack(void)
{
    // Add your custom callback code here
}

void OC6_Tasks( void )
{	
    if(IFS2bits.OC6IF)
    {
		// OC6 callback function 
		OC6_CallBack();
        IFS2bits.OC6IF = 0;
    }
}



void OC6_Start( void )
{
    OC6CON1bits.OCM = gOC6Mode;
}


void OC6_Stop( void )
{
    OC6CON1bits.OCM = 0;
}

void OC6_SecondaryValueSet( uint16_t secVal )
{
   
    OC6RS = secVal;
}


void OC6_PrimaryValueSet( uint16_t priVal )
{
   
    OC6R = priVal;
}

bool OC6_IsCompareCycleComplete( void )
{
    return(IFS2bits.OC6IF);
}


bool OC6_FaultStatusGet( OC6_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC6_FAULT0:
			status = OC6CON1bits.OCFLT0;
            break;
        default :
            break;

    }
    return(status);
}


void OC6_FaultStatusClear( OC6_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC6_FAULT0:
			OC6CON1bits.OCFLT0 = 0;
                break;
        default :
                break;
    }    
}


void OC6_ManualTriggerSet( void )
{
    OC6CON2bits.TRIGSTAT= true; 
}

bool OC6_TriggerStatusGet( void )
{
    return( OC6CON2bits.TRIGSTAT );
}


void OC6_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC6CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/
