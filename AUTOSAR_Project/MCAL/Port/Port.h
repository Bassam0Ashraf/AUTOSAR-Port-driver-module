 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Bassam Ashraf
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* The vendors id */
#define PORT_VENDOR_ID                       (1000U)

/* Port Module Id */
#define PORT_MODULE_ID                       (125U)

/* Port Instance Id */
#define PORT_INSTANCE_ID                     (0U)

/* Module Version 1.0.0 */
#define PORT_SW_MAJOR_VERSION                (1U)
#define PORT_SW_MINOR_VERSION                (0U)
#define PORT_SW_PATCH_VERSION                (0U)

/* AUTOSAR Version 4.0.3 */
#define PORT_AR_RELEASE_MAJOR_VERSION        (4U)
#define PORT_AR_RELEASE_MINOR_VERSION        (0U)
#define PORT_AR_RELEASE_PATCH_VERSION        (3U)


/* Macros for Port Status */
#define PORT_INITIALIZED                     (1U)
#define PORT_NOT_INITIALIZED                 (0U)

/*******************************************************************************
 *                      File Includes And Version Checking                     *
 *******************************************************************************/

/* Include the configuration file and check on the AUTOSAR and software version compatibility */
#include "Port_Cfg.h"

/* checking the software version compatibility between configuration file of port and port file */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility between configuration file of port and port file */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Include the standard types file check the AUTOSAR version compatibility */
#include "Std_Types.h"

/* checking the SW version compatibility between std_Types and Port */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* The "Common_Macros.h" is not AUTOSAR file so there is no version checking */
#include "Common_Macros.h"

/*******************************************************************************
 *                            DET Error Codes                                  *
 *******************************************************************************/

/* DET code to report invalid port pin id requested */
#define PORT_E_PARAM_PIN                    ( (uint8)0x0A )

/* DET code to report port pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE       ( (uint8)0X0B )

/* DET code to report when API service called with NULL pointer parameter (wrong parameter) */
#define PORT_E_PARAM_CONFIG                 ( (uint8)0X0C )

/* DET code to report when API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE           ( (uint8)0X0D )

#define PORT_E_MODE_UNCHANGEABLE            ( (uint8)0X0E )

/* DET code to report when API service called without module initialization */
#define PORT_E_UNINIT                       ( (uint8)0X0F )

/* DET code to report when APIs called with NULL pointer */
#define PORT_E_PARAM_POINTER                ( (uint8)0X10 )

/******************************************************************************
 *                          API Service Id Macros                             *
 ******************************************************************************/

/* Service ID for port init */
#define PORT_INIT_SID                       ( (uint8)0X00 )

/* Service ID for port set pin direction */
#define PORT_SET_PIN_DIRECTION_SID          ( (uint8)0X01 )

/* Service ID for port refresh port direction */
#define PORT_REFRESH_PORT_DIRECTION_SID     ( (uint8)0X02 )

/* Service ID for port get version info */
#define  PORT_GET_VERSION_INFO_SID          ( (uint8)0X03 )

/* Service ID for port set pin mode */
#define PORT_SET_PIN_MODE_SID               ( (uint8)0X04 )


/*******************************************************************************
 *                            Module Data Types                                *
 *******************************************************************************/

/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by PORT APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold pin level value */
typedef enum
{
    PORT_PIN_LEVEL_LOW,
    PORT_PIN_LEVEL_HIGH

}Port_PinLevelValue;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    INTERNAL_RESISTOR_OFF,
    INTERNAL_RESISTOR_PULL_UP,
    INTERNAL_RESISTOR_PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *	3. initial mode for pin --> DIO or CAN or ADC or ....
 *  4. the direction of pin --> INPUT or OUTPUT.
 *  5. the internal resistor --> Disable, Pull up or Pull down.
 *  6. Provide initial value for o/p pin --> Low or High.
 *  7. EN/DIS Digital mode for this pin.
 *  8. EN/DIS direction changeable during runtime.
 *  9. EN/DIS mode changeable during runtime.
 */
