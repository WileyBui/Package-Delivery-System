#include "../include/drone.h"
#include "../include/battery.h"
#include "../include/generate_id.h"
#include "../include/json_helper.h"
#include "../include/package.h"
#include "../include/vector.h"

namespace csci3081 {

Drone::Drone(const picojson::object& val) {
  position = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name = JsonHelper::GetString(val, "name");
  speed = JsonHelper::GetDouble(val, "speed");
  radius = JsonHelper::GetDouble(val, "radius");
  try {
    battery = Battery(JsonHelper::GetDouble(val, "battery_capacity"));
  } catch (std::logic_error a) {
    battery = Battery(10000);
  }
  dynamic = false;
  version = 0;
  ID = GenerateId::GenerateNewId();
  details = val;
  package = NULL;
  type = "carrier";
}

Drone::Drone(Drone& cpy) {
  position = cpy.position;
  direction = cpy.direction;
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

vector<vector<float>> Drone::GetBeelinePath(std::vector<float> src, std::vector<float> dest) {
  vector<vector<float>> path;

  Vector3D srcPosition = Vector3D(src);   // current position of the drone
  Vector3D destPosition = Vector3D(dest); // destination position of the drone
  Vector3D flyToPosition;

  float heightToAvoidCollision = 400;     // height where the drone must not touch any building

  path.push_back(toVectorFloat(srcPosition));

  // Go up to heightToAvoidCollision from the source location
  flyToPosition = srcPosition;
  flyToPosition.SetY(heightToAvoidCollision);
  path.push_back(toVectorFloat(flyToPosition));

  // Go horizontally to the destination location
  flyToPosition = destPosition;
  flyToPosition.SetY(heightToAvoidCollision);
  path.push_back(toVectorFloat(flyToPosition));

  // Go down to reach the source location
  flyToPosition = destPosition;
  path.push_back(toVectorFloat(flyToPosition));

  return path;
}

}  // namespace csci3081
