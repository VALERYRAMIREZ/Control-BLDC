/*
* File: sistema.h
* Author: Valery Ramirez
* Comments: Configuración de reloj
* Revision history: 
*/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SISTEMA_H
#define	SISTEMA_H

#include <xc.h> // include processor files - each processor file is guarded.  

/*Definiciones de datos para desbloquear OSCCONh*/

#define     N1          0x78
#define     N2          0x9A

/*Definicioens de datos para desbloquear OSCCONL*/

#define     N3          0x46
#define     N4          0x57

/*Definiciones de valores para configuración de OSCCON, las constantes están
tas para utilizar las funciones incorporadas por el compilador XC16.*/

/*Tipo de oscillador actual: COSC<2:0>*/

#define     FSTRCPS     112
#define     RSVD        96
#define     LPRC        80
#define     SOSC        64
#define     PRPLL       48
#define     PROSC       32
#define     FSTRCPPLL   16
#define     FSTRC       0

/*Tipo de oscilador nuevo: NOSC<2:0>*/

#define     NFSTRCPS    7
#define     NRSVD       6
#define     NLPRC       5
#define     NSOSC       4
#define     NPRPLL      3
#define     NPROSC      2
#define     NFSTRCPPLL  1
#define     NFSTRC      0

/*Bit de selección de bloqueo del reloj: CLKLOCK*/

/*Si FSCM está hablilitado*/

#define     CLKPLLOCKA  128
#define     CLKPLLOCKD  0

/*Bit de habilitación de las E/S: IOLOCK*/

#define     IOLOCKA     64
#define     IOLOCKD     0

/*Bit de habilitación del oscilador primario POSCEN*/

#define     POSCENH     4
#define     POSCEND     0

/*Bit de habilitación del oscilador secundario de 32 kHz SOSCEN*/

#define     SOSCENH     2
#define     SOSCEND     0

/*Bit de habilitación de cambio de oscilador OSWEN*/

#define     OSWENI      1

/*Definición de prototipos de funciones para el control del oscilador*/

void Tipo_Osc(unsigned short reloj);    /* Función para configurar el tipo de 
                                         * reloj a utilizar.*/

void Sec_Osc(unsigned short secosc);    /* Función para habilitar el uso del
                                         * oscilador secundario.*/
#endif	/* SISTEMA_H */

