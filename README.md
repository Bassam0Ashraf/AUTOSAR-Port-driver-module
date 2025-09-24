# AUTOSAR-Compliant Embedded Systems Architecture

**Advanced Embedded Systems Project | EDGES Training Program**

## Table of Contents
- [Project Overview](#project-overview)
- [Complete System Architecture](#complete-system-architecture)
- [Comprehensive Project Components](#comprehensive-project-components)
- [Advanced Implementation Features](#advanced-implementation-features)
- [Demonstration Application](#demonstration-application)
- [Technical Specifications](#technical-specifications)
- [Development Environment](#development-environment)
- [Project File Structure](#project-file-structure)
- [Quality Metrics and Compliance](#quality-metrics-and-compliance)
- [License](#license)

## Project Overview

This project implements a comprehensive AUTOSAR-compliant multi-layer embedded software architecture for TM4C123GH6PM microcontrollers, demonstrating professional-grade automotive software development practices. The implementation features a complete five-layer architecture including Application Layer, Services Layer, ECUAL (ECU Abstraction Layer), MCAL (Microcontroller Abstraction Layer), and Hardware Layer, all strictly adhering to AUTOSAR 4.0.3 specifications.

## Complete System Architecture

```
┌─────────────────────────────────────────┐
│         Application Layer               │
│         ├── App.c - Main Application    │
│         ├── main.c - Entry Point        │
├─────────────────────────────────────────┤
│         Services Layer                  │
│         ├── Os.c - Real-Time Scheduler  │
│         └── Det.c - Development Error   │
│             Tracer                      │
├─────────────────────────────────────────┤
│         ECUAL (ECU Abstraction Layer)   │
│         ├── Button Module               │
│         └── LED Module                  │
├─────────────────────────────────────────┤
│         MCAL (Microcontroller           │
│         Abstraction Layer)              │
│         ├── PORT Driver (AUTOSAR SWS)   │
│         ├── DIO Driver                  │
│         ├── GPT Driver (SysTick)        │
│         └── MCU Driver                  │
├─────────────────────────────────────────┤
│         Hardware (TM4C123GH6PM)         │
└─────────────────────────────────────────┘
```

## Comprehensive Project Components

### Application Layer

#### Main Application (App.c)
- **System Integration Controller**: Coordinates all system components through task-based architecture
- **Initialization Management**: Comprehensive system startup sequence with proper layer initialization
- **Real-Time Task Implementation**: Button debouncing, LED control, and application logic tasks
- **State Machine Logic**: Advanced button press detection with edge-triggered LED toggle functionality

**Key Functions:**
```c
void Init_Task(void);          // System-wide initialization
void Button_Task(void);        // 20ms button debouncing task
void Led_Task(void);          // 40ms LED refresh task  
void App_Task(void);          // 60ms application logic task
```

#### System Entry Point (main.c)
- **Bootstrap Functionality**: Single-point system startup
- **OS Integration**: Direct interface to real-time operating system
- **Clean Architecture**: Separation of system initialization and application execution

### Services Layer

#### Real-Time Operating System (Os.c)
- **Deterministic Scheduler**: Cooperative multi-tasking with precise timing control
- **Interrupt-Driven Architecture**: SysTick-based 20ms time base for real-time operations
- **Task Management**: Priority-based task scheduling with comprehensive time slot allocation
- **System Control**: ARM Cortex-M exception handling and fault management

**Scheduling Matrix:**
- **20ms**: Button_Task() - Continuous button state sampling
- **40ms**: Button_Task() + Led_Task() - LED state management
- **60ms**: Button_Task() + App_Task() - Application logic processing
- **80ms**: Button_Task() + Led_Task() - LED refresh cycle
- **100ms**: Button_Task() - Button state validation
- **120ms**: Button_Task() + App_Task() + Led_Task() - Complete system cycle

#### Development Error Tracer (Det.c)
- **AUTOSAR 4.0.3 Compliant**: Full compliance with AUTOSAR DET specifications
- **Error Reporting Infrastructure**: Centralized error detection and reporting mechanism
- **Development Support**: Runtime parameter validation and debugging assistance
- **Module Integration**: Seamless integration with all MCAL and ECUAL components

### ECUAL (ECU Abstraction Layer)

#### Advanced Button Module
- **Sophisticated Debouncing Algorithm**: 60ms validation window with 3-sample confirmation
- **Hardware Abstraction**: Platform-independent button interface using DIO services
- **State Management**: Reliable pressed/released detection with static state preservation
- **OS Integration**: 20ms periodic refresh synchronized with system scheduler

#### Intelligent LED Module  
- **Comprehensive Control Interface**: On/Off/Toggle/Refresh operations with state persistence
- **Hardware Independence**: DIO channel abstraction for cross-platform compatibility
- **State Synchronization**: Advanced refresh functionality maintaining LED state consistency
- **Configuration Flexibility**: Support for both positive and negative logic configurations

### MCAL (Microcontroller Abstraction Layer)

#### AUTOSAR PORT Driver (Full SWS Compliance)
- **Complete AUTOSAR 4.0.3 Implementation**: Full compliance with PORT SWS specifications
- **43-Pin Configuration Management**: Comprehensive configuration for all TM4C123GH6PM pins
- **Runtime Configuration Capabilities**: Dynamic pin direction and mode switching with safety validation
- **Protected Pin Handling**: Specialized unlock sequences for PD7 and PF0 locked pins
- **Multi-Mode Support**: GPIO, UART, SPI, I2C, PWM, CAN, Timer, and ADC functionalities
- **Version Management**: Comprehensive AUTOSAR version checking across all interfaces

**Advanced Configuration Features:**
- Post-build configuration structure with 43 individual pin definitions
- UART0 communication setup (PA0-RX, PA1-TX) for system debugging
- LED control configuration (PF1) with proper output drive settings
- Switch input configuration (PF4) with internal pull-up resistor activation
- JTAG protection for PC0-PC3 pins with proper exclusion handling

#### Professional DIO Driver
- **Channel Abstraction**: Hardware-independent digital I/O operations
- **Configuration Management**: Post-build configuration for LED and button channels
- **Error Detection Integration**: Comprehensive DET reporting for parameter validation
- **Atomic Operations**: Safe bit manipulation with proper register access protection
- **Version Control**: Full AUTOSAR version compatibility checking

#### High-Precision GPT Driver (SysTick)
- **Millisecond Accuracy**: Precise timing control with 16MHz system clock calculations
- **Dual Operation Modes**: Both interrupt-driven and polling-based timing mechanisms
- **Callback Architecture**: Flexible interrupt service routine with user-defined callback functions
- **Real-Time OS Support**: 20ms time base generation for deterministic task scheduling
- **Priority Management**: Configurable interrupt priority (Level 3) with proper NVIC integration

#### System MCU Driver
- **Clock Tree Management**: Comprehensive system clock initialization and control
- **Peripheral Clock Gating**: Efficient power management through selective clock enabling
- **Hardware Abstraction**: Register-level access abstraction for system control functions

### Hardware Platform

#### TM4C123GH6PM Microcontroller Specifications
- **ARM Cortex-M4F Core**: 32-bit RISC processor with FPU support
- **System Clock**: 16MHz operation with PLL support for higher frequencies
- **GPIO Ports**: 6 ports (A-F) with 43 configurable pins total
- **Memory**: 256KB Flash, 32KB SRAM for application and configuration storage
- **Peripherals**: UART, SPI, I2C, PWM, ADC, Timers, and CAN interfaces

## Advanced Implementation Features

### AUTOSAR Compliance Excellence
- **Version Management**: Comprehensive version checking across all module interfaces
- **Configuration Classes**: Support for Pre-compile, Link-time, and Post-build configurations
- **Error Handling Standards**: Standardized DET error reporting with proper error codes
- **Interface Standardization**: Consistent API design following AUTOSAR naming conventions

### Real-Time System Design
- **Deterministic Behavior**: Predictable timing and response characteristics across all operations
- **Interrupt Architecture**: Priority-based interrupt handling with proper nesting support
- **Task Synchronization**: Cooperative multitasking with precise timing control
- **Resource Management**: Efficient CPU and memory utilization optimization

### Safety and Quality Assurance
- **Parameter Validation**: Comprehensive input checking with detailed error reporting
- **State Machine Protection**: Proper initialization sequence enforcement
- **Atomic Operations**: Safe register access with critical section protection
- **Memory Safety**: Static allocation with bounds checking and overflow protection

## Demonstration Application

### Button-Controlled LED System
The complete system demonstrates a professional embedded application with:

- **Advanced Button Debouncing**: 60ms validation with 3-sample confirmation algorithm
- **Edge-Triggered Response**: LED toggle only on button press (not release) for precise user interaction
- **State Persistence**: Maintaining LED state across system cycles with refresh capability
- **Real-Time Responsiveness**: 20ms system response time for immediate user feedback

### System Operation Flow
1. **Initialization Phase**: Complete system startup with proper layer initialization sequence
2. **Continuous Operation**: Real-time scheduler managing multiple concurrent tasks
3. **Button Sampling**: 20ms periodic button state acquisition and debouncing
4. **LED Management**: 40ms LED state refresh and control operations
5. **Application Logic**: 60ms main application processing with state machine management

## Technical Specifications

### Performance Metrics
- **Button Debounce Time**: 60ms guaranteed with 20ms sampling rate
- **System Response**: <20ms from button press to LED toggle initiation
- **CPU Utilization**: Optimized task scheduling with minimal overhead
- **Memory Footprint**: Efficient configuration structures with minimal RAM usage

### Configuration Management
```c
// Example PORT configuration with comprehensive pin setup
const Port_ConfigType Port_PinsConfigurations[43] = {
    // UART Communication
    { PORT_A_ID, PORT_A_PIN_0, PORT_A0_MODE_UART0_RX, PORT_PIN_IN, 
      INTERNAL_RESISTOR_OFF, PORT_PIN_LEVEL_LOW, TRUE, FALSE, TRUE },
    { PORT_A_ID, PORT_A_PIN_1, PORT_A1_MODE_UART0_TX, PORT_PIN_OUT, 
      INTERNAL_RESISTOR_OFF, PORT_PIN_LEVEL_LOW, TRUE, FALSE, TRUE },
    
    // LED Control
    { PORT_F_ID, PORT_F_PIN_1, PORT_PIN_MODE_DIO, PORT_PIN_OUT, 
      INTERNAL_RESISTOR_OFF, PORT_PIN_LEVEL_LOW, TRUE, TRUE, TRUE },
    
    // Button Input
    { PORT_F_ID, PORT_F_PIN_4, PORT_PIN_MODE_DIO, PORT_PIN_IN, 
      INTERNAL_RESISTOR_PULL_UP, PORT_PIN_LEVEL_LOW, TRUE, TRUE, TRUE }
};
```

### Error Handling Integration
- **DET Error Codes**: Comprehensive error classification with specific error identifiers
- **Parameter Validation**: Runtime checking of all API parameters with detailed error reporting
- **State Validation**: Proper initialization checking before API usage
- **Null Pointer Protection**: Comprehensive validation of all pointer parameters

## Development Environment

**IDE**: Code Composer Studio (CCS)  
**Target Hardware**: TM4C123GH6PM Microcontroller (ARM Cortex-M4F)  
**System Clock**: 16MHz with precision timing calculations  
**Programming Language**: C (ANSI C99 Standard)  
**Standards Compliance**: AUTOSAR 4.0.3, MISRA-C 2004  
**Testing Framework**: CUnit Testing Framework  
**Documentation**: Doxygen-compatible inline documentation

## Project File Structure

```
AUTOSAR_Project/
├── Application/                 # Application Layer
│   ├── App.c                   # Main application logic
│   ├── App.h                   # Application interface
│   └── main.c                  # System entry point
├── Services_Layer/              # Services Layer
│   ├── Scheduler/              # Real-Time Operating System
│   │   ├── Os.c               # OS implementation
│   │   └── Os.h               # OS interface
│   └── Development_Error_Tracer/ # Error Detection Service
│       ├── Det.c              # DET implementation
│       └── Det.h              # DET interface
├── ECUAL/                       # ECU Abstraction Layer
│   ├── Button/                 # Button module
│   │   ├── Button.c           # Button implementation
│   │   ├── Button.h           # Button interface
│   │   └── Button_Cfg.h       # Button configuration
│   └── Led/                    # LED module
│       ├── Led.c              # LED implementation
│       ├── Led.h              # LED interface
│       └── Led_Cfg.h          # LED configuration
├── MCAL/                        # Microcontroller Abstraction Layer
│   ├── Port/                   # AUTOSAR PORT Driver
│   │   ├── Port.c             # PORT implementation
│   │   ├── Port.h             # PORT interface
│   │   ├── Port_Cfg.h         # PORT configuration
│   │   ├── Port_PBcfg.c       # Post-build configuration
│   │   ├── Port_PBcfg.h       # Post-build header
│   │   └── Port_Regs.h        # Hardware registers
│   ├── Dio/                    # Digital I/O Driver
│   │   ├── Dio.c              # DIO implementation
│   │   ├── Dio.h              # DIO interface
│   │   ├── Dio_Cfg.h          # DIO configuration
│   │   ├── Dio_PBcfg.c        # Post-build configuration
│   │   └── Dio_Regs.h         # Hardware registers
│   ├── Gpt/                    # General Purpose Timer (SysTick)
│   │   ├── Gpt.c              # GPT implementation
│   │   ├── Gpt.h              # GPT interface
│   │   └── Gpt_Regs.h         # Timer registers
│   └── Mcu/                    # Microcontroller Unit Driver
│       ├── Mcu.c              # MCU implementation
│       ├── Mcu.h              # MCU interface
│       └── Mcu_Regs.h         # System control registers
├── Common/                      # Common definitions
│   ├── Std_Types.h            # Standard AUTOSAR types
│   └── Common_Macros.h        # Utility macros
└── Documentation/               # Project documentation
    └── AUTOSAR_SWS_PortDriver.pdf # PORT Driver specification
```

## Quality Metrics and Compliance

### AUTOSAR Compliance Verification
- **Module ID Management**: Proper vendor and module identification across all components
- **Version Compatibility**: Comprehensive version checking between all interface modules
- **Configuration Management**: Proper separation of pre-compile, link-time, and post-build parameters
- **Error Classification**: Standardized development and production error handling

### Code Quality Standards
- **MISRA-C 2004 Compliance**: Automotive industry coding standards adherence
- **Doxygen Documentation**: Comprehensive inline documentation for all public interfaces
- **Modular Architecture**: Clear separation of concerns with well-defined module boundaries
- **Resource Optimization**: Efficient memory usage and processing overhead minimization

### Testing and Validation
- **Hardware-in-the-Loop Testing**: Complete system validation on target platform
- **Integration Testing**: Multi-layer interaction and interface validation
- **Real-Time Performance**: Timing accuracy and deterministic behavior verification
- **Error Condition Testing**: Comprehensive validation of error detection and handling paths

## License

This is an educational Advanced Embedded systems project for the EDGES Training Program.

---

**Developed by**: Bassam Ashraf  
**Course**: Advanced Embedded Diploma  
**Program**: EDGES Training Program  
**IDE**: Code Composer Studio  
**Language**: C        
**Target Hardware**: TM4C series (TM4C123GH6PM) 

---

*This comprehensive AUTOSAR-compliant project demonstrates professional embedded software development practices, emphasizing automotive industry standards, real-time system design, multi-layer architecture, and safety-critical software engineering principles. The implementation serves as a complete reference for AUTOSAR-based embedded system development with full compliance to industry specifications.*
