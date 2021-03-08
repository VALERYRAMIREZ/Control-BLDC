/* 
 * File:                globales.c   
 * Author:              Valery Ramirez
 * Comments:            N/A
 * Revision history:    N/A
 */

#include "globales.h"


/*             Declaración de variables y estructuras de datos a usar.        */

tiempo RTC;                             /* Estructura de tipo tiempo para
                                         * almacenar los datos del RTC.       */
motor PID;                              /* Estructura de tipo motot para
                                         * almacenar los datos del PID.       */


char* Alma_RTC(uint8_t nParam_1, uint8_t dato_1)/* Función para el            */
{                                       /* almacenamiento de los datos en la  */
    static uint8_t cDato_1 = 0, temp_1 = 1;/* estructura de configuración del */
    char *exporta = 0;                  /*RTC.                                */
    if(temp_1 != nParam_1)              /* Se reinicia cDato_1 si se cambia   */
    {                                   /* parámetro a llenar en la estructura*/
        cDato_1 = 0;                    /* para configurar el reloj del       */
    }                                   /* sistema.                           */
    switch(nParam_1)                    /* Llema el parámetro en función de la*/
    {                                   /* función seleccionada.              */
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
                                         * comparar en la próxima entrada a la
                                         * función.                           */
    return exporta;
}

char* Alma_PID(uint8_t nParam_2,uint8_t dato_2)/* Prototipo de función para el*/
{                                       /* almacenamiento de los datos en     */
    static uint8_t cDato_2 = 0, temp_2 = 1;/* estructuras de configuración del*/
    char *exporta = 0;                  /* PID.                               */
    if(temp_2 != nParam_2)              /* Se reinicia cDato_1 si se cambia   */
    {                                   /* parámetro a llenar en la estructura*/
        cDato_2 = 0;                    /* para configurar el reloj del       */
    }                                   /* sistema.                           */
    switch(nParam_2)                    /* Llema el parámetro en función de la*/
    {                                   /* función seleccionada.              */
        case 1:
        {
            if(cDato_2 <= 3)
            {
                PID.P[cDato_2] = dato_2;
                exporta = (char*) PID.P;
                cDato_2++;
            }
        }
        break;
        case 2:
        {
            if(cDato_2 <= 3)
            {
                PID.I[cDato_2] = dato_2;
                exporta = (char*) PID.I;
                cDato_2++;
            }
        }
        break;
        case 3:
        {
            if(cDato_2 <= 3)
            {
                PID.D[cDato_2] = dato_2;
                exporta = (char*) PID.D;
                cDato_2++;
            }
        }
        break;        
    }
    temp_2 = nParam_2;                  /* Se asigna nParam_1 a temp_2 para
                                         * comparar en la próxima entrada a la
                                         * función.                           */
    return exporta;
}