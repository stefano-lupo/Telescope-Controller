#pragma once

#include "MotorController.h"

const int MotorController::ENCODED_STEP_SIZES[5][3] = {
  {LOW, LOW, LOW},    // Full
  {HIGH, LOW, LOW},   // Half
  {LOW, HIGH, LOW},   // Quarter
  {HIGH, HIGH, LOW},  // Eighth    
  {HIGH, HIGH, HIGH}  // Sixteenth
};

void MotorController::setup() {
    pinMode(sleepPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(ms1, OUTPUT);
    pinMode(ms2, OUTPUT);
    pinMode(ms3, OUTPUT);
    
    digitalWrite(dirPin, direction);
    digitalWrite(sleepPin, active);
    setStepSize(stepSizeIndex);
    disableMotor();
}

void MotorController::toggleMotor() {
  digitalWrite(sleepPin, active);
}

void MotorController::enableMotor() {
  Serial.println("Enabling motor");
  active = true;
  toggleMotor();
}

void MotorController::disableMotor() {
   Serial.println("Disabling motor");
  active = false;
  toggleMotor();
}


void MotorController::setDirection(boolean direction) {
  direction = direction;
  digitalWrite(dirPin, direction);
  // Serial.println("Setting motor direction");
}


void MotorController::increaseSpeed() {
  motorTickPeriodMillis -= MotorController::TIME_CHANGE;
}

void MotorController::decreaseSpeed() {
  motorTickPeriodMillis += MotorController::TIME_CHANGE;
}

void MotorController::setFullStep() {
  setStepSize(0);
}

void MotorController::setHalfStep() {
  setStepSize(1);
}

void MotorController::setQuarterStep() {
  setStepSize(2);
}

void MotorController::setStepSize(int stepSizeIndex) {
  stepSizeIndex = stepSizeIndex;
  int* encodedStepSize = MotorController::ENCODED_STEP_SIZES[stepSizeIndex];
  digitalWrite(ms1, encodedStepSize[0]);
  digitalWrite(ms2, encodedStepSize[1]);
  digitalWrite(ms3, encodedStepSize[2]);
}


void MotorController::stepMotor() {
  // enableMotor();
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
  // disableMotor();
}

void MotorController::stepMotor(int numSteps) {
  // enableMotor();
  if (!active) {
    enableMotor();
  }
  for (int i=0; i<numSteps; i++) {
    stepMotor();  
  }
  // disableMotor();
}
