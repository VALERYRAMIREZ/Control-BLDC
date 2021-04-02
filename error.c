#include "error.h"
#include "motor.h"
#include "mcc_generated_files/system.h"

errCod errorCod = NO_ERROR;

void Error_Handler(uint8_t cod)
{
//    TMR3_Start();
    ERROR_LED_SetHigh();
    errorCod = cod;
    if((cod > NO_ERROR) || (cod <= ERROR_DIR))
    {
        Motor_Error();
    }
}