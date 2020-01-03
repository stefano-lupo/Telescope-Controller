#pragma once

#include ".\headers\CameraController.h"

void CameraController::setup() {
}

void CameraController::enableCapturing() {
  Serial.println("Enabling capturing!");
  active = true;
  accumulatedTimeMillis = 0;
}

void CameraController::disableCapturing() {
  Serial.println("Disabling capturing!");
  active = false;
}


void CameraController::toggleShutter() {
    Serial.println("Toggling Shutter");
    camera.shutterNow();
    Serial.println("Finished toggling Shutter");
}

void CameraController::shutterIfNesc() {
  if (hasShutterToggle) {
    toggleShutter();
    hasShutterToggle = false;
  }
}

void CameraController::tick() {
  if (active) {
    return;
  }

  // Toggle shutter on start
  if (accumulatedTimeMillis == 0) {
    hasShutterToggle = true;
  }

  accumulatedTimeMillis += interuptPeriodMillis;
  if (accumulatedTimeMillis >= shutterTimeMillis) {
    hasShutterToggle = true;
    accumulatedTimeMillis -= (shutterTimeMillis + cooldownPeriodMillis);
  }
}

void CameraController::increaseShutterTime() {
  shutterTimeMillis += SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS;

}

void CameraController::decreaseShutterTime() {
  shutterTimeMillis = max(0, shutterTimeMillis - SHUTTER_TIME_CHANGE_RESOLUTION_MILLIS);
//  Serial.print("New shutterTime  (ms): ");
//  Serial.println(shutterTimeMillis);
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