#pragma once

#include ".\headers\MotorController.h"

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

void MotorController::writeMotorState() {
  digitalWrite(sleepPin, active);
}

void MotorController::enableMotor() {
  // Serial.println("Enabling motor");
  active = true;
  writeMotorState();
}

void MotorController::disableMotor() {
  // Serial.println("Disabling motor");
  active = false;
  writeMotorState();
}


void MotorController::setDirection(boolean direction) {
  this->direction = direction;
  digitalWrite(dirPin, direction);
  // Serial.println("Setting motor direction");
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
  this->stepSizeIndex = stepSizeIndex;
  int* encodedStepSize = MotorController::ENCODED_STEP_SIZES[stepSizeIndex];
  digitalWrite(ms1, encodedStepSize[0]);
  digitalWrite(ms2, encodedStepSize[1]);
  digitalWrite(ms3, encodedStepSize[2]);
}


void MotorController::stepMotor() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
}

void MotorController::stepMotor(int numSteps) {
  
  if (!active) {
    enableMotor();
  }
  for (int i=0; i<numSteps; i++) {
    stepMotor();  
  }

  // Note: Cant disable here as it is tied to reset, which can cause issues when only doing 1 step
  // disableMotor();
  
  Serial.print("Moved motor: ");
  Serial.println(numSteps);
}
