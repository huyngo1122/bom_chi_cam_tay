// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/

#include "WebServer_Config.h"

#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;
extern unsigned long timeRunFeeder_ms;

const char *PARAM_STRING = "inputString";
const char *PARAM_INT = "inputInt";
const char *PARAM_FLOAT = "inputFloat";

#define PARAM_TIME_RUN_FEEDER  "inputTimeRunFeeder"

// HTML web page to handle 3 input fields (inputString, inputInt, inputFloat)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Kayo Feeder Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function submitMessage() {
      alert("Saved value to ESP SPIFFS");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script></head><body>
  <form action="/get" target="hidden-form">
    inputString (current value %inputString%): <input type="text" name="inputString">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputInt (current value %inputInt%): <input type="number " name="inputInt">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputFloat (current value %inputFloat%): <input type="number " name="inputFloat">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Time run Feeder (current value %inputTimeRunFeeder% ms): <input type="number " name="inputTimeRunFeeder">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char *path)
{
    Serial.printf("Reading file: %s\r\n", path);
    File file = fs.open(path, "r");
    if (!file || file.isDirectory())
    {
        Serial.println("- empty file or failed to open file");
        return String();
    }
    Serial.println("- read from file:");
    String fileContent;
    while (file.available())
    {
        fileContent += String((char)file.read());
    }
    file.close();
    Serial.println(fileContent);
    return fileContent;
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\r\n", path);
    File file = fs.open(path, "w");
    if (!file)
    {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("- file written");
    }
    else
    {
        Serial.println("- write failed");
    }
    file.close();
}

// Replaces placeholder with stored values
String processor(const String &var)
{
    // Serial.println(var);
    if (var == "inputString")
    {
        return readFile(SPIFFS, "/inputString.txt");
    }
    else if (var == "inputInt")
    {
        return readFile(SPIFFS, "/inputInt.txt");
    }
    else if (var == "inputFloat")
    {
        return readFile(SPIFFS, "/inputFloat.txt");
    }
    else if (var == PARAM_TIME_RUN_FEEDER)   // y22m07d04 kxn
    {
        return readFile(SPIFFS, MY_FILE_TXT(PARAM_TIME_RUN_FEEDER));
    }
    return String();
}

void SPIFFS_Init()
{
#ifdef ESP32
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
#else
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
#endif
}

void Read_Config()
{
    String yourInputString = readFile(SPIFFS, "/inputString.txt");
    Serial.print("*** Your inputString: ");
    Serial.println(yourInputString);

    int yourInputInt = readFile(SPIFFS, "/inputInt.txt").toInt();
    Serial.print("*** Your inputInt: ");
    Serial.println(yourInputInt);

    float yourInputFloat = readFile(SPIFFS, "/inputFloat.txt").toFloat();
    Serial.print("*** Your inputFloat: ");
    Serial.println(yourInputFloat);

    timeRunFeeder_ms = readFile(SPIFFS, MY_FILE_TXT(PARAM_TIME_RUN_FEEDER)).toInt();
    Serial.print("*** Your inputTimeRunFeeder: ");
    Serial.println(timeRunFeeder_ms);
}

void Config_Init()
{   
    SPIFFS_Init();
    // Send web page with input fields to client
    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html, processor); });

    // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    String inputMessage;
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    else if (request->hasParam(PARAM_INT)) {
      inputMessage = request->getParam(PARAM_INT)->value();
      writeFile(SPIFFS, "/inputInt.txt", inputMessage.c_str());
    }
    // GET inputFloat value on <ESP_IP>/get?inputFloat=<inputMessage>
    else if (request->hasParam(PARAM_FLOAT)) {
      inputMessage = request->getParam(PARAM_FLOAT)->value();
      writeFile(SPIFFS, "/inputFloat.txt", inputMessage.c_str());
    }
    // y22m07d04 kxn
    else if (request->hasParam(PARAM_TIME_RUN_FEEDER)) {
      inputMessage = request->getParam(PARAM_TIME_RUN_FEEDER)->value();
      writeFile(SPIFFS, MY_FILE_TXT(PARAM_TIME_RUN_FEEDER), inputMessage.c_str());
      timeRunFeeder_ms = inputMessage.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage); });

    Read_Config();
}