typedef struct 
{
    uint8 port_num;
    Port_PinType pin_num;
    Port_PinModeType pin_mode;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinLevelValue initial_level_value;
    boolean port_pin_digital;
    boolean port_pin_direction_changeable;
    boolean port_pin_mode_changeable;
}Port_ConfigType;

/***********************************************************************************
 *                               Port A Pins Macros                                *
 ***********************************************************************************/
#define PORT_A_ID                           ( (uint8)0 )

#define PORT_A_PIN_0                        ( (Port_PinType)0 )
#define PORT_A_PIN_1                        ( (Port_PinType)1 )
#define PORT_A_PIN_2                        ( (Port_PinType)2 )
#define PORT_A_PIN_3                        ( (Port_PinType)3 )
#define PORT_A_PIN_4                        ( (Port_PinType)4 )
#define PORT_A_PIN_5                        ( (Port_PinType)5 )
#define PORT_A_PIN_6                        ( (Port_PinType)6 )
#define PORT_A_PIN_7                        ( (Port_PinType)7 )

/***********************************************************************************
 *                               Port B Pins Macros                                *
 ***********************************************************************************/
#define PORT_B_ID                           ( (uint8)1 )

#define PORT_B_PIN_0                        ( (Port_PinType)0 )
#define PORT_B_PIN_1                        ( (Port_PinType)1 )
#define PORT_B_PIN_2                        ( (Port_PinType)2 )
#define PORT_B_PIN_3                        ( (Port_PinType)3 )
#define PORT_B_PIN_4                        ( (Port_PinType)4 )
#define PORT_B_PIN_5                        ( (Port_PinType)5 )
#define PORT_B_PIN_6                        ( (Port_PinType)6 )
#define PORT_B_PIN_7                        ( (Port_PinType)7 )

/***********************************************************************************
 *                               Port C Pins Macros                                *
 ***********************************************************************************/
#define PORT_C_ID                           ( (uint8)2 )

#define PORT_C_PIN_0                        ( (Port_PinType)0 )
#define PORT_C_PIN_1                        ( (Port_PinType)1 )
#define PORT_C_PIN_2                        ( (Port_PinType)2 )
#define PORT_C_PIN_3                        ( (Port_PinType)3 )
#define PORT_C_PIN_4                        ( (Port_PinType)4 )
#define PORT_C_PIN_5                        ( (Port_PinType)5 )
#define PORT_C_PIN_6                        ( (Port_PinType)6 )
#define PORT_C_PIN_7                        ( (Port_PinType)7 )

/***********************************************************************************
 *                               Port D Pins Macros                                *
 ***********************************************************************************/
#define PORT_D_ID                           ( (uint8)3 )

#define PORT_D_PIN_0                        ( (Port_PinType)0 )
#define PORT_D_PIN_1                        ( (Port_PinType)1 )
#define PORT_D_PIN_2                        ( (Port_PinType)2 )
#define PORT_D_PIN_3                        ( (Port_PinType)3 )
#define PORT_D_PIN_4                        ( (Port_PinType)4 )
#define PORT_D_PIN_5                        ( (Port_PinType)5 )
#define PORT_D_PIN_6                        ( (Port_PinType)6 )
#define PORT_D_PIN_7                        ( (Port_PinType)7 )

/***********************************************************************************
 *                               Port E Pins Macros                                *
 ***********************************************************************************/
#define PORT_E_ID                           ( (uint8)4 )

#define PORT_E_PIN_0                        ( (Port_PinType)0 )
#define PORT_E_PIN_1                        ( (Port_PinType)1 )
#define PORT_E_PIN_2                        ( (Port_PinType)2 )
#define PORT_E_PIN_3                        ( (Port_PinType)3 )
#define PORT_E_PIN_4                        ( (Port_PinType)4 )
#define PORT_E_PIN_5                        ( (Port_PinType)5 )

/***********************************************************************************
 *                               Port F Pins Macros                                *
 ***********************************************************************************/
#define PORT_F_ID                           ( (uint8)5 )

