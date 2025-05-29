 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver Registers
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#ifndef PORT_REGS_H_
#define PORT_REGS_H_

#include "Std_Types.h"

/******************************************************************************
 *                          Ports registers base address                      *
 ******************************************************************************/
#define PORTA_BASE_ADDRESS                  ( (volatile uint32*)0x40004000 )
#define PORTB_BASE_ADDRESS                  ( (volatile uint32*)0X40005000 )
#define PORTC_BASE_ADDRESS                  ( (volatile uint32*)0X40006000 )
#define PORTD_BASE_ADDRESS                  ( (volatile uint32*)0X40007000 )
#define PORTE_BASE_ADDRESS                  ( (volatile uint32*)0X40024000 )
#define PORTF_BASE_ADDRESS                  ( (volatile uint32*)0X40025000 )

/******************************************************************************
 *                              Register Offsets                              *
 ******************************************************************************/
#define GPIO_DATA_REG_OFFSET            ( 0X3FC )
#define GPIO_DIR_REG_OFFSET             ( 0X400 )
#define GPIO_AFSEL_REG_OFFSET           ( 0X420 )
#define GPIO_PUR_REG_OFFSET             ( 0X510 )
#define GPIO_PDR_REG_OFFSET             ( 0X514 )
#define GPIO_DEN_REG_OFFSET             ( 0X51C )
#define GPIO_LOCK_REG_OFFSET            ( 0X520 )
#define GPIO_CR_REG_OFFSET              ( 0X524 )
#define GPIO_AMSEL_REG_OFFSET           ( 0X528 )
#define GPIO_PCTL_REG_OFFSET            ( 0X52C )


#endif /* PORT_REGS_H_ */
