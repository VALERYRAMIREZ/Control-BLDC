/* 
 * File:                E_S.h   
 * Author:              Valery Ramirez
 * Comments:            N/A
 * Revision history:    N/A
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef E_S_H
#define	E_S_H

#include <xc.h>

void Confi_PuertoD(unsigned int pinesD);    /* Prototipo de función para
                                             * configurar el funcionamiento
                                             * del puerto D. */

void Confi_PuertoE(unsigned char pinesE);/* Prototipo de función para configurar
                                         * el funcionamiento del puerto D.    */

void Confi_E_S(void);                   /* Prototipo de función para configurar
                                         * el funcionamiento de los puertos.  */

#endif	/* E_S_H */

