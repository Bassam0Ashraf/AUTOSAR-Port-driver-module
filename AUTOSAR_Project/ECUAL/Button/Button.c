/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.c
 *
 * Description: Source file for Button Module.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/
#include "MCAL/Dio/Dio.h"
#include "Button.h"

/*******************************************************************************
 *                  Special Global variable for "Button.c" only                *
 *******************************************************************************/

static uint8 g_button_state = BUTTON_RELEASED;

/*******************************************************************************
 *                          Function definitions                               *
 *******************************************************************************/

/* Description: Read the Button state Pressed/Released */
uint8 Button_GetState(void)
{
    return g_button_state;
}

/************************************************************************************************************/

/*
 * Description: This function is called every 20ms by OS Task and it responsible for Updating
 *              the BUTTON State. it should be in a PRESSED State if the button is pressed for 60ms.
 *              and it should be in a RELEASED State if the button is released for 60ms.
 */

void Button_RefreshState(void)
{
    uint8 state = Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX);

    /* Count the number of Pressed times increment if the switch pressed for 20 ms */
    static uint8 g_Pressed_Count  = 0;

    /* Count the number of Released times increment if the switch released for 20 ms */
    static uint8 g_Released_Count = 0;

    if(state == BUTTON_PRESSED)
    {
        g_Pressed_Count++;
        g_Released_Count = 0;
    }
    else
    {
        g_Released_Count++;
        g_Pressed_Count = 0;
    }

    if(g_Pressed_Count == 3)
    {
        g_button_state = BUTTON_PRESSED;
        g_Pressed_Count       = 0;
        g_Released_Count      = 0;
    }
    else if(g_Released_Count == 3)
    {
        g_button_state = BUTTON_RELEASED;
        g_Released_Count      = 0;
        g_Pressed_Count       = 0;
    }
}

/************************************************************************************************************/