#define PORT_F_PIN_0                        ( (Port_PinType)0 )
#define PORT_F_PIN_1                        ( (Port_PinType)1 )
#define PORT_F_PIN_2                        ( (Port_PinType)2 )
#define PORT_F_PIN_3                        ( (Port_PinType)3 )
#define PORT_F_PIN_4                        ( (Port_PinType)4 )


/***********************************************************************************
 *                  Port pins index macros in the post build array                 *
 ***********************************************************************************/

#define PORT_A_PIN_0_INDEX                        ( (Port_PinType)0 )
#define PORT_A_PIN_1_INDEX                        ( (Port_PinType)1 )
#define PORT_A_PIN_2_INDEX                        ( (Port_PinType)2 )
#define PORT_A_PIN_3_INDEX                        ( (Port_PinType)3 )
#define PORT_A_PIN_4_INDEX                        ( (Port_PinType)4 )
#define PORT_A_PIN_5_INDEX                        ( (Port_PinType)5 )
#define PORT_A_PIN_6_INDEX                        ( (Port_PinType)6 )
#define PORT_A_PIN_7_INDEX                        ( (Port_PinType)7 )

#define PORT_B_PIN_0_INDEX                        ( (Port_PinType)8 )
#define PORT_B_PIN_1_INDEX                        ( (Port_PinType)9 )
#define PORT_B_PIN_2_INDEX                        ( (Port_PinType)10 )
#define PORT_B_PIN_3_INDEX                        ( (Port_PinType)11 )
#define PORT_B_PIN_4_INDEX                        ( (Port_PinType)12 )
#define PORT_B_PIN_5_INDEX                        ( (Port_PinType)13 )
#define PORT_B_PIN_6_INDEX                        ( (Port_PinType)14 )
#define PORT_B_PIN_7_INDEX                        ( (Port_PinType)15 )

#define PORT_C_PIN_0_INDEX                        ( (Port_PinType)16 )
#define PORT_C_PIN_1_INDEX                        ( (Port_PinType)17 )
#define PORT_C_PIN_2_INDEX                        ( (Port_PinType)18 )
#define PORT_C_PIN_3_INDEX                        ( (Port_PinType)19 )
#define PORT_C_PIN_4_INDEX                        ( (Port_PinType)20 )
#define PORT_C_PIN_5_INDEX                        ( (Port_PinType)21 )
#define PORT_C_PIN_6_INDEX                        ( (Port_PinType)22 )
#define PORT_C_PIN_7_INDEX                        ( (Port_PinType)23 )

#define PORT_D_PIN_0_INDEX                        ( (Port_PinType)24 )
#define PORT_D_PIN_1_INDEX                        ( (Port_PinType)25 )
#define PORT_D_PIN_2_INDEX                        ( (Port_PinType)26 )
#define PORT_D_PIN_3_INDEX                        ( (Port_PinType)27 )
#define PORT_D_PIN_4_INDEX                        ( (Port_PinType)28 )
#define PORT_D_PIN_5_INDEX                        ( (Port_PinType)29 )
#define PORT_D_PIN_6_INDEX                        ( (Port_PinType)30 )
#define PORT_D_PIN_7_INDEX                        ( (Port_PinType)31 )

#define PORT_E_PIN_0_INDEX                        ( (Port_PinType)32 )
#define PORT_E_PIN_1_INDEX                        ( (Port_PinType)33 )
#define PORT_E_PIN_2_INDEX                        ( (Port_PinType)34 )
#define PORT_E_PIN_3_INDEX                        ( (Port_PinType)35 )
#define PORT_E_PIN_4_INDEX                        ( (Port_PinType)36 )
#define PORT_E_PIN_5_INDEX                        ( (Port_PinType)37 )

#define PORT_F_PIN_0_INDEX                        ( (Port_PinType)38 )
#define PORT_F_PIN_1_INDEX                        ( (Port_PinType)39 )
#define PORT_F_PIN_2_INDEX                        ( (Port_PinType)40 )
#define PORT_F_PIN_3_INDEX                        ( (Port_PinType)41 )
#define PORT_F_PIN_4_INDEX                        ( (Port_PinType)42 )

