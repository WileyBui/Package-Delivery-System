#include "../include/drone.h"
#include "../include/package.h"
#include "../include/battery.h"
#include "../include/vector.h"
#include "../include/json_helper.h"
#include "../include/generate_id.h"

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
  ID = GenerateId::GenerateNewId();
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

} // close namespace csci3081
