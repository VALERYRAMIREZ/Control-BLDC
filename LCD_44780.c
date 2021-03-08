#include "LCD_44780.h"
#include "temporizadores.h"
#include "mensajes.h"
#include "globales.h"
#include <stdio.h>

/*         Definición de variables para el uso interno de la librería.        */

uint8_t selMenu = 1;                    /* Variable para almacenar el menú 
                                         * secundario activo.                 */
uint8_t filMenu_r = 2;                  /* Variable para almacenar la posición
                                         * en la que aparece la primera columna
                                         * del menú secundario 1.             */

/*       Definición de opciones de menú a desplegar en la pantalla LCD.       */

const char *menu_i[] = {"1) Hora","2) Param. Motor","3) Manual","4) Auto"};
const char *menu_r[] = {" Config. fecha","DD:","MM:","AA:","hh:","mm:","ss:"};
const char *menu_m[] = {"   Param. PID","P:","I:","D:"};
extern tiempo RTC;

/* Definición de funciones para el control de la pantalla LCD. */

void Inicia_LCD4(void)                      /* Función para inicializar la    */
{                                           /* pantalla LCD.                  */
    PORTD = 0;
    
    retardo_ms(16);
                                     
    Envia_Com(0x30);
    
    retardo_ms(10);
    
    Envia_Com(0x30);
    
    retardo_us(100);
    
    Envia_Com(0x30);

    retardo_us(100);
    
    Envia_Com(CF);
    
    Envia_Com4b(CF | 0x08);
    
    Envia_Com4b(CF | 0x08);
    
    Envia_Com4b(CME);
    
    Envia_Com4b(EAP | 0x06);

    Borra_Pant4b();
}

void Envia_Com(unsigned int comandoLCD)
{
    retardo_us(5);
    E = 1;
    PORTD = comandoLCD | 0x100;
    retardo_us(5);
    E = 0;
}

void Envia_Com_RAM(unsigned int comandoLCD)
{
    retardo_us(5);
    RS = 1;
    E = 1;
    PORTD = comandoLCD | 0x500;
    retardo_us(5);
    E = 0;
    retardo_us(5);
    RS = 0;
}

void Envia_Com4b(unsigned int comandoLCD4)/* Función para enviar comando con  */
{                                       /* la pantalla incializada en modo    */
    Envia_Com(comandoLCD4 & 0xf0);      /* de 4 bits.                         */
    Envia_Com((comandoLCD4 << 4) & 0xf0);
}

void Envia_Com_RAM4b(unsigned int comandoLCD4)/* Función para enviar comando  */
{                                       /* con la pantalla incializada en modo*/
    Envia_Com_RAM(comandoLCD4 & 0xf0);  /* de 4 bits.                         */
    Envia_Com_RAM((comandoLCD4 << 4) & 0xf0);
}

void Borra_Pant4b(void)                 /* Función para borrar pantalla en    */
{                                       /* modo de 4 bits.                    */
    Envia_Com4b(BP);
    retardo_ms(2);
}

void Retorno_Carro4b(void)              /* Función para realizar retorno de   */
{                                       /* en modo de 4 bits.                 */
    Envia_Com4b(RC);
    retardo_ms(2);
}

void Conf_Modo_Ent4b(unsigned int modo) /* Coloca la dirección de la DDRAM    */
{                                       /* se quiera incrementar o decrementar*/
    Envia_Com4b(CME | modo);            /* también especifica el salto del    */
    retardo_us(40);                     /* cursor durante una lectura o       */
}                                       /* escritura de datos.                */

void Enc_Apa4b(unsigned int interr)     /* Enciende y apaga la pantalla, el   */
{                                       /* el cursor, también sirve para      */
    Envia_Com4b(EAP | interr);          /* hacer parpadear el cursor en la    */
    retardo_us(40);                     /* posición actual.                   */
}

void Desp_Cur4b(unsigned int direc)     /* Mueve el cursor o desplaza la      */
{                                       /* pantalla sin cambiar el contenido  */
    Envia_Com4b(CDD | direc);           /* de la DDRAM.                       */
    retardo_us(40);
}

void Conf_Func4b(unsigned int funcion)  /* Configura la longitud del bus de   */
{                                       /* de datos, el número de líneas de la*/
    Envia_Com4b(CF | funcion);          /* pantalla y la fuente de los        */
    retardo_us(40);                     /* caracteres.                        */
}

void Conf_CGRAM4b(unsigned int dirC)    /* Establece la dirección de la CGRAM */     
{                                       /* para poder enviar o recibr datos a */
    Envia_Com4b(ECGR | dirC);           /* esa dirección.                     */
    retardo_us(40);                     
}

