#include "sistema.h"

void Tipo_Osc(unsigned short reloj)
{
    __builtin_write_OSCCONH(reloj); /* Función para configurar el tipo de reloj a
                                     * a utilizar.*/
}

void Sec_Osc(unsigned short secosc) /* Función para habilitar el uso del
                                     * oscilador secundario. */
{                                    
    __builtin_write_OSCCONL(secosc);
}