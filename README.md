# AUTOSAR PORT Driver Module  

## 📖 Project Overview  
Develop an AUTOSAR-compliant PORT driver module for TM4C microcontrollers, enabling standardized configuration and control of I/O ports and pins. This driver adheres to AUTOSAR standards for safe, modular, and portable embedded software.

## 🎯 Objectives  
- Implement AUTOSAR PORT APIs as per the SWS (Software Specification) document.  
- Support pin initialization, direction control, and mode selection (digital/analog).  
- Enable development error reporting (DET) and compliance with **MISRA-C 2004** rules.  
- Provide a hardware abstraction layer (HAL) for portability across embedded platforms.

## 💡 Features  
- **Port Initialization:** `Port_Init(const Port_ConfigType* ConfigPtr)` initializes ports at startup.  
- **Set Pin Direction:** `Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)` for runtime changes (if allowed).  
- **Refresh Direction:** `Port_RefreshPortDirection()` reapplies static configurations.  
- **Set Pin Mode:** `Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)` switches between functions.  
- **Version Info:** `Port_GetVersionInfo(Std_VersionInfoType* versioninfo)` retrieves metadata.  
- **Error Reporting:** Integrated with `Det_ReportError` for null pointers, invalid parameters, or incorrect API usage.

## 📚 Drivers & APIs  
Complies with AUTOSAR 4.x PORT SWS:  
```c
// Initialization
void Port_Init(const Port_ConfigType* ConfigPtr);

// Pin Control
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

// Version Info & Error Reporting
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
```

## 📋 Requirements  
- Compliance with **AUTOSAR PORT SWS** and **MISRA-C 2004**.  
- Use of `Port_ConfigType` structures for pin configuration in `Port_Cfg.c`.  
- Source structure: `src/`, `include/`, `config/`, and `tests/`.  
- Include **Doxygen-style comments** for documentation.

## 🚀 Implementation Highlights  
- **Error Handling:** `Det_ReportError` integration for robust runtime checks.  
- **Protected Pins:** Special handling for TM4C-protected pins (e.g., PD7, PF0).  
- **Register Management:** Configured direction, resistor, and mode via precise register access.  
- **Safe Access:** `SET_BIT` and `CLEAR_BIT` macros for atomic operations.  
- **Version API:** `Port_GetVersionInfo` provides optional version metadata.
