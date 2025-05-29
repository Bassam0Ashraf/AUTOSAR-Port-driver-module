 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Gpt_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - GPT Driver Registers
 *
 * Author: Bassam Ashraf
 ******************************************************************************/
#ifndef MCAL_GPT_GPT_REGS_H_
#define MCAL_GPT_GPT_REGS_H_

#include "Std_Types.h"

/*****************************************************************************
                        Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          ( *((volatile uint32 *)0xE000E010) )
#define SYSTICK_RELOAD_REG        ( *((volatile uint32 *)0xE000E014) )
#define SYSTICK_CURRENT_REG       ( *((volatile uint32 *)0xE000E018) )

/*****************************************************************************
                        System Control Block Registers
*****************************************************************************/
#define NVIC_SYSTEM_PRI3_REG      ( *((volatile uint32 *)0xE000ED20) )

#endif /* MCAL_GPT_GPT_REGS_H_ */
