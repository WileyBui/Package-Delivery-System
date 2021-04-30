#include "../include/battery.h"

#include <cmath>
#include <iostream>

#include "../include/generate_id.h"

namespace csci3081 {

Battery::Battery() {
  BatteryID = GenerateId::GenerateNewId();
  remainingLifeinSec = 0;
}

Battery::Battery(float remainingLifeinSec_, std::string batteryType) {
    BatteryID = GenerateId::GenerateNewId();

    if (batteryType == "recharging_drone") {                        // recharging drone's default capacity
        maxCharge = 20000;
    } 
    else {                                                          // carrier's default capacity
        maxCharge = 10000;
    }

    if (remainingLifeinSec_ < 0) {                                  // invalid negative life
        remainingLifeinSec = 0;
    }
    else if (remainingLifeinSec_ > maxCharge) {                     // over maximum capacity
        remainingLifeinSec = maxCharge;
    }
    else {
        maxCharge = remainingLifeinSec_;
        remainingLifeinSec = remainingLifeinSec_;
    }
}

float Battery::GetRemainingLife() {
  return remainingLifeinSec;
}

float Battery::GetMaxCharge() {
  return maxCharge;
}

bool Battery::IsDead() {
  if (remainingLifeinSec < 1e-6) {
    return true;
  }
  return false;
}

int Battery::GetId() {
  return BatteryID;
}

void Battery::Depleting(float sec) {
  if (sec <= 0) {  // depleting invalid negative value
    return;
  }
  if (remainingLifeinSec > sec) {
    remainingLifeinSec = remainingLifeinSec - sec;
  } else {  // Deplete more than remaining life
    remainingLifeinSec = 0;
  }
}

bool Battery::Charging(float sec) {
  if (sec <= 0) {  // Charging invalid negative value
    return false;
  }
  if (remainingLifeinSec + sec < maxCharge) {
    remainingLifeinSec += sec;
  } else {  // Charge more than max capacity
    remainingLifeinSec = maxCharge;
  }
  return true;
}

bool Battery::IsFull() {
  return (remainingLifeinSec >= maxCharge);
}

float Battery::TimeToFull() {
  return maxCharge - remainingLifeinSec;
}

int Battery::GetDisplayBar() {
  displayBar = floor(remainingLifeinSec * 5.0 / maxCharge);
  return displayBar;
}
}  // namespace csci3081
