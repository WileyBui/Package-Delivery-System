/**
 * @file charging_station.h
 */

#ifndef CHARGING_STATION_H
#define CHARGING_STATION_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include <recharge_drone.h>
#include <carrier.h>
#include <vector.h>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a ChargingStation, inherited from EntityBase
 * It stores the ChargingStation's name, ID, version, position, direction, and dynamic mode.
 */
class ChargingStation : public csci3081::EntityBase {
  public:
    /**
      * Constructor
      * param[in] val: the json object of the ChargingStation
    **/
    ChargingStation(const picojson::object& val);
    
    /**
    * @brief Copy Constructor.
    * This creates a new instance of ChargingStation that has the same content
    * as the chargingStation argument
    * @param[in] chargingStation    chargingStation instance that wants to be copied
    */
    ChargingStation(ChargingStation& chargingStation);

    /**
    * @brief This adds a new dead carrier to a deadCarriers vector.
    * @param[in] carrier  A new carrier to be added to deadCarriers vector.
    */
    void AddDeadCarrier(Carrier* carrier);
    
    /**
    * @brief This removes the first dead carrier from a deadCarriers vector.
    * This is due to a recharging drone that is heading towards a dead carrier
    * to charge its battery.
    */
    void PopDeadCarrier();

    /**
    * @brief This function checks if the charging station has already stored the dead carrier.
    * @param[in]  carrier   Dead carrier to be checked if noted in the charging station
    * @return     bool      True if the charging station has already stored the dead carrier.
    *                       False otherwise.
    */
    bool HasDeadCarrier(Carrier* carrier);

    /**
    * @brief This adds a unique charging drone to the charging station only if the distance
    * between the two is close together.
    * @param[in]  chargingDrone A charging drone to be added to the charging station.
    * @returns    bool          Returns true if the charging drone was successfully added.
    *                           False otherwise.
    */
    bool AddChargingDrone(RechargeDrone* chargingDrone);

    /**
    * @brief This removes a charging drone from the charging station. This is due to 
    * a charging drone leaving the station to charge for a dead carrier.
    * @param[in] chargingDrone A charging drone to be removed from the charging station.
    */
    void RemoveChargingDrone(RechargeDrone* chargingDrone);

    /**
    * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
    * This updates the position of the carrier on the simulation if the position changes
    * and its dynamic is set to true. In addition, this function also checks if the
    * carrier is in within distance with the package to pick it up, or within distance
    * with the customer to drop off the package
    */
    void Update(float dt);
    
  private: 
    std::vector<RechargeDrone*> chargingDrones;
    std::vector<Carrier*> deadCarriers;
};

}

#endif /* INC_CHARGING_STATION_H */