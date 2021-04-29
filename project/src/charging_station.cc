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

void ChargingStation::AddDeadCarrier(Carrier* carrier) {
  if (!HasDeadCarrier(carrier)) {
    deadCarriers.push_back(carrier);
  }
}

void ChargingStation::PopDeadCarrier() {
  if (!deadCarriers.empty()) {
    deadCarriers.erase(deadCarriers.begin());
  }
}

bool ChargingStation::HasDeadCarrier(Carrier* carrier) {
  return (std::find(deadCarriers.begin(), deadCarriers.end(), carrier) != deadCarriers.end());
}

bool ChargingStation::AddChargingDrone(RechargeDrone* chargingDrone) {
  // adds drone to the charging station only if the distance is close together
  if (IsWithin(chargingDrone)) {
    // checks if current drone has already at the charging station
    if (!(std::find(chargingDronesAtStation.begin(), chargingDronesAtStation.end(), chargingDrone) != chargingDronesAtStation.end())) {
      chargingDronesAtStation.push_back(chargingDrone);
    }
    return true;
  }
  return false;
}

void ChargingStation::RemoveChargingDrone(RechargeDrone* chargingDrone) {
  chargingDronesAtStation.erase(std::remove(chargingDronesAtStation.begin(), chargingDronesAtStation.end(), chargingDrone), chargingDronesAtStation.end());
}

void ChargingStation::Update(float dt) {
  // chargingDrone->GetBatteryObj();
  float maxChargeBattery;
  
  for (RechargeDrone* chargingDrone : chargingDronesAtStation) {
    maxChargeBattery = chargingDrone->GetBatteryMaxCharge();
    // std::cout << deadCarriers.size() << std::endl;
    // still has dead carriers
    if (IsWithin(chargingDrone) &&
        (chargingDrone->GetBattery() >= maxChargeBattery * 0.80) &&
        (!chargingDrone->IsDynamic()) &&
        (!deadCarriers.empty())) {
        
      if (deadCarriers[0]->BatteryDead() && !deadCarriers[0]->IsCurrentlyCharging()) {
        // assign chargingDrone to go to deadCarrier
        chargingDrone->SetDeadCarrier(deadCarriers[0]);
        const entity_project::IGraph* graph;
        std::vector<vector<float>> path = chargingDrone->GetRouteStrategy()->GetRoute(graph, chargingDrone->GetPosition(), deadCarriers[0]->GetPosition());
        chargingDrone->SetRoute(path);
        chargingDrone->SetPositionOfStation(GetPosition());
        chargingDrone->GetStatus();
        RemoveChargingDrone(chargingDrone);
      }
      PopDeadCarrier();
    } else if (IsWithin(chargingDrone)) {
      // charges recharging drone if at station
      chargingDrone->ChargeFromStation(dt);
    } else if (!IsWithin(chargingDrone)) {
      // removes recharging drone if out of radius from the charging station
      RemoveChargingDrone(chargingDrone);
    }
  }
}

}  // namespace csci3081
