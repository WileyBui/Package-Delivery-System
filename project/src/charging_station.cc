#include "../include/charging_station.h"

#include <EntityProject/entity.h>

#include <algorithm>

#include "../include/generate_id.h"
#include "../include/vector.h"

namespace csci3081 {
ChargingStation::ChargingStation(const picojson::object& detail) {
  position = JsonHelper::GetStdFloatVector(detail, "position");
  direction = JsonHelper::GetStdFloatVector(detail, "direction");
  name = JsonHelper::GetString(detail, "name");
  radius = JsonHelper::GetDouble(detail, "radius");
  dynamic = false;
  version = 0;
  ID = GenerateId::GenerateNewId();
  details = detail;
  type = "charging_station";
}

ChargingStation::ChargingStation(ChargingStation& chargingStation) {
  this->position = chargingStation.GetPosition();
  this->direction = chargingStation.GetDirection();
  name = chargingStation.GetName();
  radius = chargingStation.GetRadius();
  dynamic = false;
  version = chargingStation.GetVersion();
  ID = chargingStation.GetId();
  details = chargingStation.GetDetails();
  type = "charging_station";
}

bool ChargingStation::IsDroneWithinRadius(Drone* currentDrone, float radius) {
  if (Distance(Vector3D(GetPosition()), Vector3D(currentDrone->GetPosition())) < radius) {
    return true;
  }
  return false;
}

bool ChargingStation::AddDrone(Drone* currentDrone) {
  // adds drone to the charging station only if the distance is close together
  // also checks if current drone is already at the charging station
  if (IsDroneWithinRadius(currentDrone, 10)) {
    if (!(std::find(dronesAtStation.begin(), dronesAtStation.end(), currentDrone) != dronesAtStation.end())) {
      dronesAtStation.push_back(currentDrone);
    }
    return true;
  }
  return false;
}

void ChargingStation::Update(float dt) {
  for (Drone* drone : dronesAtStation) {
    if (IsDroneWithinRadius(drone, 10)) {
      drone->Charging(dt);
    } else {
      // removes drone if out of radius from the charging station
      dronesAtStation.erase(std::remove(dronesAtStation.begin(), dronesAtStation.end(), drone), dronesAtStation.end());
    }
  }
}

}  // namespace csci3081