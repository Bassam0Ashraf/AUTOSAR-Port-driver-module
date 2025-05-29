 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Gpt.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - SysTick Timer Driver.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/


/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "Gpt.h"
#include "Gpt_Regs.h"

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/

#define SYSTICK_CTRL_COUNT_FLAG_MASK    0x00010000         // Count flag bit mask in SysTick CTRL register.
#define SYSTICK_CTRL_ENABLE_MASK        0x00000001         // Enable bit mask in SysTick CTRL register.
#define SYSTICK_PRIORITY_MASK           0x1FFFFFFF         // Priority bit mask in NVIC_SYSTEM_PRI3_REG.
#define SYSTICK_INTERRUPT_PRIORITY      3
#define SYSTICK_PRIORITY_BITS_POS       29

/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/

/* Global pointer to function used to point upper layer functions to be used in Call Back */
static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt use to call
 * the call-back function.
 * ********************************************************************/
void SysTick_Handler(void)
{
    /* Check if the SysTick_SetCallBack is already called */
    if(g_SysTick_Call_Back_Ptr != NULL_PTR)
    {
        (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
}


/************************************************************************************
* Service Name: SysTick_Init
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
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;                         /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999 * a_TimeInMilliSeconds;         /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;                         /* Clear the Current Register value */
    /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
}


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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;                                            // Disable the SysTick Timer by Clear the ENABLE Bit.

    SYSTICK_RELOAD_REG  = 15999 * a_TimeInMilliSeconds;                            // Set the Reload value to count Seconds.

    SYSTICK_CURRENT_REG = 0;                                            // Clear the Current Register value.

    SYSTICK_CTRL_REG   |= 0x05;                                         // Enable SysTick timer & choose the clock source to be system clock.

    while( !(SYSTICK_CTRL_REG  &  SYSTICK_CTRL_COUNT_FLAG_MASK) );      // Wait until the COUNT flag = 1.

    SYSTICK_CTRL_REG    = 0;                                            // Disable the SysTick Timer by Clear the ENABLE Bit.

    SYSTICK_RELOAD_REG  = 0;                                            // Set the Reload value 0.

    SYSTICK_CURRENT_REG = 0;                                            // Clear the Current Register value.
}


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
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG  &= ~ SYSTICK_CTRL_ENABLE_MASK; /* Disable the SysTick Timer by Clear the ENABLE Bit */
}


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
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG  |=  SYSTICK_CTRL_ENABLE_MASK;               // Start timer.
}


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
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG    = 0;        // Disable the SysTick Timer by Clear the ENABLE Bit.

    SYSTICK_RELOAD_REG  = 0;        // Set the Reload value 0.

    SYSTICK_CURRENT_REG = 0;        // Clear the Current Register value.

    g_SysTick_Call_Back_Ptr = NULL_PTR;
}


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
void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}