/******************************************************************************
 *                      Typedef for the port pins modes                       *
 ******************************************************************************/

/*********************************************************
 *                      Port A Modes                     *
 *********************************************************/

/*
 PA0 Modes
*/
typedef enum {
    PORT_A0_MODE_DIO,            // GPIO
    PORT_A0_MODE_UART0_RX,       // UART0 RX
    PORT_A0_MODE_CAN1_RX  = 8    // CAN1 RX
} Port_A0_Modes;

/*
 PA1 Modes
*/
typedef enum {
    PORT_A1_MODE_DIO,            // GPIO
    PORT_A1_MODE_UART0_TX,       // UART0 TX
    PORT_A1_MODE_CAN1_TX  = 8    // CAN1 TX
} Port_A1_Modes;

/*
 PA2 Modes
*/
typedef enum {
    PORT_A2_MODE_DIO,            // GPIO
    PORT_A2_MODE_SSI0_CLK = 2    // SSI0 Clock
} Port_A2_Modes;

/*
 PA3 Modes
*/
typedef enum {
    PORT_A3_MODE_DIO,            // GPIO
    PORT_A3_MODE_SSI0_FSS = 2    // SSI0 Frame Select
} Port_A3_Modes;

/*
 PA4 Modes
*/
typedef enum {
    PORT_A4_MODE_DIO,            // GPIO
    PORT_A4_MODE_SSI0_RX = 2     // SSI0 Receive
} Port_A4_Modes;

/*
 PA5 Modes
*/
typedef enum {
    PORT_A5_MODE_DIO,            // GPIO
    PORT_A5_MODE_SSI0_TX = 2     // SSI0 Transmit
} Port_A5_Modes;

/*
 PA6 Modes
*/
typedef enum {
    PORT_A6_MODE_DIO,            // GPIO
    PORT_A6_MODE_I2C1_SCL = 3,   // I2C1 Clock
    PORT_A6_MODE_M1PWM2 = 5      // PWM Module 1, Generator 2
} Port_A6_Modes;

/*
 PA7 Modes
*/
typedef enum {
    PORT_A7_MODE_DIO,            // GPIO
    PORT_A7_MODE_I2C1_SDA = 3,   // I2C1 Data
    PORT_A7_MODE_M1PWM3 = 5      // PWM Module 1, Generator 3
} Port_A7_Modes;

/*********************************************************
 *                      Port B Modes                     *
 *********************************************************/

/*
 PB0 Modes
*/
typedef enum {
    PORT_B0_MODE_DIO,            // GPIO
    PORT_B0_MODE_UART1_RX,       // UART1 RX
    PORT_B0_MODE_T2_CCP0   = 7   // Timer2 Capture/Compare/PWM0
} Port_B0_Modes;

/*
 PB1 Modes
*/
typedef enum {
    PORT_B1_MODE_DIO,            // GPIO
    PORT_B1_MODE_UART1_TX,       // UART1 TX
    PORT_B1_MODE_T2_CCP1   = 7   // Timer2 Capture/Compare/PWM1
} Port_B1_Modes;

/*
 PB2 Modes
*/
typedef enum {
    PORT_B2_MODE_DIO,            // GPIO
    PORT_B2_MODE_I2C0_SCL  = 3,  // I2C0 Clock
    PORT_B2_MODE_T3_CCP0   = 7   // Timer3 Capture/Compare/PWM0
} Port_B2_Modes;

/*
 PB3 Modes
*/
typedef enum {
    PORT_B3_MODE_DIO,            // GPIO
    PORT_B4_MODE_SSI2_CLK  = 2,  // SSI2 Clock
    PORT_B4_MODE_M0PWM2    = 4,  // PWM Module 0, Generator 2
    PORT_B3_MODE_T3_CCP0   = 7,  // Timer3 Capture/Compare/PWM1
    PORT_B4_MODE_CAN0_RX         // CAN0 Receive
} Port_B3_Modes;

