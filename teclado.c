#include "teclado.h"
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
    if(!keyboard->t1PrevState && keyboard->t1ActState)
    {
        bldc.initMotor = true;
    }
    if(!keyboard->t2PrevState && keyboard->t2ActState)
    {
        bldc.iMotor = true;
    }
//    Keyboard_Actual_State(keyboard);
//    if(keyboard->t1PrevState && !keyboard->t1ActState)
//    {
//        keyboard->t1PrevState = keyboard->t1ActState;
//    }
//    if(!keyboard->t1PrevState && keyboard->t1ActState)
//    {
//        bldc.initMotor = true;
//        keyboard->t1PrevState = keyboard->t1ActState;
//    }
//    
//    if(keyboard->t2PrevState && !keyboard->t2ActState)
//    {
//        keyboard->t2PrevState = keyboard->t2ActState;
//    }
//    if(!keyboard->t2PrevState && keyboard->t2ActState)
//    {
//        bldc.initMotor = false;
//        keyboard->t2PrevState = keyboard->t2ActState;
//    }
//    if(keyboard->t3PrevState && !keyboard->t3ActState)
//    {
//        keyboard->t3PrevState = keyboard->t3ActState;
//    }
//    if(!keyboard->t3PrevState && keyboard->t3ActState)
//    {
//        bldc.iMotor = true;
//        keyboard->t3PrevState = keyboard->t3ActState;      
//    }    
//    if(keyboard->t4PrevState && !keyboard->t4ActState)
//    {
//        keyboard->t4PrevState = keyboard->t4ActState;
//    }
//    if(!keyboard->t4PrevState && keyboard->t4ActState)
//    {
//        bldc.initMotor = false;
//        keyboard->t4PrevState = keyboard->t4ActState;       
//    }    
}