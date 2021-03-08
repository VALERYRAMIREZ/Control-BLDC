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
#include "mcc_generated_files/system.h"

/*
                         Main application
 */
#include <xc.h>
#include <string.h>
#include "globales.h"
#include "sistema.h"
#include "E_S.h"
#include "temporizadores.h"
#include "interrup.h"
#include "mensajes.h"
#include "LCD_44780.h"
#include "botones.h"

int main(void) {
    extern SENALES senales;
    char boton;
    extern uint8_t selMenu;
    Tipo_Osc(PROSC);
    Confi_E_S();
    Inicia_Interr();
    Inicia_LCD4();
    Ciclo_Timer1(10,0b0000000000000010);
    PORTE = 0x08;
    Inicia_Ciclo_Timer1();
    senales.tecla = 0;                  /* Lo puedo llamar de esa forma porque*/
    Posicion_Cur4b(1,0);                /* ya est? instanciada la union en    */
    Menu();                             /* interup.c y al inicio de main se   */
                                         /* instancia la estructura como una   */
                                        /* variable externa.                  */
    while(1)
    {
        tecladoAnt = PORTE;
        if(senales.tecla)
        {
            boton = det_Tecla(teclado);
            if(strcmp(&boton,"#") && !senales.nInterfaz)/* Se cambia la opci?n*/
            {                               /* del men? seleccionado.         */
                Selec_MenuS(boton);
            }
            else if(!strcmp(&boton,"#") && !senales.nInterfaz)/* Se accede al */
            {                               /* men? secundario seleccionado.  */
                Menu_S(selMenu);
                senales.nInterfaz = 1;
            }
            else if(!strcmp(&boton,"*") && senales.nInterfaz)/* Se sale del   */
            {                               /* men? secundario actual y se    */
                Menu();                     /* vuelve al men? principal.      */
                Selec_MenuS(boton);
                senales.nInterfaz = 0;
            }
            else if(senales.nInterfaz)// && (selMenu == 1))/* Se permite que el  */
            {                               /* cursor se mueva entre los      */
                cpos_Menu_S(selMenu,(uint8_t) boton);/* par?metros a llenar   */
            }                               /* del men? secundario 1          */
            boton = 0;                      /* (configuraci?n del reloj).     */
            senales.tecla = 0;    
        }                               
    }
    return 0;
}

