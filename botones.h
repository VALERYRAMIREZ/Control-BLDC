/* 
 * File:                botones.h
 * Author:              Valery Ramirez
 * Comments:            Librería para la manipulación de los botones, teclado.
 * Revision history:    N/A
 */

#ifndef XC_BOTONES_H
#define	XC_BOTONES_H

#include <xc.h> 
#include <stdbool.h>

/*          Definiciones de constantes usadas para el teclado.                */

/*               Prototipos de funciones para manejo del teclado.             */

unsigned char Anti_R(uint8_t estado, bool pin);/* Prototipo de función
                                         * para realizar un filtro pasa bajo
                                         * exponencial con el fin de realizar
                                         * un antirebote en un pin específico.*/

unsigned int flanco(bool bitAnt, bool bit);/* Prototipo de función para detectar
                                         * el flanco del cambio de estado en un
                                         * bit.                               */

uint8_t detec_Columna(uint8_t pad);     /* Prototipo de función para detectar
                                         * la columna activada cuando se han
                                         * presionado teclas.                 */

char det_Tecla(uint8_t lectura);        /* Prototipo de función para
                                         * asignar el valor de la tecla
                                         * presionada.                        */

#endif	/* XC_BOTONES_H */

