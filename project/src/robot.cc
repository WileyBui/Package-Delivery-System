#include "../include/robot.h"
#include "../include/package.h"
#include "../include/battery.h"
#include "../include/vector.h"
#include "../include/json_helper.h"
#include "../include/utils.h"

namespace csci3081 {

Robot::Robot(const picojson::object& val) {
  position  = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name      = JsonHelper::GetString(val, "name");
  speed     = JsonHelper::GetDouble(val, "speed");
  radius    = JsonHelper::GetDouble(val, "radius");
  dynamic   = false;
  version   = 0;
  ID        = EntityHash.nextNumber();
  details   = val;
  battery   = Battery(10000);
  package   = NULL;
  type      = "carrier";
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
}


void Robot::Update(float dt){
  std::vector<float> nextPosition;
	float distance;
	float time;
	float portion;

	Vector3D result;
  if (IsDynamic()){
    battery.Depleting(dt);
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
    if (HavePackage()){
      Package *package = GetPackage();
      // Check the status of Package 
      if (!GetPackage()->IsDynamic()){
        // Need the Robot to pick up
        if (IsWithin(package)){
          GetPackage()->SetDynamic(true);
        }
      }
      else {
        // Package is on the Robot
        if (IsWithin(GetPackage()->GetOwner())){
          DropPackage();
          dynamic = false;
        }
      }
    }
  }
  else {
    battery.Charging(dt);
  }  
}

} // close namespace csci3081
