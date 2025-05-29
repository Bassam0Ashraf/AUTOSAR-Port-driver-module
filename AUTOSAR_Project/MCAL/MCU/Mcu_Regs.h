 /******************************************************************************
 *
 * Module: MCU
 *
 * File Name: Mcu_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - MCU Registers
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#ifndef MCAL_MCU_MCU_REGS_H_
#define MCAL_MCU_MCU_REGS_H_

#include "Std_Types.h"

/*****************************************************************************
                        System Control Registers
*****************************************************************************/

#define SYSCTL_RCGCGPIO_REG       ( *((volatile uint32 *)0x400FE608) )
#define SYSCTL_PRGPIO_REG         ( *((volatile uint32 *)0x400FEA08) )

#endif /* MCAL_MCU_MCU_REGS_H_ */
