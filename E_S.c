/* 
 * File:                E_S.c   
 * Author:              Valery Ramirez
 * Comments:            N/A
 * Revision history:    N/A
 */

#include "E_S.h"

void Confi_PuertoD(unsigned int pinesD) /* Función para configurar el         */
{                                       /* funcionamiento del puerto D.       */
    TRISD = pinesD;
    ODCD = 0;
}

void Confi_PuertoE(unsigned char pinesE)/* Función para configurar el         */
{                                       /* funcionamiento del puerto E.       */
    TRISE = pinesE;
    ODCE = 0;
    CNPU4 = 0x3c00;                     /* Se le ponen las pullup a los pines */
                                        /* de fila.                           */
    PORTE = 0x01;
}

void Confi_E_S(void)                    /* Función para configurar el         */
{                                       /* funcionamiento de los puertos.     */
    Confi_PuertoD(0b1111000000000000);
    Confi_PuertoE(0b11110000);
}