/*
 PB4 Modes
*/
typedef enum {
    PORT_B4_MODE_DIO,            // GPIO
    PORT_B4_MODE_SSI2CLK   = 2,  // SSI2 Clock
    PORT_B4_MODE_T1_CCP0   = 7   // Timer1 Capture/Compare/PWM0
} Port_B4_Modes;

/*
 PB5 Modes
*/
typedef enum {
    PORT_B5_MODE_DIO,            // GPIO
    PORT_B5_MODE_SSI2_FSS  = 2,  // SSI2 Frame Select
    PORT_B5_MODE_M0PWM3    = 4,  // PWM Module 0, Generator 3
    PORT_B5_MODE_T1_CCP1   = 7,  // Timer1 Capture/Compare/PWM1
    PORT_B5_MODE_CAN0_TX         // CAN0 Transmit
} Port_B5_Modes;

/*
 PB6 Modes
*/
typedef enum {
    PORT_B6_MODE_DIO,            // GPIO
    PORT_B6_MODE_SSI2_RX   = 2,  // SSI2 Receive
    PORT_B6_MODE_M0PWM0    = 4,  // PWM Module 0, Generator 0
    PORT_B6_MODE_T0_CCP0   = 7   // Timer0 Capture/Compare/PWM0
} Port_B6_Modes;

/*
 PB7 Modes
*/
typedef enum {
    PORT_B7_MODE_DIO,            // GPIO
    PORT_B7_MODE_SSI2_TX   = 2,  // SSI2 Transmit
    PORT_B7_MODE_M0PWM1    = 4,  // PWM Module 0, Generator 1
    PORT_B7_MODE_T0_CCP1   = 7   // Timer0 Capture/Compare/PWM1
} Port_B7_Modes;


/*********************************************************
 *                      Port C Modes                     *
 *********************************************************/

/*
 PC0 Modes
*/
typedef enum {
    PORT_C0_MODE_DIO,              // GPIO
    PORT_C0_MODE_TCK_SWCLK,        // JTAG TCK/SWCLK
    PORT_C0_MODE_T4_CCP0   = 7     // Timer4 Capture/Compare/PWM0
} Port_C0_Modes;

/*
 PC1 Modes
*/
typedef enum {
    PORT_C1_MODE_DIO,              // GPIO
    PORT_C1_MODE_TMS_SWDIO,        // JTAG TMS/SWDIO
    PORT_C1_MODE_T4_CCP1   = 7     // Timer4 Capture/Compare/PWM1
} Port_C1_Modes;

/*
 PC2 Modes
*/
typedef enum {
    PORT_C2_MODE_DIO,              // GPIO
    PORT_C2_MODE_TDI,              // JTAG TDI
    PORT_C2_MODE_T5_CCP0    = 7    // Timer5 Capture/Compare/PWM0
} Port_C2_Modes;

/*
 PC3 Modes
*/
typedef enum {
    PORT_C3_MODE_DIO,              // GPIO
   PORT_C3_MODE_TDO_SWO,           // JTAG TDO/SWO
    PORT_C3_MODE_T5CCP1    = 7     // Timer5 Capture/Compare/PWM1
} Port_C3_Modes;

/*
 PC4 Modes
*/
typedef enum {
    PORT_C4_MODE_DIO,                // GPIO
    PORT_C4_MODE_UART4_RX,           // UART4 RX
    PORT_C4_MODE_UART1_RX,           // UART1 RX
    PORT_C4_MODE_M0PWM6       = 4,   // PWM Module 0, Generator 6
    PORT_C4_MODE_IDX1         = 6,   // Quadrature Index 1
    PORT_C4_MODE_WT0_CCP0,           // Wide Timer0 Capture/Compare/PWM 0
    PORT_C4_MODE_UART1_RTS           // UART1 Request to Send
} Port_C4_Modes;

