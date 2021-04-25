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
#include <drone.h>
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
    * @brief This charges the drone. If the battery of the drone reaches its max
    * capacity, it will not charge anymore.
    */
    bool IsDroneWithinRadius(Drone* currentDrone, float radius);

    /**
    * @brief This charges the drone. If the battery of the drone reaches its max
    * capacity, it will not charge anymore.
    */
    bool AddDrone(Drone* currentDrone);

    /**
    * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
    * This updates the position of the carrier on the simulation if the position changes
    * and its dynamic is set to true. In addition, this function also checks if the
    * carrier is in within distance with the package to pick it up, or within distance
    * with the customer to drop off the package
    */
    void Update(float dt);
  private: 
    std::vector<Drone*> dronesAtStation;
};

}

#endif /* INC_CHARGING_STATION_H */