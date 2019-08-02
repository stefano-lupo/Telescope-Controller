#pragma once

#include "CameraController.h"

void CameraController::setup() {
  pinMode(this->ledPin, OUTPUT);
  digitalWrite(this->ledPin, this->active);
}

void CameraController::enableCapturing() {
  Serial.println("Enabling capturing!");
  this->active = true;
  this->accumulatedTimeMillis = 0;
  digitalWrite(this->ledPin, this->active);
}

void CameraController::disableCapturing() {
  Serial.println("Disabling capturing!");
  this->active = false;
  digitalWrite(this->ledPin, this->active);
}


void CameraController::toggleShutter() {
    Serial.println("Toggling Shutter");
    digitalWrite(this->ledPin, HIGH);
    this->camera.shutterNow();
    Serial.println("Finished toggling Shutter");
    digitalWrite(this->ledPin, LOW);
}

void CameraController::shutterIfNesc() {
  if (this->hasShutterToggle) {
    this->toggleShutter();
    this->hasShutterToggle = false;
  }
}

void CameraController::tick() {
  if (!this->active) {
    return;
  }
  this->accumulatedTimeMillis += this->interuptPeriodMillis;
  if (this->accumulatedTimeMillis >= this->shutterTimeMillis) {
    this->hasShutterToggle = true;
    this->accumulatedTimeMillis -= this->shutterTimeMillis;
  }
}

void CameraController::increaseShutterTime() {
  this->shutterTimeMillis += SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS;
//  Serial.print("New shutterTime  (ms): ");
//  Serial.println(this->shutterTimeMillis);
}

void CameraController::decreaseShutterTime() {
  this->shutterTimeMillis = max(0, this->shutterTimeMillis - SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS);
//  Serial.print("New shutterTime  (ms): ");
//  Serial.println(this->shutterTimeMillis);
}

void CameraController::setShutterTime(int shutterTimeMillis) {
  this->shutterTimeMillis = shutterTimeMillis;
}
