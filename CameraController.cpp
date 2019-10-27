#pragma once

#include ".\headers\CameraController.h"

void CameraController::setup() {
}

void CameraController::enableCapturing() {
  Serial.println("Enabling capturing!");
  this->active = true;
  this->accumulatedTimeMillis = 0;
}

void CameraController::disableCapturing() {
  Serial.println("Disabling capturing!");
  this->active = false;
}


void CameraController::toggleShutter() {
    Serial.println("Toggling Shutter");
    this->camera.shutterNow();
    Serial.println("Finished toggling Shutter");
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

void CameraController::formatString(char* str) {
  int remainingTime = (shutterTimeMillis - accumulatedTimeMillis) / 1000;
  // Serial.print("Reminaing ");
  // Serial.println(remainingTime);
  char activeChar = active ? 'A' : 'I';
  int shutterTime = shutterTimeMillis / 1000;
  sprintf(str, "Cam %c %ds %ds", activeChar, shutterTime, remainingTime);
}

void CameraController::snapShot() {
  toggleShutter();
}