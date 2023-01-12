#include "OTA_AccessPoint.h"


#include "Arduino.h"
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

/*
    Go to http://192.168.4.1 in a web browser
    connected to this access point to see it.

    Go to http://192.168.4.1 in a web browser to upload Firmware
    https://randomnerdtutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/
*/
const char* ssid = "KayoFeedernoFree";
const char* password = "likehshop";

AsyncWebServer server(80);

void OTA_AccessPoint_Init(){
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Congratulations! Your machine is hacked");
    });

    Config_Init();

    AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
    server.begin();
}