#include "../include/carrier.h"
#include "../include/package.h"
#include "../include/battery.h"
#include "../include/vector.h"
#include "../include/json_helper.h"
#include "../include/utils.h"

namespace csci3081 {

bool Carrier::BatteryDead() {
  return battery.IsDead();
}

bool Carrier::Charging(float sec){
  return battery.Charging(sec);
}

bool Carrier::HavePackage() {
  if (package == NULL) {
    return false;
  }
  else {
    return true;
  }
}

Package* Carrier::GetPackage(){
  return package;
}

bool Carrier::AddPackage(Package* arg){
  dynamic = true;
  if (HavePackage()) {
    return false;
  }
  else {
    package = arg;
    return true;
  }
}

Package* Carrier::DropPackage(){
  Package* drop;
  drop = package;
  if (package!=NULL) {
    package->Deliver();
    package = NULL;
  }
  return drop;
}

void Carrier::SetPosition(std::vector<float> agr){
  position.clear();
  position = agr;
}

void Carrier::SetSpeed(float s){
  if (s>=0){
    speed = s;
  }
}
float Carrier::GetSpeed() {
  return speed;
}

void Carrier::AddPosition(std::vector<float> v){
  route.push_back(v);
  dynamic = true;
}

std::vector<float> Carrier::NextPosition() {
  std::vector<float> temp;
  // Check for next position, if there is none, return current position
  if (route.size()>0) {
    temp = route[0];
  }
  else {
    temp = position;
  }
  return temp;
}

void Carrier::PopPosition(){
  if (route.size()>0){
    route.erase(route.begin());
  }
  if (route.size() == 0){
    dynamic = false;
  }
}

} // close namespace csci3081
