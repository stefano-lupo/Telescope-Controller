#pragma once

#include ".\headers\MotorController.h"

void MotorController::setup() {
    pinMode(sleepPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(ms1, OUTPUT);
    pinMode(ms2, OUTPUT);
    pinMode(ms3, OUTPUT);
    
    digitalWrite(dirPin, direction);
    digitalWrite(sleepPin, active);
    setStepSize(MotorStepConfigs::FULL_STEP);
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
}

void MotorController::setStepSize(const MotorStepConfig& config) {
  digitalWrite(ms1, config.ms1);
  digitalWrite(ms2, config.ms3);
  digitalWrite(ms3, config.ms2);
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
