#include "teclado.h"
#include "error.h"
#include "motor.h"

keyboard keys;

void Keyboard_Previous_State(keyboard *key)
{
    key->t1PrevState = TEC4_GetValue();
    key->t2PrevState = TEC5_GetValue();
    key->t3PrevState = TEC6_GetValue();
    key->t4PrevState = TEC7_GetValue();    
}

void Keyboard_Actual_State(keyboard *key)
{
    key->t1ActState = TEC4_GetValue();
    key->t2ActState = TEC5_GetValue();
    key->t3ActState = TEC6_GetValue();
    key->t4ActState = TEC7_GetValue();      
}

void Keyboard_Update_Button(keyboard *keyboard)
{
    if(!keyboard->t1PrevState && keyboard->t1ActState && (errorCod == NO_ERROR))
    {
        bldc.initMotor ^= 1;
    }
    if(!keyboard->t2PrevState && keyboard->t2ActState && bldc.initMotor)
    {
        bldc.iMotor ^= 1;
    }
    if(!keyboard->t3PrevState && keyboard->t3ActState)
    {
        bldc.sDir ^= 1;
    }   
}