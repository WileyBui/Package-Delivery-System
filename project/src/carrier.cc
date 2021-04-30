#include "../include/carrier.h"

#include "../include/battery.h"
#include "../include/json_helper.h"
#include "../include/package.h"
#include "../include/vector.h"

namespace csci3081 {

bool Carrier::BatteryDead() {
  return battery.IsDead();
}
bool Carrier::BatteryFull() {
  return battery.IsFull();
}
float Carrier::GetBattery() {
  return battery.GetRemainingLife();
}
float Carrier::GetMaxBattery() {
  return battery.GetMaxCharge();
}

bool Carrier::Charging(float sec) {
  return battery.Charging(sec);
}

bool Carrier::HavePackage() {
  if (package == NULL) {
    return false;
  } else {
    return true;
  }
}

Package* Carrier::GetPackage() {
  return package;
}

bool Carrier::AddPackage(Package* arg) {
  dynamic = true;
  if (HavePackage()) {
    return false;
  } else {
    package = arg;
    return true;
  }
}

Package* Carrier::DropPackage() {
  Package* drop;
  drop = package;
  if (package != NULL) {
    package = NULL;
  }
  return drop;
}

void Carrier::SetPosition(std::vector<float> agr) {
  position.clear();
  position = agr;
}

void Carrier::SetSpeed(float s) {
  if (s >= 0) {
    speed = s;
  }
}

float Carrier::GetSpeed() {
  return speed;
}

void Carrier::SetRoute(std::vector<std::vector<float>> v) {
  route = v;
  dynamic = true;
}

std::vector<float> Carrier::NextPosition() {
  std::vector<float> temp;
  // Check for next position, if there is none, return current position
  if (route.size() > 0) {
    temp = route[0];
  } else {
    temp = position;
  }
  return temp;
}

void Carrier::PopPosition() {
  if (route.size() > 0) {
    route.erase(route.begin());
  }
  if (route.size() == 0) {
    dynamic = false;
  }
}

void Carrier::GetStatus() {
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

RouteStrategy* Carrier::GetRouteStrategy() {
  return routeStrategy;
}

bool Carrier::IsCurrentlyCharging() {
  return ChargingStatus;
}

void Carrier::SetChargingStatus(bool b) {
  ChargingStatus = b;
}

void Carrier::SetDroneStatusWhenBatteryDies(std::string status) {
  droneStatusWhenBatteryDies = status;
}

std::string Carrier::GetDroneStatusWhenBatteryDies() {
  return droneStatusWhenBatteryDies;
}

void Carrier::GoDownToGround() {
  // drone
  if (GetName().find("drone") != std::string::npos) {
    float groundLevel = 253;

    if ((GetPosition().at(1) > groundLevel) && (droneStatusWhenBatteryDies == "not dead yet")) {
      route.clear();

      std::vector<vector<float>> path;
      std::vector<float> destPosition = GetPosition();
      destPosition.at(1) = groundLevel;

      path.push_back(GetPosition());
      path.push_back(destPosition);

      dynamic = false;
      GetStatus();
      dynamic = true;

      SetRoute(path);
      droneStatusWhenBatteryDies = "battery dead; going towards ground";
    } else if ((GetPosition().at(1) <= groundLevel) && (droneStatusWhenBatteryDies == "battery dead; going towards ground")) {
      droneStatusWhenBatteryDies = "battery dead; is on ground";
      if (HavePackage()) {
        Package* pack = DropPackage();
        pack->SetCarrier(NULL);
        pack->SetDynamic(false);
      }
      dynamic = false;
      route.clear();
      GetStatus();
    }
  } else {
    // robot; doesn't need to go to "ground" since robot stays at ground level
    if (droneStatusWhenBatteryDies == "not dead yet") {
      droneStatusWhenBatteryDies = "battery dead; is on ground";
      if (HavePackage()) {
        Package* pack = DropPackage();
        pack->SetCarrier(NULL);
        pack->SetDynamic(false);
      }
      dynamic = false;
      route.clear();
      GetStatus();
    }
  }
}

Battery* Carrier::GetBatteryObj(){
  return &battery;
}

void Carrier::Update(float dt) {
  std::vector<float> nextPosition;
  float distance;
  float time;
  float portion;
  Vector3D result;
  if (IsDynamic()) {
    if (BatteryDead()) {
      GoDownToGround();
    } else if (dt > GetBattery()) {
      dt = GetBattery();
    }

    if (dt > 0) {
      battery.Depleting(dt);
      while (true) {
        nextPosition = NextPosition();
        distance = Distance(Vector3D(GetPosition()), Vector3D(nextPosition));
        time = distance / GetSpeed();
        if (time >= dt) {
          portion = time / dt;
          result = Vector3D(GetPosition()) + ((Vector3D(nextPosition) - Vector3D(GetPosition())) / portion);
          SetPosition(toVectorFloat(result));
          break;
        } else if (time > 0) {
          SetPosition(nextPosition);
          PopPosition();
          dt = dt - time;
        } else if (time == 0) {
          PopPosition();
          break;
        }
      }
      if (HavePackage()) {
        Package* package = GetPackage();
        // Check the status of Package
        if (!GetPackage()->IsDynamic()) {
          // Need the drone to pick up
          if (IsWithin(package)) {
            GetPackage()->SetDynamic(true);
          }
        } else {
          // Package is on the drone
          if (IsWithin(GetPackage()->GetOwner())) {
            DropPackage()->Deliver();
            dynamic = false;
            GetStatus();
          }
        }
      }
    }
  }
}
}  // namespace csci3081