/*
 PC5 Modes
*/
typedef enum {
    PORT_C5_MODE_DIO,               // GPIO
    PORT_C5_MODE_UART4_TX,          // UART4 TX
    PORT_C5_MODE_UART1_TX,          // UART1 TX
    PORT_C5_MODE_M0PWM7      = 4,   // PWM Module 0, Generator 7
    PORT_C5_MODE_PHA1        = 6,   // Quadrature Phase A 1
    PORT_C5_MODE_WT0_CCP1,          // Wide Timer0 Capture/Compare/PWM1
    PORT_C5_MODE_UART1_CTS          // UART1 Clear to Send
} Port_C5_Modes;

/*
 PC6 Modes
*/
typedef enum {
    PORT_C6_MODE_DIO,               // GPIO
    PORT_C6_MODE_UART3_RX,          // UART3 RX
    PORT_C6_MODE_PHB1        = 6,   // Quadrature Phase B 1
    PORT_C6_MODE_WT1_CCP0,          // Wide Timer1 Capture/Compare/PWM0
    PORT_C6_MODE_USB0_EPEN          // USB0 External Power Enable
} Port_C6_Modes;

/*
 PC7 Modes
*/
typedef enum {
    PORT_C7_MODE_DIO,               // GPIO
    PORT_C7_MODE_UART3_TX,          // UART3 TX
    PORT_C7_MODE_WT1_CCP1    = 7,   // Wide Timer1 Capture/Compare/PWM1
    PORT_C7_MODE_USB0_PFLT          // USB0 Power Fault
} Port_C7_Modes;


/*********************************************************
 *                      Port D Modes                     *
 *********************************************************/

/*
 PD0 Modes
*/
typedef enum {
    PORT_D0_MODE_DIO,            // GPIO
    PORT_D0_MODE_SSI3_CLK,       // SSI3 Clock
    PORT_D0_MODE_SSI1_CLK,       // SSI1 Clock
    PORT_D0_MODE_I2C3_SCL,       // I2C3 Clock
    PORT_D0_MODE_M0PWM6,         // PWM Module 0, Generator 6
    PORT_D0_MODE_M1PWM0,         // PWM Module 1, Generator 0
    PORT_D0_MODE_WT2_CCP0  = 7   // Wide Timer2 Capture/Compare/PWM0
} Port_D0_Modes;

/*
 PD1 Modes
*/
typedef enum {
    PORT_D1_MODE_DIO,            // GPIO
    PORT_D1_MODE_SSI3FSS,        // SSI3 Frame Select
    PORT_D1_MODE_SSI1FSS,        // SSI1 Frame Select
    PORT_D1_MODE_I2C3SDA,        // I2C3 Data
    PORT_D1_MODE_M0PWM7,         // PWM Module 0, Generator 7
    PORT_D1_MODE_M1PWM1,         // PWM Module 1, Generator 1
    PORT_D1_MODE_WT2_CCP0  = 7   // Wide Timer2 Capture/Compare/PWM1
} Port_D1_Modes;

/*
 PD2 Modes
*/
typedef enum {
    PORT_D2_MODE_DIO,              // GPIO
    PORT_D2_MODE_SSI3_RX,          // SSI3 Receive
    PORT_D2_MODE_SSI1_RX,          // SSI1 Receive
    PORT_D2_MODE_M0FAULT0    = 4,  // PWM Module 0, Fault 0
    PORT_D2_MODE_WT3_CCP0    = 7,  // Wide Timer3 Capture/Compare/PWM0
    PORT_D2_MODE_USB0_EPEN   = 8   // USB0 External Power Enable
} Port_D2_Modes;

/*
 PD3 Modes
*/
typedef enum {
    PORT_D3_MODE_DIO,              // GPIO
    PORT_D3_MODE_SSI3_TX,          // SSI3 Transmit
    PORT_D3_MODE_SSI1_TX,          // SSI1 Transmit
    PORT_D3_MODE_IDX0       = 6,   // Quadrature Index 0
    PORT_D3_MODE_WT3_CCP1,         // Wide Timer3 Capture/Compare/PWM1
    PORT_D3_MODE_USB0PFLT          // USB0 Power Fault
} Port_D3_Modes;

