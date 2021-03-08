/* 
 * File:                LCD_44780.h
 * Author:              Valery Ramirez
 * Comments:            Configuración de control para pantalla LCD basada en
 *                      el controlador HD44780
 * Revision history:    N/A
 */
  
#ifndef LCD_44780_H
#define	LCD_44780_H

#include <xc.h> 

/* Definición de terminales para el control de la pantalla LCD. */

#define         RS      PORTDbits.RD10
#define         RW      PORTDbits.RD9
#define         E       PORTDbits.RD8
#define         D7      PORTDbits.RD7
#define         D6      PORTDbits.RD6
#define         D5      PORTDbits.RD5
#define         D4      PORTDbits.RD4
#define         D3      PORTDbits.RD3
#define         D2      PORTDbits.RD2
#define         D1      PORTDbits.RD1
#define         D0      PORTDbits.RD0

/* Definición de constantes para usar en los comandos de control para la
   pantalla LCD                                                               */

#define         BP      0x01            /* Borrar pantalla                    */
#define         RC      0x02            /* Retorno de carro                   */
#define         CME     0x04            /* Configuración del modo de entrada  */
#define         EAP     0x08            /* Encender-apagar pantalla           */
#define         CDD     0x10            /* Desplazamiento del cursor o display*/
#define         CF      0x20            /* Configuración de función           */
#define         ECGR    0x40            /* Establecer dirección de la CGRAM   */
#define         EDDR    0x80            /* Establecer dirección de la DDRAM   */
#define         LBFD    0x100           /* Leer bandera de ocupado y contenido
                                         * del contador.                      */
#define         EDCD    0x200           /* Escribe dato a la DD o CG RAM e
                                           incrementa o decrementa el contador
                                           de dirección (AC).                 */
#define         LDCD    0x300           /* Lee dato de la DD o CG RAM e
                                           incrementa o decrementa el contador
                                           de dirección (AC).                 */

/* Definición de posición inicial de las líneas para la pantalla de 4 líneas
   por 16 caracteres.                                                         */

#define         lin_1_i 0x80
#define         lin_1_f 0x8f
#define         lin_2_i 0xc0
#define         lin_2_f 0xcf
#define         lin_3_i 0x90
#define         lin_3_f 0x9f
#define         lin_4_i 0xd0
#define         lin_4_f 0xdf

/* Definición de constantes para la selección de animación en la pantalla     */

#define         NOR     0           /* Mensaje impreso completo al instante.  */
#define         IZQ     1           /* Mensaje impreso de izquierda a derecha.*/
#define         DER     2           /* Mensaje impreso de derecha a izquiera. */
#define         ARR     3           /* Mensaje impreso de arriba a abajo.     */
#define         ABA     4           /* Mensaje impreso de abaja a arriba.     */

/* Definición de prototipos de función para el control de la pantalla LCD.    */

void Inicia_LCD4(void);                 /* Prototipo de función para
                                         * inicializar la pantalla LCD.       */

void Envia_Com(unsigned int comandoLCD);/* Prototipo de función para enviar
                                         * un comando a la pantalla LCD.      */

void Envia_Com_RAM(unsigned int ComandoLCD);/* Prototipo de función para
                                         * enviar un comando de escritura a la
                                         * CGRAM o DDRAM de la pantalla LCD en
                                         * ormato de 4 bits.                  */

void Envia_Com4b(unsigned int comandoLCD4);/* Prototipo de función para enviar
                                         * un comando a la pantalla LCD en
                                         * formato de 4 bits.                 */

void Envia_Com_RAM4b(unsigned int comandoLCD4);/* Prototipo de función para
                                         * enviar un comando de manipulación de
                                         * la CGRAM o DDRAM con la pantalla en
                                         * modo de 4 bits.                    */

void Borra_Pant4b(void);                /* Prototipo de función para borrar la
                                         * pantalla LCD.                      */

