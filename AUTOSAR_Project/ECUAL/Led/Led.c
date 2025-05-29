/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#include "MCAL/Dio/Dio.h"
#include "Led.h"

/*******************************************************************************
 *                          Function definitions                               *
 *******************************************************************************/

/* Description: Set the LED state to ON */
void Led_SetOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/************************************************************************************************************/

/* Description: Set the LED state to OFF */
void Led_SetOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/************************************************************************************************************/

/*Description: Toggle the LED state */
void Led_Toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

/************************************************************************************************************/

/* Description: Refresh the LED state */
void Led_RefreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* Re-write the same value */
}

/************************************************************************************************************/
