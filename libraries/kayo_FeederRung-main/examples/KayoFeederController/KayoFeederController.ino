/*
    - http://192.168.4.1/config
    - http://192.168.4.1/update
*/
#include "Vietduino_Manager_Priority.h"
#include "Vietduino_Led.h"
#include "Vietduino_Button.h"
#include "PinVar.h"

#include "OTA_AccessPoint.h"


Vietduino_Led feeder(PIN_FEEDER, SIG_ACTIVE_FEEDER);
Vietduino_Button ds30c4;

unsigned long timeRunFeeder_ms = 2000;

void setup()
{
    ds30c4.begin(PIN_SENSOR, SIG_ACTIVE_SENSOR);
    ds30c4.setPressTicks(100);

    Serial.begin(115200);
    Serial.println(F("Start"));
    ds30c4.attachPress([](Vietduino_Task * me){
        feeder.stop();
        Serial.println(F("Stop FEEDER"));
    });

    ds30c4.attachRelease([](Vietduino_Task * me){
        feeder.write(timeRunFeeder_ms);
        Serial.println(F("Start FEEDER"));
    });

    OTA_AccessPoint_Init();
}

void loop()
{
    VIETDUINO_UPDATE;
}