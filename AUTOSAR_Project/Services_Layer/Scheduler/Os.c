/******************************************************************************
 *
 * Module: OS
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#include "Os.h"
#include "Application/App.h"
#include "ECUAL/Button/Button.h"
#include "ECUAL/Led/Led.h"
#include "MCAL/GPT/Gpt.h"

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")


/*******************************************************************************
 *                  Special Global variable for "Os.c" only                    *
 *******************************************************************************/

/* Global variable store the Os Time */
static uint8 g_Time_Tick_Count = 0;

/* Global variable to indicate the the timer has a new tick */
static uint8 g_New_Time_Tick_Flag = 0;

/*******************************************************************************
 *                          Function definitions                               *
 *******************************************************************************/

/* Description:
 * Function responsible for:
 * 1. Enable Interrupts
 * 2. Start the Os timer
 * 3. Execute the Init Task
 * 4. Start the Scheduler to run the tasks
 */

void Os_start(void)
{
    /* Global Interrupts Enable */
    Enable_Exceptions();

    /* 
     * Set the Call Back function to call Os_NewTimerTick
     * this function will be called every SysTick Interrupt (20ms)
     */
    SysTick_SetCallBack(Os_NewTimerTick);

    /* Start SysTickTimer to generate interrupt every 20ms */
    SysTick_Init(OS_BASE_TIME);

    /* Execute the Init Task */
    Init_Task();

    /* Start the Os Scheduler */
    Os_Scheduler();
}

/*********************************************************************************************/

/* Description: Function called by the Timer Driver in the MCAL layer using the call back pointer */
void Os_NewTimerTick(void)
{
    /* Increment the Os time by OS_BASE_TIME */
    g_Time_Tick_Count   += OS_BASE_TIME;

    /* Set the flag to 1 to indicate that there is a new timer tick */
    g_New_Time_Tick_Flag = 1;
}

/*********************************************************************************************/

/* Description: The Engine of the Os Scheduler used for switch between different tasks */
void Os_Scheduler(void)
{
    while(1)
    {
        /* Code is only executed in case there is a new timer tick */
        if(g_New_Time_Tick_Flag == 1)
        {
            switch(g_Time_Tick_Count)
            {
            case 20:
                    Button_Task();
                    g_New_Time_Tick_Flag = 0;
                    break;
            case 100:
                    Button_Task();
                    g_New_Time_Tick_Flag = 0;
                    break;
            case 40:
                   Button_Task();
                   Led_Task();
                   g_New_Time_Tick_Flag = 0;
                   break;
            case 80:
                    Button_Task();
                    Led_Task();
                    g_New_Time_Tick_Flag = 0;
                    break;
            case 60:
                    Button_Task();
                    App_Task();
                    g_New_Time_Tick_Flag = 0;
                    break;
            case 120:
                    Button_Task();
                    App_Task();
                    Led_Task();
                    g_New_Time_Tick_Flag = 0;
                    g_Time_Tick_Count = 0;
                    break;
            }
        }

    }

}
/*********************************************************************************************/