/*
 PD4 Modes
*/
typedef enum {
    PORT_D4_MODE_DIO,             // GPIO
    PORT_D4_MODE_UART6_RX,       // UART6 RX
    PORT_D4_MODE_WT4_CCP0   = 7   // Wide Timer4 Capture/Compare/PWM0
} Port_D4_Modes;

/*
 PD5 Modes
*/
typedef enum {
    PORT_D5_MODE_DIO,             // GPIO
    PORT_D5_MODE_UART6_TX,        // UART6 TX
    PORT_D5_MODE_WT4_CCP1   = 7   // Wide Timer4 Capture/Compare/PWM1
} Port_D5_Modes;

/*
 PD6 Modes
*/
typedef enum {
    PORT_D6_MODE_DIO,               // GPIO
    PORT_D6_MODE_UART2_RX,          // UART2 RX
    PORT_D6_MODE_PHA0       = 6,    // Quadrature Phase A 0
    PORT_D6_MODE_WT5_CCP0           // Wide Timer1 Capture/Compare/PWM0
} Port_D6_Modes;

/*
 PD7 Modes
*/
typedef enum {
    PORT_D7_MODE_DIO,                // GPIO
    PORT_D7_MODE_UART2_TX,           // UART2 TX
    PORT_D7_MODE_PHB0       = 6,     // Quadrature Phase B 0
    PORT_D7_MODE_WT5_CCP1,           // Wide Timer1 Capture/Compare/PWM1
    PORT_D7_MODE_NMI                 // Non-Maskable Interrupt
} Port_D7_Modes;

/*********************************************************
 *                      Port E Modes                     *
 *********************************************************/

/*
 PE0 Modes
*/
typedef enum {
    PORT_E0_MODE_DIO,              // GPIO
    PORT_E0_MODE_UART7_RX          // UART7 RX
} Port_E0_Modes;

/*
 PE1 Modes
*/
typedef enum {
    PORT_E1_MODE_DIO,              // GPIO
    PORT_E1_MODE_UART7_TX          // UART7 TX
} Port_E1_Modes;

/*
 PE2 Modes
*/
typedef enum {
    PORT_E2_MODE_DIO,            // GPIO
} Port_E2_Modes;

/*
 PE3 Modes
*/
typedef enum {
    PORT_E3_MODE_DIO,            // GPIO
} Port_E3_Modes;

/*
 PE4 Modes
*/
typedef enum {
    PORT_E4_MODE_DIO,             // GPIO
    PORT_E4_MODE_UART5_RX,        // UART5 RX
    PORT_E4_MODE_I2C2_SCL  = 3,   // I2C2 SCL
    PORT_E4_MODE_M0PWM4,          // PWM Module 0, Generator 4
    PORT_E4_MODE_M1PWM2,          // PWM Module 1, Generator 2
    PORT_E4_MODE_CAN0_RX   = 8    // CAN0 RX
} Port_E4_Modes;

/*
 PE5 Modes
*/
typedef enum {
    PORT_E5_MODE_DIO,             // GPIO
    PORT_E5_MODE_UART5_TX,        // UART5 TX
    PORT_E5_MODE_I2C2_SDA  = 3,   // I2C2SDA
    PORT_E5_MODE_M0PWM5,          // PWM Module 0, Generator 5
    PORT_E5_MODE_M1PWM3,          // PWM Module 1, Generator 3
    PORT_E5_MODE_CAN0_TX   = 8    // CAN0 TX
} Port_E5_Modes;

/*********************************************************
 *                      Port F Modes                     *
 *********************************************************/

/*
 PF0 Modes
*/
typedef enum {
    PORT_F0_MODE_DIO,                 // GPIO
    PORT_F0_MODE_UART1_RTS,           // UART1 Request to Send
    PORT_F0_MODE_SSI1_RX,             // SSI1 Rx
    PORT_F0_MODE_CAN0_RX,             // CAN0 Rx
    PORT_F0_MODE_M1PWM4       = 5,    // PWM Module 1, Generator 4
    PORT_F0_MODE_PHA0,                // PhA0
    PORT_F0_MODE_T0_CCP0,             // Timer0 Capture/Compare/PWM0
    PORT_F0_MODE_NMI                  // NMI
} Port_F0_Modes;

