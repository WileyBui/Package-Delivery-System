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

vector<vector<float>> Drone::GetBeelinePath(std::vector<float> src, 
														                std::vector<float> dest,
														                float droneSpeed,
														                float dt) {
  vector<vector<float>> path;

	Vector3D srcPosition  = Vector3D(src); // current position of the drone
	Vector3D destPosition = Vector3D(dest);
	Vector3D nextPosition = srcPosition; // sets to the current position, for now
	Vector3D flyToPosition;

	bool hasFlownUp 		    = false;
	bool hasFlownHorizontal = false;
	bool hasFlownDown 		  = false;
	float heightToAvoidCollision = 400;

	while (true) {
		if (!hasFlownUp) {
			if (nextPosition.GetY() >= heightToAvoidCollision) {
				// successfully moved up
				hasFlownUp = true;
			} else { 
				// move current position up until heightToAvoidCollision 
				flyToPosition = nextPosition;
				flyToPosition.SetY(heightToAvoidCollision);
			}
		}

		if (hasFlownUp && !hasFlownHorizontal) {
			if (nextPosition.IsWithinXandZRange(destPosition, 3)) {
				// successfully flown to destination position (with y = heightToAvoidCollision)
				hasFlownHorizontal = true;
			} else {
				// move from source position (with y = heightToAvoidCollision)
				// to destination position (with y = heightToAvoidCollision)
				flyToPosition = destPosition;
				flyToPosition.SetY(heightToAvoidCollision);
			}
		}

		if (hasFlownHorizontal && !hasFlownDown) {
			if (Distance(nextPosition, destPosition) <= 5) {
				// successfully flown to destination position
				hasFlownDown = true;
			} else {
				// move toward the destination
				flyToPosition = destPosition;
			}
		}

		// calculate the direction
		Vector3D direction = flyToPosition - nextPosition;

		// normalize the direction
		direction = direction.Normalize();

		// calculate the velocity of the drone
		Vector3D velocity = direction * droneSpeed;

		// calculate the distance traveled over this time step: s = v*dt
		nextPosition = nextPosition + velocity * (dt * 10);

		path.push_back(toVectorFloat(nextPosition));

		if (hasFlownDown) {
			return path;
		}
	}
}

} // close namespace csci3081
