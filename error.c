#include "error.h"
#include "motor.h"

errCod errorCod = NO_ERROR;

void Error_Handler(uint8_t cod)
{
    errorCod = cod;
    if((cod >= NO_ERROR) || (cod <= ERROR_DIR))
    {
        Motor_Error();
    }
}