/*
 PF1 Modes
*/
typedef enum {
    PORT_F1_MODE_DIO,                 // GPIO
    PORT_F1_MODE_UART1_CTS,           // UART1 Clear to Send
    PORT_F1_MODE_SSI1_TX,             // SSI1Tx
    PORT_F1_MODE_M1PWM5        = 5,   // PWM Module 1, Generator 5
    PORT_F1_MODE_PhB0,                // PhB0
    PORT_F1_MODE_T0_CCP1              // Timer0 Capture/Compare/PWM1
} Port_F1_Modes;

/*
 PF2 Modes
*/
typedef enum {
    PORT_F2_MODE_DIO,              // GPIO
    PORT_F2_MODE_SSI1_CLK,         // SSI1 Clk
    PORT_F2_MODE_M0FAULT0   = 4,   // PWM Module 0, Fault 0
    PORT_F2_MODE_M1PWM6,           // PWM Module 1, Generator 6
    PORT_F2_MODE_T1_CCP0    = 7    // Timer1 Capture/Compare/PWM0
} Port_F2_Modes;

/*
 PF3 Modes
*/
typedef enum {
    PORT_F3_MODE_DIO,              // GPIO
    PORT_F3_MODE_SSI1_FSS   = 2,   // SSI1 Fss
    PORT_F3_MODE_CAN0_TX    = 3,   // CAN0 Tx
    PORT_F3_MODE_M1PWM7     = 5,   // PWM Module 1, Generator 7
    PORT_F3_MODE_T1_CCP1    = 7    // Timer1 Capture/Compare/PWM1
} Port_F3_Modes;

/*
 PF4 Modes
*/
typedef enum {
    PORT_F4_MODE_DIO,              // GPIO
    PORT_F4_MODE_M1FAULT0   = 5,   // PWM Module 1, Fault 0
    PORT_F4_MODE_IDX0,             // IDX0
    PORT_F4_MODE_T2_CCP0,          // Timer2 Capture/Compare/PWM0
    PORT_F4_MODE_USB0_EPEN         // USB0 External Power Enable
} Port_F4_Modes;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0X00
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              1- Setup PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
*              2- Setup number of the pin in the PORT.
*              3- Setup initial mode for pin --> DIO or CAN or ADC or ....
*              4- the direction of pin --> INPUT or OUTPUT.
*              5- the internal resistor --> Disable, Pull up or Pull down.
*              6- Provide initial value for o/p pin --> Low or High.
*              7- EN/DIS Digital mode for this pin.
*              8- EN/DIS direction changeable during runtime.
*              9- EN/DIS mode changeable during runtime.
************************************************************************************/
void Port_Init
(
        const Port_ConfigType *ConfigPtr
);




/********************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0X01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin | Port Pin ID number, Direction | Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: The function Port_SetPinDirection shall set the port pin
 *              direction during runtime
 ********************************************************************************/
/* Pre-compile option to keep set pin direction API or not */
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection
(
        Port_PinType Pin,
        Port_PinDirectionType Direction
);
#endif



/********************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service Id[hex]: 0X02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Service Description: shall refresh the direction of all configured ports to the
 *                      configured direction
 ********************************************************************************/
void Port_RefreshPortDirection(void);




/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
/* Pre-compile option to keep get version info API or not */
#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo
(
        Std_VersionInfoType* versioninfo
);
#endif




/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin | Port pin ID, Mode | New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the port pin mode of the referenced pin during runtime.
 ************************************************************************************/
/* Pre-compile option to keep get port set pin mode API or not */
#if (PORT_SET_PIN_MODE_API  == STD_ON)
void Port_SetPinMode
(
        Port_PinType Pin,
        Port_PinModeType Mode
);
#endif


/************************************************************************************
 *                      Array of structure to use it in other files                 *
 ************************************************************************************/

extern const Port_ConfigType Port_PinsConfigurations[NUMBER_OF_PORT_PINS];

#endif /* PORT_H */