void Conf_DDRAM4b(unsigned int dirD)    /* Establece la dirección de la DDRAM */
{                                       /* para poder enviar o recibir datos a*/
    Envia_Com4b(EDDR | dirD);           /* esa dirección.                     */
    retardo_us(40);
}

void Lee_BF4b(unsigned int dirB)        /* Lee la bandera de ocupado y también*/
{                                       /* lee el valor del contador de       */
    Envia_Com_RAM4b(LBFD | dirB);           /* direcciones.                       */
    retardo_us(5);
}

void Esc_DCRAM4b(char *fra, char anim)  /* Escribe dato a la DDRAM o CGRAM e  */
{   
    switch(anim)
    {
        case 0:
        {
            Mensaje_Ent(fra);
            break;
        }
        case 1:
        {
            Mensaje_Izq(fra);
            retardo_ms(250);
            break;
        }
        case 2:
        {
            Mensaje_Der(fra);
            retardo_ms(250);
            break;
        }
        default:
        {
            Mensaje_Ent("   Sin opción   ");
            break;
        }
    }

}                                      

/* Debo seguir trabajando en las función Lee_DCRAM4b para retornar el dato    */

//Lee_DCRAM4b(unsigned int dat)           /* Lee dato de la DDRAM o CGRAM e     */
//{                                       /* incrementa o decrementa el contador*/
//    Envia_Com4b(LDCD | dat)             /* de direcciones.                    */
//    retardo_us(40);
//}

void Posicion_Cur4b(char fila, char columna)
{
    switch(fila)
    {
        
        case 1:
        {
            Envia_Com4b(EDDR | (lin_1_i + columna));
            break;  
        }
        case 2:
        {
            Envia_Com4b(EDDR | (lin_2_i + columna));
            break; 
        }
        case 3:
        {
            Envia_Com4b(EDDR | (lin_3_i + columna));
            break; 
        }
        case 4:
        {
            Envia_Com4b(EDDR | (lin_4_i + columna));
            break; 
        }
        default:
        {
            Envia_Com4b(EDDR | (lin_1_i + columna));
            break;  
        }
    }
}

void Mensaje_Ent(char *mensaje)         /* Función para imprimir el mensaje   */
{                                       /* sin animaciones.                   */
    while(*mensaje)
    {
        Envia_Com_RAM4b(*(mensaje++));
        retardo_us(40);
    }
}

void Mensaje_Izq(char *mensaje)         /* Prototipo de función para imprimir */
{                                       /* el mensaje con los caracteres      */
    unsigned char c, dim = Dim_Mensaje(mensaje);/* desplazándose              */
    for(c = 0; c <= dim; c++)           /* desde la izquierda hacia la        */
    {                                   /* derecha.                           */
        Desp_Cur4b(lin_1_i);
        unsigned char desplaza = 0;
        for(desplaza = dim-c; desplaza <= dim; desplaza++)
        {
            Envia_Com_RAM4b(mensaje[desplaza]);
            retardo_ms(10);
        }
    }
}

void Mensaje_Der(char *mensaje)         /* Prototipo de función para imprimir */
{                                       /* el mensaje con los caracteres      */
   unsigned char c, dim = Dim_Mensaje(mensaje);/* desplazándose     */
    Desp_Cur4b(lin_1_f);
    for(c = 0; c <= dim; c++)           /* desde la izquierda hacia la        */
    {                                   /* derecha.                           */
        unsigned char desplaza = 0;
        for(desplaza = 0; desplaza <= dim; desplaza++)
        {
            Envia_Com_RAM4b(mensaje[desplaza]);
            retardo_ms(10);
        }
        Desp_Cur4b(lin_1_f - c);
    }
}

void Menu(void)                         /* Función para mostrar el menú       */
{                                       /* inicial en pantalla.               */
    short lineaM;
    Borra_Pant4b();
    for(lineaM = 0; lineaM < 4;lineaM++)
    {
        Posicion_Cur4b(lineaM+1,1);
        Mensaje_Ent((char*) menu_i[lineaM]);
    }
}

void Selec_MenuS(char posMenu)          /* Función para desplazarse a través  */
{                                       /* de las funciones del menu principal*/
    if(posMenu == 'A')                  /* con el fin de seleccionar el menú  */
    {                                   /* secundario a deplegar.             */
        selMenu++;
        Posicion_Cur4b(selMenu - 1,0);
        Mensaje_Ent((char*) " ");
    }
    else if(posMenu == 'B')
    {
        selMenu--;
        Posicion_Cur4b(selMenu + 1,0);
        Mensaje_Ent((char*) " ");
    }
    switch(selMenu)
    {
        case 5:
        {
            selMenu = 1;
            break;
        }
        case 0:
        {
            selMenu = 4;
            break;
        }
    }
    Posicion_Cur4b(selMenu,0);
    Mensaje_Ent((char*) ">");
}