void Retorno_Carro4b(void);             /* Prototipo de función para hacer el
                                         * retorno de carro en modo de 4 bits.*/

void Conf_Modo_Ent4b(unsigned int modo);/* Prototipo de función para          */
                                        /* configurar el contador de dirección*/
                                        /* además de de especificar el        */
                                        /* el deplazamiento de la pantalla o  */
                                        /* cursor durante una escritura o     */
                                        /* de datos.                          */

void Enc_Apa4b(unsigned int interr);    /* Prototipo de función para encender */
                                        /* y apagar la pantalla, también      */
                                        /* configura el parpadeo del caracter */
                                        /* en la posición del cursor.         */

void Desp_Cur4b(unsigned int direc);    /* Prototipo de función para desplazar*/
                                        /* el cursor sin cambiar el contenido */
                                        /* de la DDRAM.                       */

void Conf_Func4b(unsigned int funcion);  /* Prototipo de función para          */
                                        /* establecer la logntud del bus de   */
                                        /* datos, el número de líneas de la   */
                                        /* pantalla y el tamaño de los        */
                                        /* caracteres.                        */

void Conf_CGRAM4b(unsigned int dirC);   /* Prototipo de función para          */
                                        /* establecer la dirección de la CGRAM*/

void Conf_DDRAM4b(unsigned int dirD);   /* Prototipo de función para          */
                                        /* establecer la dirección de la CGRAM*/

/* Debo seguir trabajando en las función Lee_BF4b para retornar el dato       */
//Lee_BF4b(unsigned int dirB);            /* Prototipo de función para y leer la*/
//                                        /* bandera de ocupado y el contenido  */
//                                        /* de el contador de direcciones      */

void Esc_DCRAM4b(char *fra, char anim); /* Prototipo de función para          */
                                        /* escribir datos a la DDRAM o CGRAM, */
                                        /* e incrementar o decrementar el     */
                                        /* contador de direcciones.           */

/* Debo seguir trabajando en las función Lee_DCRAM4b para retornar el dato    */

//Lee_DCRAM4b(unsigned int dat)           /* Lee dato de la DDRAM o CGRAM e     */
//{                                       /* incrementa o decrementa el contador*/
//    Envia_Com4b(LDCD | dat)             /* de direcciones.                    */
//    retardo_us(40);
//}                       */

void Posicion_Cur4b(char fila, char columna);/* Prototipo de función para mover
                                         * el cursor hacia una dirección.     */

void Mensaje_Ent(char *mensaje);        /* Prototipo de función para imprimir
                                         * el mensaje completo sin animación. */

void Mensaje_Izq(char *mensaje);        /* Prototipo de función para imprimir
                                         * el mensaje con los caracteres
                                         * apareciendi de izquierda a derecha.*/

void Mensaje_Der(char *mensaje);        /* Prototipo de función para imprimir
                                         * el mensaje con los caracteres
                                         * apareciendo de derecha a izquierda.*/

void Menu(void);                        /* Prototipo de función para seleccionar
                                         * el menú a desplegar en la panalla
                                         * LCD.                               */

void Selec_MenuS(char posMenu);         /* Prototipo de función para seleccionar
                                         * el menú secundario a deplegar.     */

void Menu_S(uint8_t funcion);           /* Prototipo de función para imprimir */
                                        /* los menúes secundarios.            */

void cpos_Menu_S(uint8_t funcion, uint8_t boton);/* Prototipo de función para    */
                                        /* el cursor en la posición del       */
                                        /* parámetro a llenar.                */

void Opcion_RTC(uint8_t vRTC);          /* Prototipo de función para despliegue
                                         * y almacenamiento de los parámetros
                                         * correspondientes al RTC.           */

void Opcion_PID(uint8_t vPID);          /* Prototipo de función para despliegue            
                                         * y almacenamiento de los parámetros
                                         * correspondientes al PID.           */
                                                
#endif	/* LCD_44780_H */
