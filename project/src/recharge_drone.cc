#include "../include/recharge_drone.h"
#include "../include/battery.h"
#include "../include/generate_id.h"
#include "../include/json_helper.h"
#include "../include/package.h"
#include "../include/vector.h"
#include <iostream>

namespace csci3081 {
RechargeDrone::RechargeDrone(const picojson::object& val) {
  position = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name = JsonHelper::GetString(val, "name");
  speed = JsonHelper::GetDouble(val, "speed");
  radius = JsonHelper::GetDouble(val, "radius");
  try {
    battery = Battery(JsonHelper::GetDouble(val, "battery_capacity"), "recharging_drone");
  } catch (std::logic_error a) {
    battery = Battery(20000, "recharging_drone");
  }
  dynamic = false;
  version = 0;
  ID = GenerateId::GenerateNewId();
  details = val;
  type = "recharging_drone";
  // Checking to see if a route type is specified
  std::string routetype;
  try {
    routetype = JsonHelper::GetString(val, "path");
  }
  catch (...) {
    routetype = "beeline";
  }
  if (routetype == "beeline"){
    routeStrategy = new BeelineRoute();
  }
  else if (routetype == "parabolic"){
    routeStrategy = new ParabolicRoute();
  }
  else{
    routeStrategy = new SmartRoute();
  }
}

RechargeDrone::RechargeDrone(RechargeDrone& cpy) {
  position = cpy.position;
  direction = cpy.direction;
  name = cpy.name;
  radius = cpy.radius;
  dynamic = cpy.dynamic;
  version = cpy.version;
  ID = cpy.ID;
  details = cpy.details;
  battery = cpy.battery;
  speed = cpy.speed;
  type = "recharging_drone";
  routeStrategy = cpy.routeStrategy;
}

bool RechargeDrone::IsCurrentlyCharging() {
  return isCurrentlyCharging;
}

void RechargeDrone::ChargeFromStation(float dt){
  // the recharging station can charge 500x faster
  for (int i = 0; i < 250; i++) {
    if (battery.IsFull()) {
      isCurrentlyCharging = false;
      return;
    } else {
      battery.Charging(dt);
    }
  }
  isCurrentlyCharging = true;
}

bool RechargeDrone::IsChargingCarrierFull(float dt){
  for (int i = 0; i < 250; i++) {
    if (DeadCarrier->BatteryFull()) {
      DeadCarrier->SetChargingStatus(false);
      std::cout << DeadCarrier->GetName() << ": recharge full with battery = " << DeadCarrier->GetBattery() << std::endl;
      return true;
    } else {
      DeadCarrier->SetChargingStatus(true);
      DeadCarrier->Charging(dt);
      battery.Depleting(dt);
    }
  }

  return false;
}

bool RechargeDrone::BatteryDead() {
  return battery.IsDead();
}

bool RechargeDrone::BatteryFull(){
  return battery.IsFull();
}

float RechargeDrone::GetBattery() {
  return battery.GetRemainingLife();
}

float RechargeDrone::GetBatteryMaxCharge() {
  return battery.GetMaxCharge();
}

bool RechargeDrone::Charging(float sec) {
  return battery.Charging(sec);
}

void RechargeDrone::SetPosition(std::vector<float> agr) {
  position.clear();
  position = agr;
}

void RechargeDrone::SetDynamic(bool dynamic_) {
  dynamic = dynamic_;
}

void RechargeDrone::SetSpeed(float s) {
  if (s >= 0) {
    speed = s;
  }
}

float RechargeDrone::GetSpeed() {
  return speed;
}

void RechargeDrone::SetRoute(std::vector<std::vector<float>> v) {
  route = v;
  dynamic = true;
}

std::vector<float> RechargeDrone::NextPosition() {
  std::vector<float> temp;
  // Check for next position, if there is none, return current position
  if (route.size() > 0) {
    temp = route[0];
  } else {
    temp = position;
  }
  return temp;
}

void RechargeDrone::PopPosition() {
  if (route.size() > 0) {
    route.erase(route.begin());
  }
  if (route.size() == 0) {
    dynamic = false;

    if (!alreadyNotified) {
      GetStatus();
      alreadyNotified = true;
    }
  }
}

void RechargeDrone::GetStatus() {
  picojson::object notification_builder = JsonHelper::CreateJsonNotification();
  if (!IsDynamic()) {
    JsonHelper::AddStringToJsonObject(notification_builder, "value", "idle");
  } else {
    JsonHelper::AddStringToJsonObject(notification_builder, "value", "moving");
    JsonHelper::AddStdVectorVectorFloatToJsonObject(notification_builder, "path", route);
  }
  picojson::value notification_to_send = JsonHelper::ConvertPicojsonObjectToValue(notification_builder);
  Notify(notification_to_send, *this);
}

RouteStrategy* RechargeDrone::GetRouteStrategy(){
  return routeStrategy;
}

bool RechargeDrone::IsChargingACarrier(){
  return (DeadCarrier && DeadCarrier->IsCurrentlyCharging());
}

void RechargeDrone::SetDeadCarrier(Carrier* carrier){
    dynamic = true;
   DeadCarrier = carrier;
 }

Carrier* RechargeDrone::GetDeadCarrier(){
  return DeadCarrier;
}

void RechargeDrone::SetPositionOfStation(vector<float> station){
  PositionOfStation = station;
}

vector<float> RechargeDrone::GetPositionOfStation(){
  return PositionOfStation;
}

void RechargeDrone::Update(float dt){
  if(DeadCarrier&&(DistanceBetween(DeadCarrier) < 20)){
    if(IsChargingCarrierFull(dt)) {
      //charging finished, gotta to back
      DeadCarrier->SetDroneStatusWhenBatteryDies("not dead yet");
      SetDeadCarrier(NULL);

      route.clear();
      alreadyNotified = false;
      
      if (battery.GetRemainingLife() < battery.GetMaxCharge() * 0.2) {
        std::cout << "Recharging drone needs to be recharged... heading back to station!" << std::endl;
        const entity_project::IGraph* graph;
        std::vector<vector<float>> path = GetRouteStrategy()->GetRoute(graph,GetPosition(),PositionOfStation);
        SetRoute(path);
        GetStatus();
      } else {
        std::cout << "Recharging drone is done charging a carrier; waiting for the next dead carrier..." << battery.GetRemainingLife() << std::endl;
      }
    }
  }
  
  std::vector<float> nextPosition;
  float distance;
  float time;
  float portion;
  Vector3D result;
  if (dt > GetBattery()) {
      dt = GetBattery();
  }
  if (dt > 0) {
    battery.Depleting(dt);
    while(true){
      nextPosition = NextPosition();
      distance = Distance(Vector3D(GetPosition()), Vector3D(nextPosition));
      time = distance / GetSpeed();
      if (time >= dt) {
        portion = time / dt;
        result = Vector3D(GetPosition()) + ((Vector3D(nextPosition) - Vector3D(GetPosition())) / portion);
        SetPosition(toVectorFloat(result));
        break;
      } 
      else if (time > 0) {
        SetPosition(nextPosition);
        PopPosition();
        dt = dt - time;
      }
      else if (time == 0) {
        PopPosition();
        break;
      }
    }
  }
}

}  // namespace csci3081
