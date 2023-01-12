// y22m05d13  kxn test
#include "Vietduino_Led.h"
#include "Vietduino_NewFunction.h"

#define LED13_PIN   13
#define LED13_ACTIVE  HIGH

#define LED1_PIN   1
#define LED1_ACTIVE  LOW

Vietduino_Led L13(LED13_PIN, LED13_ACTIVE);
Vietduino_Led L1(LED1_PIN, LED1_ACTIVE);


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // DO NOT put your code here:
  VIETDUINO_UPDATE;

//  L13.write(2000);
//  delay(3000);
//  L13.write(300, 300, 4);
//  delay(5000);
//  L13.write(100, 100, 5, 1000);
//  delay(7000);
  runLedFunction();
}

void runLedFunction(){
  L1.write(2000);
  delay(3000);
  L1.write(300, 300, 4);
  delay(5000);
  L1.write(100, 100, 5, 1000);
  delay(7000);
}

void runLedFunction_13(){
  L13.write(2000);
  delay(3000);
  L13.write(300, 300, 4);
  delay(5000);
  L13.write(100, 100, 5, 1000);
  delay(7000);
}

#define delay   M_DELAY
CREATE_FUNCTION(runLed){
  L13.write(2000);
  delay(3000);
  L13.write(300, 300, 4);
  delay(5000);
  L13.write(100, 100, 5, 1000);
  delay(7000);
//  delay(15000);
  runLedFunction_13();
  END_CREATE_FUNCTION
}