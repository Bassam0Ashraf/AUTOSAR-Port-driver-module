 /*******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Bassam Ashraf
 *******************************************************************************/

/*******************************************************************************
 *                      File Includes And Version Checking                     *
 *******************************************************************************/

/* Include the Port.h file and check on the AUTOSAR and software version compatibility */
#include "Port.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Services_Layer/Development_Error_Tracer/Det.h"

/* checking the AUTOSAR version compatibility between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION  != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION  != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/* The "Port_Regs.h" is not AUTOSAR file so there is no version checking */
#include "Port_Regs.h"

/*******************************************************************************
 *                    Commonly used macros (Port Registers)                    *
 *******************************************************************************/

/* IMPORTANT NOTE:
 * If you change the name of pointer "PortConfig_Reg_Ptr" in "Port.c" file
 * you have to change it here in "Port.h" file in every macros in this section
 * "Commonly used macros (Port Registers)" ONLY to make sure the module run correctly. */

/* Macro to get the data register of the current port number */
#define PORT_DATA_REG                           ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_DATA_REG_OFFSET) )

/* Macro to get the data of the direction register of the current port number */
#define PORT_DIRECTION_REG                      ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_DIR_REG_OFFSET) )

/* Macro to get the data of the alternative function register of the current port number */
/* if bit CLEAR pin used as GPIO if SET using any mode configure by port control register  */
#define PORT_ALTERNATE_FUNCTION_SELECT_REG      ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_AFSEL_REG_OFFSET) )

/*  Macro to get the data of pull up register of the current port number */
#define PORT_PULL_UP_REG                        ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_PUR_REG_OFFSET) )

/*  Macro to get the data of pull down register of the current port number */
#define PORT_PULL_DOWN_REG                      ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_PDR_REG_OFFSET) )

/* Macro to get the data of the digital enable register of the current port number */
#define PORT_DIGITAL_ENABLE_REG                 ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_DEN_REG_OFFSET) )

/* Macro to get the data of the lock register of the current port number (PD7 or PF0) */
#define PORT_LOCK_REG                           ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_LOCK_REG_OFFSET) )

/* Macro to get the data of the commit register of the current port number (PD7 or PF0) */
/* when bit is set all change on DEN,PDR,PUR,AFSEL Registers */
#define PORT_COMMIT_REG                         ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_CR_REG_OFFSET) )

/* Macro to get the data of the analog select register of the current port number */
#define PORT_ANALOG_MODE_SELECT_REG             ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_AMSEL_REG_OFFSET) )

/*  Macro to get the data of the control register of the current port number */
/* select mode and configure pin for that mode each pin represent 4 bits in this register e.g PA0 --> [0:3] */
#define PORT_CONTROL_REG                        ( *(volatile uint32 *)((volatile uint8 *)PortConfig_Reg_Ptr + GPIO_PCTL_REG_OFFSET) )

/*******************************************************************************
 *                  Special Global variable for "Port.c" only                  *
 *******************************************************************************/

STATIC const Port_ConfigType * Port_Pin_Structure_Ptr = NULL_PTR;   /* Pointer to structure that will point to array of structure that hold our configuration.  */

STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;                    /* Variable indicate the status of port module. */

