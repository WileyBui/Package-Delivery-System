#include <iostream>
#include "../include/battery.h"
#include "../include/generate_id.h"
#include <cmath>

namespace csci3081 {

Battery::Battery() {
    BatteryID = GenerateId::GenerateNewId();
    remainingLifeinSec = 0;
}

Battery::Battery(float remainingLifeinSec_) {
    BatteryID = GenerateId::GenerateNewId();
    if (remainingLifeinSec_ < 0) {                                  // invalid negative life
        remainingLifeinSec = 0;
    }
    else if (remainingLifeinSec_ > maxCharge) {                         // over maximum capacity
        remainingLifeinSec = maxCharge;
    }
    else {
        remainingLifeinSec = remainingLifeinSec_;
    }
}

float Battery::GetRemainingLife() {
    return remainingLifeinSec;
}

bool Battery::IsDead() {
    if (remainingLifeinSec<1e-6) {
        return true;
    }
    return false;
}

int Battery::GetId() {
    return BatteryID;
}

void Battery::Depleting(float sec) {
    if (sec<=0){                                            // depleting invalid negative value
        return;
    }
    if (remainingLifeinSec>sec) {                           
        remainingLifeinSec = remainingLifeinSec - sec;
    }
    else {                                                  // Deplete more than remaining life
        remainingLifeinSec = 0;
    }
}

bool Battery::Charging(float sec) {
    if (sec<=0){                                                // Charging invalid negative value
        return false;
    }
    if (remainingLifeinSec+sec<maxCharge) {
        remainingLifeinSec += sec;
    }
    else {                                                      // Charge more than max capacity
        remainingLifeinSec = 100;
    }
}
bool Battery::IsFull(){
    return (remainingLifeinSec == maxCharge);
}



float Battery::TimeToFull() {
    return maxCharge - remainingLifeinSec;
}

int Battery::GetDisplayBar() {
    displayBar = floor(remainingLifeinSec*5.0/maxCharge);
    return displayBar;
}
}

