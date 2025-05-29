/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_PBcfg.h
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#ifndef MCAL_PORT_PORT_PBCFG_H_
#define MCAL_PORT_PORT_PBCFG_H_


/* Module Version 1.0.0 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/* AUTOSAR Version 4.0.3 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION      (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION      (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION      (3U)

/*******************************************************************************
 *                      File Includes And Version Checking                     *
 *******************************************************************************/

/* Include the Port.h file and check on the AUTOSAR and software version compatibility */
#include "Port.h"

/* checking the software version compatibility */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBCfg.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBCfg.h does not match the expected version"
#endif


extern const Port_ConfigType Port_PinsConfigurations [NUMBER_OF_PORT_PINS];

#endif /* MCAL_PORT_PORT_PBCFG_H_ */
