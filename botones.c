#include "botones.h"
#include "globales.h"
#include <stdbool.h>
#include <stdio.h>

/*             Variables a utilizar por las funciones.                        */

enum estBotones                     /* Enumerador para seleccionar el valor de*/
{                                   /* salida de la función para deteccion de */
    bajo,                           /* flancos.                               */
    alto,
    subida,
    bajada
};

const uint8_t columnas[] = {0x10,0x20,0x00,0x40,0x00,0x00,0x00,0x80};

const char tcldo[][4] = {{'7','8','9','D'},
                        {'4','5','6','C'},
                        {'1','2','3','B'},
                        {'*','0','#','A'}};

/*            Funciones para discriminar la tecla presionada.                 */

uint8_t Anti_R(uint8_t estad, bool pin)
{
    uint8_t vieja = estad & 0x7f;
    bool bandera = (estad & 0x80)? true : false;
    
    vieja -= (vieja >> 2);          /* El corrimiento de 2 divide a la variable
                                     * "vieja" por 4: y = x/n es lo mismo que
                                     * x >> n.                                */
    vieja += pin? 0x1f : 0x00;      /* Si el bit es igual a 1 le suma 25%.    */
    
    estad = (vieja & 0x7f) | ((bandera & 0x01) << 0x07);
    return estad;
}

unsigned int flanco(bool bitAnt, bool bit)/* Función para determinar el tipo  */
{                                   /* de flanco que hubo al darse un cambio  */
    enum estBotones estFlanco;      /* de estado en el puerto E. La función   */
    if(!bitAnt && bit)              /* solo debe llamarse al darse un cambio  */
    {                               /* en el estado del puerto.               */
        estFlanco = subida;
    }
    else if(bitAnt && !bit)
    {
        estFlanco = bajada;
    }
    return estFlanco;
}

uint8_t detec_Columna(uint8_t pad)      /* Función para detectar la columna   */
{                                       /* activada cuando se han presionado  */
    return columnas[((pad & 0xf0) >> 4) - 1];/* teclas, devuelve la posición  */
                                        /* en el nibble alto de la columna    */
                                        /* activada. La función está hecha    */
                                        /* para que la función "flanco" sepa  */
                                        /* cual bit va a comparar.            */
}

char det_Tecla(uint8_t lectura)         /* Función para asignar el valor      */
{                                       /* a la tecla presionada. La función */
    uint8_t fila = 0, col = 0, contf = 0, contc = 0;/* calcula la columna y la*/
    do                                  /* fila como el valor almacenado en un*/
    {                                   /* arreglo bidimensional.             */
        col = ((lectura & 0xf0) >> 4) >> contc;
        contc++;
    } while(col != 1);
    do
    {
        fila = ((lectura & 0x0f) >> contf);
        contf++;
    } while(fila != 1);
    return tcldo[contf-1][contc-1];
}
