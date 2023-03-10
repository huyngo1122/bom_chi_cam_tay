// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define some steppers and the pins the will use
// AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
// AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
// AccelStepper stepper3(AccelStepper::FULL4WIRE, 7, 5, 6, 4);
AccelStepper stepper3(AccelStepper::FULL4WIRE, 4, 5, 6, 7);
void setup()
{  
    // stepper1.setMaxSpeed(200.0);
    // stepper1.setAcceleration(100.0);
    // stepper1.moveTo(24);
    
    // stepper2.setMaxSpeed(300.0);
    // stepper2.setAcceleration(100.0);
    // stepper2.moveTo(1000000);
    
    stepper3.setMaxSpeed(150.0);
    stepper3.setAcceleration(300.0);
    stepper3.moveTo(2038); 
}

void loop()
{
    // Change direction at the limits
    if (stepper3.distanceToGo() == 0)
	stepper3.moveTo(-stepper3.currentPosition());
    // stepper1.run();
    stepper3.run();
}
