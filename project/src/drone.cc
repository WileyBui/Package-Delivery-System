#include "../include/drone.h"
#include "../include/package.h"
#include "../include/battery.h"
#include "../include/vector.h"
#include "../include/json_helper.h"
#include "../include/utils.h"

namespace csci3081 {

Drone::Drone(const picojson::object& val) {
  position = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name = JsonHelper::GetString(val, "name");
  speed = JsonHelper::GetDouble(val, "speed");
  radius = JsonHelper::GetDouble(val, "radius");
  try {
    battery = Battery(JsonHelper::GetDouble(val, "battery_capacity"));
  }
  catch (std::logic_error a){
    battery = Battery(10000);
  }
  dynamic = false;
  version = 0;
  ID = EntityHash.nextNumber();
  details = val;
  package = NULL;
  type = "carrier";
}

Drone::Drone(Drone& cpy){
  position=cpy.position;
  direction=cpy.direction;
  name = cpy.name;
  radius = cpy.radius;
  dynamic = cpy.dynamic;
  version = cpy.version;
  ID = cpy.ID;
  details = cpy.details;
  battery = cpy.battery;
  package = cpy.package;
  speed = cpy.speed;
  type = "carrier";
}


void Drone::Update(float dt){
  std::vector<float> nextPosition;
	float distance;
	float time;
	float portion;
	Vector3D result;
  if (IsDynamic()){
    std::cout << dt << std::endl;
    if (dt>GetBattery()){
       dt = GetBattery();
    }
    while (true) {
      nextPosition = NextPosition();
      distance = Distance(Vector3D(GetPosition()),Vector3D(nextPosition));
      time = distance/GetSpeed();
      if (time>=dt) {
        portion = time/dt;
        result = Vector3D(GetPosition())+((Vector3D(nextPosition)-Vector3D(GetPosition()))/portion);
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
    battery.Depleting(dt);
    if (HavePackage()){
      Package *package = GetPackage();
      // Check the status of Package 
      if (!GetPackage()->IsDynamic()){
        // Need the drone to pick up
        if (IsWithin(package)){
          GetPackage()->SetDynamic(true);
        }
      }
      else {
        // Package is on the drone
        if (IsWithin(GetPackage()->GetOwner())){
          DropPackage()->Deliver();
          dynamic = false;
        }
      }
    }
  }
  else {
    battery.Charging(dt);
  }  
}

void Drone::GetStatus() {
  picojson::object notification_builder = JsonHelper::CreateJsonNotification();
  if (BatteryDead()){
    JsonHelper::AddStringToJsonObject(notification_builder,"value","idle");
  }
  else {
    JsonHelper::AddStringToJsonObject(notification_builder,"value","moving");
    JsonHelper::AddStdVectorVectorFloatToJsonObject(notification_builder, "path", route);
  }
  picojson::value notification_to_send = JsonHelper::ConvertPicojsonObjectToValue(notification_builder);
  Notify(notification_to_send,*this);
}

} // close namespace csci3081
