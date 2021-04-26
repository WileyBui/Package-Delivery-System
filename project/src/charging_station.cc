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

bool ChargingStation::IsChargingDroneWithinRadius(ChargingDrone* chargingDrone, float radius) {
  if (Distance(Vector3D(GetPosition()), Vector3D(chargingDrone->GetPosition())) < radius) {
    return true;
  }
  return false;
}

void ChargingStation::AddDeadCarrier(Carrier* carrier) {
  if (!(std::find(deadCarriers.begin(), deadCarriers.end(), carrier) != deadCarriers.end())) {
    deadCarriers.push_back(carrier);
  }
}

void ChargingStation::PopDeadCarrier() {
  if (!deadCarriers.empty()) {
    deadCarriers.erase(deadCarriers.begin());
  }
}

bool ChargingStation::AddChargingDrone(ChargingDrone* chargingDrone) {
  // adds drone to the charging station only if the distance is close together
  if (IsChargingDroneWithinRadius(chargingDrone, 10)) {
    // checks if current drone has already at the charging station
    if (!(std::find(chargingDronesAtStation.begin(), chargingDronesAtStation.end(), chargingDrone) != chargingDronesAtStation.end())) {
      chargingDronesAtStation.push_back(chargingDrone);
    }
    return true;
  }
  return false;
}

void ChargingStation::RemoveChargingDrone(ChargingDrone* chargingDrone) {
  chargingDronesAtStation.erase(std::remove(chargingDronesAtStation.begin(), chargingDronesAtStation.end(), chargingDrone), chargingDronesAtStation.end());
}

void ChargingStation::Update(float dt) {
  float fullChargingDroneBattery = 20000;
  for (ChargingDrone* chargingDrone : chargingDronesAtStation) {
    // still has dead carriers
    if (IsChargingDroneWithinRadius(chargingDrone, 10) && (chargingDrone.GetBattery() >= fullChargingDroneBattery * 0.80) && (!deadCarriers.empty())) {
      // assign chargingDrone to go to deadCarrier
      
      RemoveChargingDrone(chargingDrone);
      PopDeadCarrier();
    } else if (!IsChargingDroneWithinRadius(chargingDrone, 10)) {
      // removes drone if out of radius from the charging station
      RemoveChargingDrone(chargingDrone);
    } else if ((chargingDrone.GetBattery() < fullChargingDroneBattery)){
      // keeps charging the charging drone
    }
  }
}

}  // namespace csci3081

