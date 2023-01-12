/*
    - http://192.168.4.1/config
    - http://192.168.4.1/update
*/
#include "Vietduino_Manager_Priority.h"
#include "Vietduino_Led.h"
#include "Vietduino_Button.h"
#include "PinVar.h"

#include "OTA_AccessPoint.h"


// Vietduino_Led feeder(PIN_FEEDER, SIG_ACTIVE_FEEDER);
Vietduino_Led feeder;
Vietduino_Button ds30c4;
Vietduino_Button btn;

unsigned long timeRunFeeder_ms = 2000;
unsigned long timeDetectFeeder_ms = 100;

void setup()
{
    ds30c4.begin(PIN_SENSOR, SIG_ACTIVE_SENSOR);
    btn.begin(PIN_BUTTON, SIG_ACTIVE_BUTTON);
    
    feeder.begin(PIN_FEEDER, SIG_ACTIVE_FEEDER);
    feeder.write(100,100,5);

    Serial.begin(115200);
    Serial.println(F("Start"));

    ds30c4.attachPress([](Vietduino_Task * me){
        feeder.stop();
        Serial.println(F("Stop FEEDER"));
    });

    ds30c4.attachRelease([](Vietduino_Task * me){
        feeder.write(timeRunFeeder_ms);
        Serial.println(F("Start FEEDER"));
        ds30c4.setPressTicks(timeDetectFeeder_ms);
    });

    btn.attachPress([](Vietduino_Task * me){
        feeder.stop();
        Serial.println(F("Stop FEEDER"));
    });

    btn.attachRelease([](Vietduino_Task * me){
        feeder.write(timeRunFeeder_ms);
        Serial.println(F("Start FEEDER"));
        ds30c4.setPressTicks(timeDetectFeeder_ms);
    });

    OTA_AccessPoint_Init();
    ds30c4.setPressTicks(timeDetectFeeder_ms);
    btn.setPressTicks(timeDetectFeeder_ms);
}

void loop()
{
    VIETDUINO_UPDATE;
    SetPinOverSerial();
}

void SetPinOverSerial(){
    if(Serial.available()){
        int tempPin = Serial.readStringUntil('\n').toInt();

        Serial.println("Rec: " + String(tempPin));

        pinMode(tempPin, OUTPUT);
        digitalWrite(tempPin, 1);
        delay(500);
        digitalWrite(tempPin, 0);
        delay(500);

        digitalWrite(tempPin, 1);
        delay(500);
        digitalWrite(tempPin, 0);
        delay(500);

        pinMode(tempPin, INPUT);
    }
}