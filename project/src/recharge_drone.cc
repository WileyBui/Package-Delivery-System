#include "../include/recharge_drone.h"
#include "../include/battery.h"
#include "../include/generate_id.h"
#include "../include/json_helper.h"
#include "../include/package.h"
#include "../include/vector.h"
#include <iostream>
// #include "../include/beeline_route.h"
// #include "../include/smart_route.h"
// #include "../include/parabolic_route.h"

namespace csci3081 {
RechargeDrone::RechargeDrone(const picojson::object& val) {
  position = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name = JsonHelper::GetString(val, "name");
  speed = JsonHelper::GetDouble(val, "speed");
  radius = JsonHelper::GetDouble(val, "radius");
  try {
    battery = Battery(JsonHelper::GetDouble(val, "battery_capacity"));
  } catch (std::logic_error a) {
    battery = Battery(20000);
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
void RechargeDrone::ChargeDrone(float dt){
  DeadCarrier->Charging(1000*dt);
  battery.Depleting(1000*dt);
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

bool RechargeDrone::Charging(float sec) {
  return battery.Charging(sec);
}

void RechargeDrone::SetPosition(std::vector<float> agr) {
  position.clear();
  position = agr;
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
  if(DeadCarrier&&IsWithin(DeadCarrier)){//charging finished gotta to back
    DeadCarrier->SetChargingStatus(false);
    if(DeadCarrier->BatteryFull()){
    route.clear();
    const entity_project::IGraph* graph;
    std::vector<vector<float>> path = GetRouteStrategy()->GetRoute(graph,GetPosition(),PositionOfStation);
    std::cout<<path.size()<<std::endl;
		SetRoute(path);
    }
    else{
      DeadCarrier->SetChargingStatus(true);
      std::cout<<"Charging here"<<std::endl;
      ChargeDrone(dt);
      std::cout<<DeadCarrier->GetBattery()<<std::endl;
      return;
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
  //   if (BatteryDead()) {
  //     if (GetName().find("drone") != std::string::npos) {
  //       float groundLevel = 253;

  //       if ((GetPosition().at(1) > groundLevel) && (droneStatusWhenBatteryDies == "not dead yet")) {
  //         route.clear();

  //         std::vector<vector<float>> path;
  //         std::vector<float> destPosition = GetPosition();
  //         destPosition.at(1) = groundLevel;

  //         path.push_back(GetPosition());
  //         path.push_back(destPosition);

  //         dynamic = false;
  //         GetStatus();
  //         dynamic = true;

  //         SetRoute(path);
  //         droneStatusWhenBatteryDies = "battery dead; going towards ground";
  //       } else if ((GetPosition().at(1) <= groundLevel) && (droneStatusWhenBatteryDies == "battery dead; going towards ground")) {
  //         droneStatusWhenBatteryDies = "battery dead; is on ground";
  //         if (HavePackage()) {
  //           Package* pack = DropPackage();
  //           pack->SetRechargeDrone(NULL);
  //           pack->SetDynamic(false);
  //         }
  //         dynamic = false;
  //         route.clear();
  //         GetStatus();
  //       }
  //     }
  //   } else if (dt > GetBattery()) {
  //     dt = GetBattery();
  //   }

  //   if (dt > 0) {
  //     battery.Depleting(dt);
  //     while (true) {
  //       nextPosition = NextPosition();
  //       distance = Distance(Vector3D(GetPosition()), Vector3D(nextPosition));
  //       time = distance / GetSpeed();
  //       if (time >= dt) {
  //         portion = time / dt;
  //         result = Vector3D(GetPosition()) + ((Vector3D(nextPosition) - Vector3D(GetPosition())) / portion);
  //         SetPosition(toVectorFloat(result));
  //         break;
  //       } else if (time > 0) {
  //         SetPosition(nextPosition);
  //         PopPosition();
  //         dt = dt - time;
  //       } else if (time == 0) {
  //         PopPosition();
  //         break;
  //       }
  //     }
  //     if (HavePackage()) {
  //       Package* package = GetPackage();
  //       // Check the status of Package
  //       if (!GetPackage()->IsDynamic()) {
  //         // Need the drone to pick up
  //         if (IsWithin(package)) {
  //           GetPackage()->SetDynamic(true);
  //         }
  //       } else {
  //         // Package is on the drone
  //         if (IsWithin(GetPackage()->GetOwner())) {
  //           DropPackage()->Deliver();
  //           dynamic = false;
  //           GetStatus();
  //         }
  //       }
  //     }
  //   }
  // }
}

}  // namespace csci3081
// RechargeDrone::~Drone(){
//   if (routeStrategy != NULL){
//     delete routeStrategy;
//   }
// }

