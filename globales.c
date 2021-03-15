/* 
 * File:                globales.c   
 * Author:              Valery Ramirez
 * Comments:            N/A
 * Revision history:    N/A
 */

#include "globales.h"


/*             Declaraci�n de variables y estructuras de datos a usar.        */

tiempo RTC;                             /* Estructura de tipo tiempo para
                                         * almacenar los datos del RTC.       */

char* Alma_RTC(uint8_t nParam_1, uint8_t dato_1)/* Funci�n para el            */
{                                       /* almacenamiento de los datos en la  */
    static uint8_t cDato_1 = 0, temp_1 = 1;/* estructura de configuraci�n del */
    char *exporta = 0;                  /*RTC.                                */
    if(temp_1 != nParam_1)              /* Se reinicia cDato_1 si se cambia   */
    {                                   /* par�metro a llenar en la estructura*/
        cDato_1 = 0;                    /* para configurar el reloj del       */
    }                                   /* sistema.                           */
    switch(nParam_1)                    /* Llema el par�metro en funci�n de la*/
    {                                   /* funci�n seleccionada.              */
        case 1:
        {
            if(cDato_1 <= 3)
            {
                RTC.ano[cDato_1] = dato_1;
                exporta = (char*) RTC.ano;
                cDato_1++;
            }
        }
        break;
        case 2:
        {
            if(cDato_1 <= 1)
            {
                RTC.mes[cDato_1] = dato_1;
                exporta = (char*) RTC.mes;
                cDato_1++;
            }
        }
        break;
        case 3:
        {
            if(cDato_1 <= 1)
            {
                RTC.dia[cDato_1] = dato_1;
                exporta = (char*) RTC.dia;
                cDato_1++;
            }
        }
        break;
        case 4:
        {
            if(cDato_1 <= 1)
            {
                RTC.hora[cDato_1] = dato_1;
                exporta = (char*) RTC.hora;
                cDato_1++;
            }
        }
        break;
        case 5:
        {
            if(cDato_1 <= 1)
            {
                RTC.minuto[cDato_1] = dato_1;
                exporta = (char*) RTC.minuto;
                cDato_1++;
            }
        }
        break;
        case 6:
        {
            if(cDato_1 <= 1)
            {
                RTC.segundo[cDato_1] = dato_1;
                exporta = (char*) RTC.segundo;
                cDato_1++;
            }
        }
        break;
    }
    temp_1 = nParam_1;                    /* Se asigna nParam_1 a temp para
                                         * comparar en la pr�xima entrada a la
                                         * funci�n.                           */
    return exporta;
}

