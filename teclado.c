#include "teclado.h"
#include "motor.h"

keyboard keys;

void Keyboard_Previous_State(keyboard *key)
{
    key->pS.t1PrevState = TEC4_GetValue();
    key->pS.t2PrevState = TEC5_GetValue();
    key->pS.t3PrevState = TEC6_GetValue();
    key->pS.t4PrevState = TEC7_GetValue();    
}

void Keyboard_Actual_State(keyboard *key)
{
    key->aS.t1ActState = TEC4_GetValue();
    key->aS.t2ActState = TEC5_GetValue();
    key->aS.t3ActState = TEC6_GetValue();
    key->aS.t4ActState = TEC7_GetValue();      
}

void Keyboard_Check_State(keyboard *keyboard)
{  
    Keyboard_Actual_State(keyboard);
    if(keyboard->pS.t1PrevState && !keyboard->aS.t1ActState)
    {
        keyboard->pS.t1PrevState = keyboard->aS.t1ActState;
    }
    if(!keyboard->pS.t1PrevState && keyboard->aS.t1ActState)
    {
        bldc.initMotor = true;
        keyboard->pS.t1PrevState = true;
    }
    
    if(keyboard->pS.t2PrevState && !keyboard->aS.t2ActState)
    {
        keyboard->pS.t2PrevState = keyboard->aS.t2ActState;
    }
    if(!keyboard->pS.t2PrevState && keyboard->aS.t2ActState)
    {
        bldc.initMotor = false;
        keyboard->pS.t2PrevState = true;
    }
    if(keyboard->pS.t3PrevState && !keyboard->aS.t3ActState)
    {
        keyboard->pS.t3PrevState = keyboard->aS.t3ActState;
    }
    if(!keyboard->pS.t3PrevState && keyboard->aS.t3ActState)
    {
        bldc.iMotor = true;
        keyboard->pS.t3PrevState = true;      
    }    
    if(keyboard->pS.t4PrevState && !keyboard->aS.t4ActState)
    {
        keyboard->pS.t4PrevState = keyboard->aS.t4ActState;
    }
    if(!keyboard->pS.t4PrevState && keyboard->aS.t4ActState)
    {
        bldc.initMotor = false;
        keyboard->pS.t4PrevState = true;       
    }    
}