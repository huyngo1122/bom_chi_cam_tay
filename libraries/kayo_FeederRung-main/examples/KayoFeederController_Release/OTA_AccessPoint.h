#pragma once
#include "WebServer_Config.h"
// #include "Arduino.h"
// #if defined(ESP8266)
//   #include <ESP8266WiFi.h>
//   #include <ESPAsyncTCP.h>
// #elif defined(ESP32)
//   #include <WiFi.h>
//   #include <AsyncTCP.h>
// #endif

// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

/*
    Go to http://192.168.4.1 in a web browser
    connected to this access point to see it.

    Go to http://192.168.4.1 in a web browser to upload Firmware
    https://randomnerdtutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/
*/
// #include <ESPAsyncWebServer.h> error Multiple define

extern void OTA_AccessPoint_Init();