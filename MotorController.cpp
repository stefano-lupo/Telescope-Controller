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
    pinMode(this->sleepPin, OUTPUT);
    pinMode(this->stepPin, OUTPUT);
    pinMode(this->dirPin, OUTPUT);
    pinMode(this->ms1, OUTPUT);
    pinMode(this->ms2, OUTPUT);
    pinMode(this->ms3, OUTPUT);
    pinMode(this->ledPin, OUTPUT);
    
    digitalWrite(this->dirPin, this->direction);
    digitalWrite(this->sleepPin, this->active);
    digitalWrite(this->ledPin, this->active);
    this->setStepSize(this->stepSizeIndex);
}

void MotorController::toggleMotor() {
  digitalWrite(this->sleepPin, this->active);
  digitalWrite(this->resetPin, this->active);
  digitalWrite(this->ledPin, this->active);
}

void MotorController::enableMotor() {
  Serial.println("Enabling motor");
  this->active = true;
  this->toggleMotor();
}

void MotorController::disableMotor() {
  Serial.println("Disabling motor");
  this->active = false;
  this->toggleMotor();
}

void MotorController::toggleDirection() {
  this->direction = !this->direction;
  digitalWrite(this->dirPin, this->direction);
  Serial.println("Swapping motor direction");
}

void MotorController::increaseSpeed() {
  this->motorTickPeriodMillis -= MotorController::TIME_CHANGE;
}

void MotorController::decreaseSpeed() {
  this->motorTickPeriodMillis += MotorController::TIME_CHANGE;
}

void MotorController::nextStepSize() {
  this->stepSizeIndex = (this->stepSizeIndex + 1) % 5;
}

void MotorController::setStepSize(int stepSizeIndex) {
  int* encodedStepSize = MotorController::ENCODED_STEP_SIZES[stepSizeIndex];
  digitalWrite(this->ms1, encodedStepSize[0]);
  digitalWrite(this->ms2, encodedStepSize[1]);
  digitalWrite(this->ms3, encodedStepSize[2]);
}

void MotorController::stepMotor() {
  if (!this->active) {
//    Serial.println("Had step request but am sleeping");
    return;
  }

//  Serial.println("Stepping Motor");
  digitalWrite(this->stepPin, HIGH);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
  digitalWrite(this->stepPin, LOW);
  delayMicroseconds(MotorController::STEP_PULSE_TIME_MICRO);
}

void MotorController::stepMotor(int numSteps) {
  for (int i=0; i<numSteps; i++) {
    this->stepMotor();  
  }
}

void MotorController::tick() {
  if (!this->active) {
    return;
  }
  
  this->accumulatedTimeMillis += this->interuptPeriodMillis;
  if (this->accumulatedTimeMillis >= this->motorTickPeriodMillis) {
    this->needsMove = true;
    this->accumulatedTimeMillis -= this->motorTickPeriodMillis;
  }
}

void MotorController::moveIfNesc() {
  if (this->needsMove) {
    this->stepMotor();
    this->needsMove = false;
  }
}
