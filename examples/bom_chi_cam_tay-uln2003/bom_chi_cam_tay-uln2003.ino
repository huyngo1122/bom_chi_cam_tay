// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

// #include <AccelStepper.h>
/*
so do chan ket noi mach dieu khien dong co step ULN2003
///////////////////////////////////////
Arduino NANO              ULN2003
    4                       IN4
    5                       IN2
    6                       IN3
    7                       IN1
doi voi ULN2003 1 vong quay se can 2038 buoc
*/
/////////////////////////////////////

#include <AccelStepper_huy.h>
#include "OneButton.h"
#include "huy_debug.h"
// khai báo chân nút nhấn
#define PIN_INPUT 9
#define step_back -2038
// set động cơ quay 10 vòng
#define set_step -20380
// lùi lại 3 vòng(đối với động cơ ULN2003)
#define back_value_end_step -6114
// gia tốc khi quay thuận
#define MaxSpeed_forwards 300.0
#define Acceleration_forwards 200.0
// gia tốc khi quay ngược
#define MaxSpeed_backwards 500.0
#define Acceleration_backwards 500.0

// Define some steppers and the pins the will use
// AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
// AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);

OneButton button(PIN_INPUT, true);
unsigned long pressStartTime_button;

// AccelStepper stepper3(AccelStepper::FULL4WIRE, 7, 5, 6, 4);
AccelStepper_huy stepper3(AccelStepper_huy::FULL4WIRE, 4, 5, 6, 7);
long step_value = 0;

///////////////////////////////////////
void checkTicks()
{
  // include all buttons here to be checked
  button.tick(); // just call tick() to check the state.
}
/////////////////////////////////////

void pressStart()
{

  step_value = set_step;
  stepper3.setMaxSpeed(MaxSpeed_forwards);     // TOC do toi da cho phep
  stepper3.setAcceleration(Acceleration_forwards); // gia toc so cang lon gia toc cang nhanh
  stepper3.moveTo(step_value);     // vi tri doi voi uln2003 1 vong quay se can 2038 buoc

  // HUY_DEBUG("currentPos:    ");

  // gia tri buoc dang chay
  //  HUY_DEBUG_LN(stepper3.currentPosition());

  // HUY_DEBUG("targetPos:    ");
  // gia trị bước đã set trong moveTo
  // HUY_DEBUG_LN(stepper3.targetPosition());

  pressStartTime_button = millis() - 500; // as set in setPressTicks()
} // pressStart()

/////////////////////////////////////
// this function will be called when the button was released after a long hold.
void pressStop()
{

  HUY_DEBUG_LN(stepper3.currentPosition());
  stepper3.setMaxSpeed(MaxSpeed_backwards);     // TOC do toi da cho phep
  stepper3.setAcceleration(Acceleration_backwards); // gia toc so cang lon gia toc cang nhanh
  if (stepper3.currentPosition() > step_back)
  {
    stepper3.moveTo(-stepper3.currentPosition());
  }
  else if (stepper3.currentPosition() < step_back)
  {
    stepper3.moveTo(stepper3.currentPosition() - step_back);
  }

} // pressStop()
  /////////////////////////////////////
void doubleClick()
{
  // khi không sử dụng nữa thì nhấn double click dể trả lại giá trị nén trong ống chì,
  // tránh thất thoát chì khong mong muốn
  stepper3.moveTo(stepper3.currentPosition() - back_value_end_step);
stepper3.setMaxSpeed(MaxSpeed_backwards);     // TOC do toi da cho phep
  stepper3.setAcceleration(Acceleration_backwards); // gia toc so cang lon gia toc cang nhanh

} // doubleClick
void setup()
{
  Serial.begin(115200);
  HUY_DEBUG_LN("One Button Example with interrupts.");

  // setup interrupt routine
  // when not registering to the interrupt the sketch also works when the tick is called frequently.
  attachInterrupt(digitalPinToInterrupt(PIN_INPUT), checkTicks, CHANGE);
  button.attachDoubleClick(doubleClick);
  button.setPressTicks(500); // that is the time when LongPressStart is called
  button.attachLongPressStart(pressStart);
  button.attachLongPressStop(pressStop);

  // stepper3.moveTo(2038); // vi tri doi voi uln2003 1 vong quay se can 2038 buoc
}

/////////////////////////////////////
void stop_step()
{
  // HUY_DEBUG_LN("stop");
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  stepper3.setCurrentPosition(0);
}

/////////////////////////////////////

void loop()
{
  // Change direction at the limits

  stepper3.run();

  if (stepper3.distanceToGo() == 0)
    stop_step();

  button.tick();
}
