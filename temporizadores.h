/* 
 * File:                temprizadores.h
 * Author:              Valery Ramirez
 * Comments:            Encabezado para la configuración de los temporizadores.
 * Revision history:    N/A
 */
 
#ifndef TEMPORIZADORES_H
#define	TEMPORIZADORES_H

#include <xc.h> // include processor files - each processor file is guarded.  

/* Definiciones de constantes para configuración de T1CON */

#define         TCKPS256            48
#define         TCKPS64             32
#define         TCKPS8              16
#define         TCKPS1              0

/* Prototipos de función para la configuación de los temporizadores */

void Ciclo_Timer1(unsigned int tempo1, unsigned int conf1);/* Prototipo de
                                         * función para configurar el
                                         * funcionamiento del timer 1. */

void Inicia_Ciclo_Timer1(void);         /* Prototipo de función para iniciar el
                                         * funcionamiento del timer 1. */

void Detiene_Ciclo_Timer1(void);        /* Prototipo de función para detener el
                                         * funcionamiento del timer 1. */

void Confi_Timer2(unsigned int tempo2, unsigned int confi2);/* Prototipo de
                                         * función para configurar el
                                         * funcionamiento del timer 2. */

void Confi_Timer23(void);               /* Prototipo de función para configurar
                                         * el temporizador 23                 */

void retardo_us(unsigned long ret2);     /* Prototipo de función para generar
                                         * retardos en us, en múltipos de 5us.*/

void retardo_ms(unsigned long ret2);     /* Prototipo de función para generar
                                         * retardos en ms. */

void retardo_s(unsigned long ret2);     /* Prototipo de función para generar
                                         * retardos en s. */

void Inicia_Timer2(void);               /* Prototipo de función para iniciar el
                                         * funcionamiento del timer 2. */

void Detiene_Timer2(void);              /* Prototipo de función para detner el
                                         * funcionamiento del timer 2. */

void Inicia_Timer232(void);             /* Prototipo de función para detner el
                                         * funcionamiento del timer 2. */

void Detiene_Timer232(void);            /* Prototipo de función para detner el
                                         * funcionamiento del timer 2. */

/* Definición de prototipos de función  para el manejo del temporizador 4.    */

void Confi_Timer4();                    /* Prototipo de función para configurar
                                         * el temporizador 4.                 */

void Inicia_Timer4(void);               /* Prototipo de función para iniciar el
                                         * funcionamiento del timer 1. */

void Detiene_Timer4(void);              /* Prototipo de función para detener el
                                         * funcionamiento del timer 1. */

void Confi_Timer45(void);               /* Prototipo de función para configurar
                                         * el timer45 en modo de 32 bits.     */

void Ciclo45_ms(unsigned long ret45);   /* Prototipo de función para configurar
                                         * el ciclo de trabajo del sistema en
                                         * ms.                                */

//void Inicia_Ciclo45(void);              /* Prototipo de función para comenzar
//                                         * el ciclo de trabajo del sistema.   */
//
//void Detiene_Ciclo45(void);             /* Prototipo de función para detener el
//                                         * ciclo de trabajo del sistema.      */

void retardo_T4_ms(unsigned long ret2); /* Prototipo de función para generar
                                         * retardos en ms. */

#endif	/* TEMPORIZADORES_H */