/*******************************************************************************
 *                          Function definitions                               *
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
void Port_Init(const Port_ConfigType * ConfigPtr )
{
    volatile uint32 * PortConfig_Reg_Ptr = NULL_PTR;    /* point to the required Port Registers base address */
    boolean Error = FALSE;
    uint8 PortPinConfigStructIndex = 0;                 /* Index for array of structure "Port_PinsConfigurations" */

    /*******************************************************************************
     *                           Checking on DET Error                             *
     *******************************************************************************/

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
        Error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif

    /* No DET error is detected */
    if ( FALSE == Error )
    {
        Port_Pin_Structure_Ptr = ConfigPtr;

        for( PortPinConfigStructIndex = 0; PortPinConfigStructIndex < NUMBER_OF_PORT_PINS; PortPinConfigStructIndex ++)
        {
            /*******************************************************************************
             *                              Select PORTn                                   *
             *******************************************************************************/

            /* Will leave these pins without configuration PC0 to PC3 (reserved for JTAG) */
            if( ( Port_Pin_Structure_Ptr -> port_num == PORT_C_ID) && (Port_Pin_Structure_Ptr -> pin_num <= PORT_C_PIN_3) )
            {
                Port_Pin_Structure_Ptr ++;  /* Make pointer to structure point to the next structure to skip (PC0 --> PC3) */
                continue;                   /* Skip current loop and go to the next iteration. */
            }

            /* Get Base Address of PORT (A or B or C or D or E or F) */
            switch (Port_Pin_Structure_Ptr -> port_num)
            {
                case  0: PortConfig_Reg_Ptr = (volatile uint32 *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
                         break;
                case  1: PortConfig_Reg_Ptr = (volatile uint32 *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
                         break;
                case  2: PortConfig_Reg_Ptr = (volatile uint32 *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
                         break;
                case  3: PortConfig_Reg_Ptr = (volatile uint32 *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
                         break;
                case  4: PortConfig_Reg_Ptr = (volatile uint32 *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
                         break;
                case  5: PortConfig_Reg_Ptr = (volatile uint32 *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
                         break;
            }

            /* unlock the commit register for these pins PD7 or PF0 */
            if( ((Port_Pin_Structure_Ptr -> port_num == PORT_D_ID) && (Port_Pin_Structure_Ptr -> pin_num == PORT_D_PIN_7)) || ((Port_Pin_Structure_Ptr -> port_num == PORT_F_ID) && (Port_Pin_Structure_Ptr -> pin_num == PORT_F_PIN_0)) ) /* PD7 or PF0 */
            {
                PORT_LOCK_REG = 0x4C4F434B;         /* Unlock the GPIOCR register */
                SET_BIT( PORT_COMMIT_REG , Port_Pin_Structure_Ptr -> pin_num );       /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }


            /*******************************************************************************
             *                                Select Mode                                  *
             *******************************************************************************/

            /* Setup the pin mode as GPIO */
            if ( PORT_PIN_MODE_DIO == Port_Pin_Structure_Ptr -> pin_mode )
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT( PORT_ANALOG_MODE_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT( PORT_ALTERNATE_FUNCTION_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* Clear the PMCx bits for this pin */
                PORT_CONTROL_REG &= ~(0xF << (Port_Pin_Structure_Ptr -> pin_num * 4) );

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT( PORT_DIGITAL_ENABLE_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup Alternative function for the pin */
            else if ( PORT_PIN_MODE_DIO != Port_Pin_Structure_Ptr -> pin_mode )
            {
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT( PORT_ALTERNATE_FUNCTION_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* First clear the PMCx bits for this pin to make sure the bit will be set correctly and then Set the PMCx bits for this pin */
                PORT_CONTROL_REG = ( PORT_CONTROL_REG & ~(0xF << (Port_Pin_Structure_Ptr -> pin_num * 4)) )\
                                 | ( Port_Pin_Structure_Ptr -> pin_mode << (Port_Pin_Structure_Ptr -> pin_num * 4) );

                /* Enable,Disable digital or analog pin */
                if ( TRUE == Port_Pin_Structure_Ptr -> port_pin_digital )
                {
                    /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                    CLEAR_BIT( PORT_ANALOG_MODE_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                    /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                    SET_BIT( PORT_DIGITAL_ENABLE_REG , Port_Pin_Structure_Ptr -> pin_num );
                }

                else
                {
                    /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                    CLEAR_BIT( PORT_DIGITAL_ENABLE_REG , Port_Pin_Structure_Ptr -> pin_num );

                    /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                    SET_BIT( PORT_ANALOG_MODE_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );
                }
            }

            else
            {
                /* Do Nothing */
            }


            /*******************************************************************************
             *                      Select Direction of pin (Input,Output)                 *
             *******************************************************************************/

            /* Setup direction of pin to make it INPUT pin */
            if ( PORT_PIN_IN == Port_Pin_Structure_Ptr -> direction )
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup direction of pin to make it OUTPUT pin */
            else if ( PORT_PIN_OUT == Port_Pin_Structure_Ptr -> direction )
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            else
            {
                /* Do Nothing */
            }

            /*******************************************************************************
             *                        Select pin level value (High,Low)                    *
             *******************************************************************************/

            /* Setup pin level to make it HIGH */
            if ( PORT_PIN_LEVEL_HIGH == Port_Pin_Structure_Ptr -> initial_level_value )
            {
                /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                SET_BIT( PORT_DATA_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup pin level to make it LOW */
            else if ( PORT_PIN_LEVEL_LOW == Port_Pin_Structure_Ptr -> initial_level_value )
            {
                /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                CLEAR_BIT( PORT_DATA_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            else
            {
                /* Do Nothing */
            }


            /*******************************************************************************
             *                         Select Internal Resistor mode                       *
             *******************************************************************************/

            /* Setup internal resistor to be PULL UP */
            if ( INTERNAL_RESISTOR_PULL_UP == Port_Pin_Structure_Ptr -> resistor )
            {
                /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                SET_BIT( PORT_PULL_UP_REG , Port_Pin_Structure_Ptr -> pin_num);
            }

            /* Setup internal resistor to be PULL DOWN */
            else if ( INTERNAL_RESISTOR_PULL_DOWN == Port_Pin_Structure_Ptr -> resistor )
            {

                /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                SET_BIT( PORT_PULL_DOWN_REG , Port_Pin_Structure_Ptr-> pin_num);
            }

            /* Turn OFF internal resistor */
            else
            {
                /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT( PORT_PULL_UP_REG , Port_Pin_Structure_Ptr -> pin_num);


                /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                CLEAR_BIT( PORT_PULL_DOWN_REG , Port_Pin_Structure_Ptr -> pin_num);
            }

            /* Increment the Port_Pin_Structure_Ptr pointer to points on the following structure */
            Port_Pin_Structure_Ptr ++;
        }

        Port_Status = PORT_INITIALIZED;
    }

    else
    {
        /* Do Nothing */
    }

}




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

void Port_SetPinDirection(Port_PinType Pin , Port_PinDirectionType Direction)
{
    volatile uint32 * PortConfig_Reg_Ptr = NULL_PTR;            /* point to the required Port Registers base address */
    boolean Error = FALSE;

    /*******************************************************************************
     *                           Checking on DET Error                             *
     *******************************************************************************/

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the port pin id requested is invalid */
    if ( (NUMBER_OF_PORT_PINS <= Pin) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_PARAM_PIN);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

    Port_Pin_Structure_Ptr = &Port_PinsConfigurations [Pin];    /* Point to the index of array of structure for the provided pin */

    /* Check if the port pin not configured as changeable */
    if ( FALSE == Port_Pin_Structure_Ptr -> port_pin_direction_changeable )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

    /* Check if module not initialized */
    if ( PORT_NOT_INITIALIZED == Port_Status )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_UNINIT);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

#endif

    /* No DET error is detected */
    if ( FALSE == Error )
    {
        Port_Pin_Structure_Ptr = &Port_PinsConfigurations [Pin];    /* Point to the index of array of structure for the provided pin */
        /*******************************************************************************
         *                              Select PORTn                                   *
         *******************************************************************************/

        /* Get Base Address of PORT (A or B or C or D or E or F) */
        switch (Port_Pin_Structure_Ptr -> port_num)
        {
            case  0: PortConfig_Reg_Ptr = (volatile uint32 *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  1: PortConfig_Reg_Ptr = (volatile uint32 *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  2: PortConfig_Reg_Ptr = (volatile uint32 *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  3: PortConfig_Reg_Ptr = (volatile uint32 *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  4: PortConfig_Reg_Ptr = (volatile uint32 *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  5: PortConfig_Reg_Ptr = (volatile uint32 *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }

        /* Will leave these pins without configuration PC0 to PC3 (reserved for JTAG) */
        if( (Port_Pin_Structure_Ptr -> port_num == PORT_C_ID) && ( Port_Pin_Structure_Ptr -> pin_num <= PORT_C_PIN_3) )
        {
            return;
        }

        /*******************************************************************************
         *                      Select Direction of pin (Input,Output)                 *
         *******************************************************************************/

        /* Check if the port pin not configured as changeable */
        if ( TRUE == Port_Pin_Structure_Ptr -> port_pin_direction_changeable )
        {
            /* Setup direction of pin to make it INPUT pin */
            if ( PORT_PIN_IN == Direction )
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup direction of pin to make it OUTPUT pin */
            else if ( PORT_PIN_OUT == Direction )
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            else
            {
                /* Do Nothing */
            }
        }

        else
        {
            /* Do Nothing */
        }
    }

    else
    {
        /* Do Nothing */
    }
}
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
void Port_RefreshPortDirection(void)
{
    volatile uint32 * PortConfig_Reg_Ptr = NULL_PTR;            /* point to the required Port Registers base address */
    boolean Error = FALSE;
    uint8 PortPinConfigStructIndex = 0;                 /* Index for array of structure "Port_PinsConfigurations" */

    /*******************************************************************************
     *                           Checking on DET Error                             *
     *******************************************************************************/

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if module not initialized */
    if ( PORT_NOT_INITIALIZED == Port_Status )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

#endif

    /* No DET error is detected */
    if ( FALSE == Error )
    {
        Port_Pin_Structure_Ptr = &Port_PinsConfigurations[PORT_A_PIN_0_INDEX];  /* Point to the first index of array of structure */

        for( PortPinConfigStructIndex = 0; PortPinConfigStructIndex < NUMBER_OF_PORT_PINS; PortPinConfigStructIndex ++)
        {
            /*******************************************************************************
             *                              Select PORTn                                   *
             *******************************************************************************/

            /* Will leave these pins without configuration PC0 to PC3 (reserved for JTAG) */
            if( (Port_Pin_Structure_Ptr -> port_num == PORT_C_ID) && ( Port_Pin_Structure_Ptr -> pin_num <= PORT_C_PIN_3) )
            {
                Port_Pin_Structure_Ptr ++;  /* Make pointer to structure point to the next structure to skip (PC0 --> PC3) */
                continue;                   /* Skip current loop and go to the next iteration. */
            }

            /* Get Base Address of PORT (A or B or C or D or E or F) */
            switch (Port_Pin_Structure_Ptr -> port_num)
            {
                case  0: PortConfig_Reg_Ptr = (volatile uint32 *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
                         break;
                case  1: PortConfig_Reg_Ptr = (volatile uint32 *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
                         break;
                case  2: PortConfig_Reg_Ptr = (volatile uint32 *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
                         break;
                case  3: PortConfig_Reg_Ptr = (volatile uint32 *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
                         break;
                case  4: PortConfig_Reg_Ptr = (volatile uint32 *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
                         break;
                case  5: PortConfig_Reg_Ptr = (volatile uint32 *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
                         break;
            }

            /* Setup direction of pin to make it INPUT pin */
            if ( PORT_PIN_IN == Port_Pin_Structure_Ptr -> direction )
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup direction of pin to make it OUTPUT pin */
            else if ( PORT_PIN_OUT == Port_Pin_Structure_Ptr -> direction )
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT( PORT_DIRECTION_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            else
            {
                /* Do Nothing */
            }

        }

    }

    else
    {
        /* Do Nothing */
    }
}




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

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    /*******************************************************************************
     *                           Checking on DET Error                             *
     *******************************************************************************/

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }

    else
    {
        /* Do Nothing */
    }

    /* Check if module not initialized */
    if ( PORT_NOT_INITIALIZED == Port_Status )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
                        PORT_E_UNINIT);
    }

    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
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

void Port_SetPinMode(Port_PinType Pin , Port_PinModeType Mode)
{
    volatile uint32 * PortConfig_Reg_Ptr = NULL_PTR;            /* point to the required Port Registers base address */
    boolean Error = FALSE;

    /*******************************************************************************
     *                           Checking on DET Error                             *
     *******************************************************************************/

#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the port pin id requested is invalid */
    if ( (NUMBER_OF_PORT_PINS <= Pin) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_PIN);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }


    Port_Pin_Structure_Ptr = &Port_PinsConfigurations [Pin];    /* Point to the index of array of structure for the provided pin */

    /* Check if the port pin mode not configured as changeable */
    if ( FALSE == Port_Pin_Structure_Ptr -> port_pin_mode_changeable )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_MODE_UNCHANGEABLE);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

    /* Check if module not initialized */
    if ( PORT_NOT_INITIALIZED == Port_Status )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_UNINIT);
        Error = TRUE;
    }

    else
    {
        /* Do Nothing */
    }

#endif

    /* No DET error is detected */
    if ( FALSE == Error )
    {
        Port_Pin_Structure_Ptr = &Port_PinsConfigurations [Pin];    /* Point to the index of array of structure for the provided pin */

        /*******************************************************************************
         *                              Select PORTn                                   *
         *******************************************************************************/

        /* Get Base Address of PORT (A or B or C or D or E or F) */
        switch (Port_Pin_Structure_Ptr -> port_num)
        {
            case  0: PortConfig_Reg_Ptr = (volatile uint32 *)PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  1: PortConfig_Reg_Ptr = (volatile uint32 *)PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  2: PortConfig_Reg_Ptr = (volatile uint32 *)PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  3: PortConfig_Reg_Ptr = (volatile uint32 *)PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  4: PortConfig_Reg_Ptr = (volatile uint32 *)PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  5: PortConfig_Reg_Ptr = (volatile uint32 *)PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }

        /* Will leave these pins without configuration PC0 to PC3 (reserved for JTAG) */
        if( (Port_Pin_Structure_Ptr -> port_num == PORT_C_ID) && ( Port_Pin_Structure_Ptr -> pin_num <= PORT_C_PIN_3) )
        {
            return;
        }

        /*******************************************************************************
         *                                Select Mode                                  *
         *******************************************************************************/

        /* Check if the port pin mode not configured as changeable */
        if ( TRUE == Port_Pin_Structure_Ptr -> port_pin_mode_changeable )
        {
            /* Setup the pin mode as GPIO */
            if ( PORT_PIN_MODE_DIO == Mode )
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT( PORT_ANALOG_MODE_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT( PORT_ALTERNATE_FUNCTION_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* Clear the PMCx bits for this pin */
                PORT_CONTROL_REG &= ~(0xF << (Port_Pin_Structure_Ptr -> pin_num * 4) );

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT( PORT_DIGITAL_ENABLE_REG , Port_Pin_Structure_Ptr -> pin_num );
            }

            /* Setup Alternative function for the pin */
            else
            {
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT( PORT_ALTERNATE_FUNCTION_SELECT_REG , Port_Pin_Structure_Ptr -> pin_num );

                /* First clear the PMCx bits for this pin to make sure the bit will be set correctly and then Set the PMCx bits for this pin */
                PORT_CONTROL_REG = ( PORT_CONTROL_REG & ~(0xF << (Port_Pin_Structure_Ptr -> pin_num * 4)) )\
                                 | ( Mode << (Port_Pin_Structure_Ptr -> pin_num * 4) );
            }
        }

        else
        {
            /* Do Nothing */
        }

    }

    else
    {
        /* Do Nothing */
    }
}
#endif
