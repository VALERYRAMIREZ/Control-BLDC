/* 
 * File:                mensajes.c   
 * Author:              Valery Ramirez
 * Comments:            Funciones para manejar el procesamiento de mensajes.
 * Revision history:    N/A
 */

#include <xc.h>
#include <stdio.h>
#include "mensajes.h"

unsigned char Dim_Mensaje(char *arreglo)/* Función para calcular la cantidad  */
{                                   /* de elementos de un string.             */
    unsigned char cuenta = 0;
    while(arreglo[cuenta] != NULL)
    {
        cuenta++;
    }
    return cuenta;
}
