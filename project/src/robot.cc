#include "../include/robot.h"
#include "../include/package.h"
#include "../include/battery.h"
#include "../include/vector.h"
#include "../include/json_helper.h"
#include "../include/generate_id.h"
#include "../include/smart_route.h"


namespace csci3081 {

Robot::Robot(const picojson::object& val) {
  position  = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name      = JsonHelper::GetString(val, "name");
  speed     = JsonHelper::GetDouble(val, "speed");
  radius    = JsonHelper::GetDouble(val, "radius");
  dynamic   = false;
  version   = 0;
  ID        = GenerateId::GenerateNewId();
  details   = val;
  try {
    battery = Battery(JsonHelper::GetDouble(val, "battery_capacity"));
  }
  catch (std::logic_error a){
    battery = Battery(10000);
  }
  package   = NULL;
  type      = "carrier";
  routeStrategy = new SmartRoute(); //robot can only implement smart route
  }


Robot::Robot(Robot& cpy){
  position  = cpy.position;
  direction = cpy.direction;
  name      = cpy.name;
  radius    = cpy.radius;
  dynamic   = cpy.dynamic;
  version   = cpy.version;
  ID        = cpy.ID;
  details   = cpy.details;
  battery   = cpy.battery;
  package   = cpy.package;
  speed     = cpy.speed;
  type      = "carrier";
  routeStrategy = cpy.routeStrategy;
}

// Robot::~Robot(){
//   delete routeStrategy;
// }

} // close namespace csci3081
