/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.h
 *
 * Description: Header file for Led Module.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/
#ifndef LED_H
#define LED_H

#include "Led_Cfg.h"

/* Description: Set the LED state to ON */
void Led_SetOn(void);


/* Description: Set the LED state to OFF */
void Led_SetOff(void);


/*Description: Toggle the LED state */
void Led_Toggle(void);


/* Description: Refresh the LED state */
void Led_RefreshOutput(void);

#endif /* LED_H */
