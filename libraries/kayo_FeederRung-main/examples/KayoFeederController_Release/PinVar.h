#pragma once

/*
    Note: 
        - Esp8266 IO0 output ERROR with Trans C1815
*/
#define USE_SONOFF_S22


#if defined(USE_SONOFF_S22)
    #define SIG_ACTIVE_FEEDER   HIGH
    #define SIG_ACTIVE_SENSOR   LOW
    #define SIG_ACTIVE_BUTTON   LOW
    #define PIN_FEEDER  12
    #define PIN_SENSOR  4
    #define PIN_BUTTON  0
#else
    #define SIG_ACTIVE_FEEDER   HIGH
    #define SIG_ACTIVE_SENSOR   LOW
    #define SIG_ACTIVE_BUTTON   LOW

    #define PIN_FEEDER  D11
    #define PIN_SENSOR  D10
    #define PIN_BUTTON  D9
#endif