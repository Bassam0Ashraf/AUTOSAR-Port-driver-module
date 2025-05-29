 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Gpt.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - SysTick Timer Driver.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#ifndef GPT_H
#define GPT_H

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "Std_Types.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Tick_Time - Time in miliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick Timer configuration to count n miliseconds:
*              - Set the Reload value
*              - Enable SysTick Timer with System clock 16Mhz
*              - Enable SysTick Timer Interrupt and set its priority
************************************************************************************/	
void SysTick_Init(uint16 a_TimeInMilliSeconds);


/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): a_TimeInMilliSeconds - Time in MilliSeconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time
 * in milliseconds using polling or busy-wait technique. The function
 * should exit when the time is elapsed and stops the timer at the end.
 * ********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);


/************************************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Stop the SysTick Timer.
************************************************************************************/
void SysTick_Stop(void);


/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to start/resume the SysTick Timer.
 * ********************************************************************/
void SysTick_Start(void);


/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Deinitialize the SysTick Timer.
 * ********************************************************************/
void SysTick_DeInit(void);


/************************************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Ptr2Func - Call Back function address
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick Timer call back
************************************************************************************/
void SysTick_SetCallBack(void (*Ptr2Func)(void));

#endif /* GPT_H */
