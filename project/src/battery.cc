#include <iostream>
#include "../include/battery.h"
#include "../include/utils.h"

namespace csci3081 {

Battery::Battery() {
    BatteryID = BatteryHash.nextNumber();
    remainingLifeinSec = 0;
    displayBar = floor(remainingLifeinSec*5.0/maxCharge);
    if (displayBar>1) {
        isDead = false;
    }
    else {
        isDead = true;
    }
}

Battery::Battery(float remainingLifeinSec_) {
    BatteryID = BatteryHash.nextNumber();
    if (remainingLifeinSec_ < 0) {                                  // invalid negative life
        remainingLifeinSec = 0;
    }
    else if (remainingLifeinSec_ > 10000) {                         // over maximum capacity
        remainingLifeinSec = 10000;
    }
    else {
        remainingLifeinSec = remainingLifeinSec_;
    }

    // Calculate displayBar
    displayBar = floor(remainingLifeinSec*5.0/maxCharge);

    // From DisplayBar determine the bool value of isDead
    if (displayBar>1) {
        isDead = false;
    }
    else {
        isDead = true;
    }
}

float Battery::GetRemainingLife() {
    return remainingLifeinSec;
}

bool Battery::IsDead() {
    return isDead;
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
        isDead = true;
    }

    displayBar = floor(remainingLifeinSec*5.0/maxCharge);
    if (displayBar>1) {
        isDead = false;
    }
    else {
        isDead = true;
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
        remainingLifeinSec = 10000;
    }
    displayBar = floor(remainingLifeinSec*5.0/maxCharge);
    if (displayBar>1) {
        isDead = false;
    }
    else {
        isDead = true;
    }
    return true;
}


float Battery::TimeToFull() {
    return maxCharge - remainingLifeinSec;
}

int Battery::GetDisplayBar() {
    return displayBar;
}
}