void Menu_S(uint8_t funcion)            /* Función para desplegar los menú    */
{                                       /* secundarios.                       */
    short lineaS;
    static uint8_t colMenu_r = 9;       /* Variable para almacenar la posición
                                         * en la que aparece la segunda columna
                                         * del menú secundario 1.             */
    Borra_Pant4b();
    switch(funcion)
    {
        case 1:
        {
            for(lineaS = 0; lineaS < 4; lineaS++)
            {
                Posicion_Cur4b(lineaS+1,1);
                if(!lineaS)
                {
                    Mensaje_Ent((char*) menu_r[lineaS]);
                }
                else
                {
                    Mensaje_Ent((char*) menu_r[lineaS]);
                    Posicion_Cur4b(lineaS+1,colMenu_r);
                    Mensaje_Ent((char*) menu_r[lineaS+3]);
                }
            }
        }
        break;
        case 2:
        {
            for(lineaS = 0; lineaS < 4; lineaS++)
            {
                Posicion_Cur4b(lineaS+1,0);
                Mensaje_Ent((char*) menu_m[lineaS]);
            }
        }
        break;
        default:
        {
            Posicion_Cur4b(2,0);
            Mensaje_Ent((char*) "   No hay menú");
        }
        break;
    }
}

void cpos_Menu_S(uint8_t funcion, uint8_t boton)/* Función para mover el      */
{                                       /* cursor a la posición del parámetro */
                                        /* a llenar.                          */
    switch(funcion)
    {
        case 1:
        {
            Opcion_RTC(boton);
        }
        break;
        case 2:
        {
            Opcion_PID(boton);
        }
        default:
        {
            //Nada.
        }
    }
}

void Opcion_RTC(uint8_t vRTC)           /* Función para despliegue            */
{                                       /* y almacenamiento de los parámetros */
    static uint8_t cFila_1 = 2, cCol_1 = 4, cParam = 1;/* correspondientes al */
    switch(vRTC)                        /* RTC.                               */
    {
        case (uint8_t) 'D':
        {
            cFila_1++;
            cParam++;
            if((cFila_1 == 5) && (cCol_1 == 4))
            {
                cFila_1 = 2;
                cCol_1 = 12;
            }
            if((cFila_1 == 5) && (cCol_1 == 12))
            {
                cFila_1 = 2;
                cCol_1 = 4;
            }
        }       
        break;
        case (uint8_t) 'C':
        {
            cFila_1--;
            cParam--;
            if(!cParam)
            {
                cParam = 6;
            }
            if((cFila_1 == 1) && (cCol_1 == 4))
            {
                cFila_1 = 4;
                cCol_1 = 12;
            }
            if((cFila_1 == 1) && (cCol_1 == 12))
            {
                cFila_1 = 4;
                cCol_1 = 4;
            }
        }
        break;
        default:                        /* El caso default tiene implementado */
        {                               /* el llenado de los parámetros       */
            Posicion_Cur4b(cFila_1,cCol_1);/* correspondientes del menú       */
            Mensaje_Ent((char*) Alma_RTC(cParam,vRTC));/* secundario          */
        }                               /* seleccionado.                      */
        break;
    }    
    Posicion_Cur4b(cFila_1,cCol_1);
}

void Opcion_PID(uint8_t vPID)           /* Función para despliegue            */
{                                       /* y almacenamiento de los parámetros */
    static uint8_t cFila_2 = 2, cCol_2 = 3, cParam_2 = 1;/* correspondientes  */
    switch(vPID)                        /* al PID.                            */
    {
        case (uint8_t) 'D':
        {
            cFila_2++;
            cParam_2++;
            if(cParam_2 == 4)
            {
                cParam_2 = 1;
            }
            if(cFila_2 == 5)
            {
                cFila_2 = 2;
            }
        }       
        break;
        case (uint8_t) 'C':
        {
            cFila_2--;
            cParam_2--;
            if(!cParam_2)
            {
                cParam_2 = 3;
            }
            if(cFila_2 == 1)
            {
                cFila_2 = 4;
            }
        }
        break;
        default:                        /* El caso default tiene implementado */
        {                               /* el llenado de los parámetros       */
            if(cCol_2 == 7)
            {
                cCol_2 = 3;
            }
            Posicion_Cur4b(cFila_2,cCol_2);/* correspondientes del menú       */
            Mensaje_Ent((char*) Alma_PID(cParam_2,vPID));/* secundario        */
        }                               /* seleccionado.                      */
        break;
    }    
    Posicion_Cur4b(cFila_2,cCol_2);
}