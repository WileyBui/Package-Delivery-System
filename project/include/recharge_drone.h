/**
 * @file recharge_drone.h
 *
 * @copyright Dustin Zhang, All rights reserved.
 */

#ifndef INC_RCGDRONE_H_
#define INC_RCGDRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
//#include <vector>         // Used for vector like vector3D and vector2D
#include <iostream>
#include <string>
#include <vector>  // Used for vector like vector3D and vector2D

#include "battery.h"
#include "carrier.h"
#include "entity_base.h"
#include "package.h"
#include "vector.h"
// #include "route_strategy.h"
#include "beeline_route.h"
#include "parabolic_route.h"
#include "smart_route.h"

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a drone
 * It stores the drone's name, ID, version, position, direction, speed, and 
 * dynamic mode.
 */
class RechargeDrone : public csci3081::EntityBase, public csci3081::ASubject {
 public:
  /**
    * Constructor, creates a recharing drone object
    * param[in] val    a picojson::object object that has the detail of the 
    *                   package including name, position, direction, radius,
    *                   and speed 
  **/
  RechargeDrone(const picojson::object& val);

  /**
    * @brief Copy Constructor.
    * This creates a new instance of recharing drone that has the same content
    * as the Package argument
    * @param[in] cpy    Drone instance that wants to be copied
    */
  RechargeDrone(RechargeDrone&);
  /**
    * @brief This function will charge the recharging drone at the station when there is no
    * DeadCarrier
    * @param[in] t time that charge the recharging drone
    */

  bool IsCurrentlyCharging();

  void ChargeFromStation(float dt);

  /**
    * @brief This function will charge the DeadCarrier if the DeadCarrier is not charged to full. After
    * the DeadCarrier get charged to full it will set the DeadCarrier Charging Status to false so the simulation will know
    * the DeadCarrier is ready to be schduled 
    * @param[in] t time that charge the recharging drone
    * @return this function will return true when the DeadCarrier get charged to full
    */
  bool IsChargingCarrierFull(float dt);

  /**
    * @brief This checks if the recharging drone is out of battery
    * @return TRUE if the battery of the carrier is out 
    *         FALSE otherwise
    */
    bool BatteryDead();

  /**
    * @brief This returns the time in secs left in the carrier's battery
    */
    float GetBattery();


  /**
    * @brief This returns the max charge of the recharge drone's battery.
    */
    float GetBatteryMaxCharge();

  /**
    * @brief This function is used to charge the battery of the carrier for 
    * a certain amount of time in seconds
    * @param[in] sec  amount of time in secs to charge the battery
    * @return TRUE if the battery can be charged
    *         FALSE otherwise
    */
    bool Charging(float);

     /**
    * @brief This sets the speed of the carrier. Change the speed of the carrier
    * if the argument is a non-negative float number
    * @param[in] s    a non-negative float value for the carrier's speed
    */
    void SetSpeed(float);

    /**
    * @brief return the current speed of the carrier
    */
    float GetSpeed();
    
    /**
    * @brief This function uses to set the new position of the carrier. However, 
    * carrier only moves in simulation if its dynamic attribute is set to true
    * @param agr    a std::vector<float> that has the new position of the carrier
    */  
    void SetPosition(std::vector<float> v);

    /**
    * @brief This changes the dynamic of the recharge drone. Note that for the recharge drone to
    * move on the simulation, dynamic of the recharge drone must be set to true
    * @param[in]  n     True if the recharge drone is actively moving in the simulation
    *                 False otherwise
    */
    void SetDynamic(bool dynamic_);

    /**
    * @brief This function adds a full route to route attribute of the carrier 
    * This is useful when use for the GetPath() function from IGraph class
    * @param agr    a std::vector<std::vector<float>> that has the positions need to be added
    */ 
    void SetRoute(std::vector<vector<float>>); 

    /**
    * @brief This function returns the next position in std::vector<float> in 
    * the queue that the carrier needs to move to
    */
    std::vector<float> NextPosition();

    /**
    * @brief This function pops the first element/position in the position 
    * queue of the carrier
    */
    void PopPosition();

    /**
    * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
    * This updates the position of the carrier on the simulation if the position changes
    * and its dynamic is set to true. In addition, this function also checks if the
    * carrier is in within distance with the package to pick it up, or within distance
    * with the customer to drop off the package
    */
    void Update(float dt);

    /**
    * @brief Overwritten GetStatus from ASubject. This function creates the arguments 
    * required by Notify function and makes call to Notify function. This function should
    * be called when path is added to the carrier and when the carrier becomes idle
    * @param picojson::value& event 
    * @param const entity_project::IEntity& entity
    */
    void GetStatus();

    /**
    * @brief This function set the DeadCarrier Pointer to a new carrier.
    * @param[in] carrier a carrier pointer that needed to be charged by recharging drone 
    */
    void SetDeadCarrier(Carrier* carrier);
    /**
    * @brief This function set the DeadCarrier Pointer to a new carrier.
    * @return return the DeadCarrier NULL for nothing
    */
    Carrier* GetDeadCarrier();
    /**
    * @brief This function set the position of the station(SetPositionOfStation)
    *  to a new position
    * @param[in] pos the new position of the Station
    */
    void SetPositionOfStation(vector<float> station);
     /**
    * @brief This function Get the position of the station(SetPositionOfStation)
    * @return return the SetPositionOfStation(NULL for nothing)
    */
    vector<float> GetPositionOfStation();
    /**
    * @brief This function should check the DeadCarrier pointer if its null or not and check if the DeadCarrier is getting charged or not.
    * This function should be called in the simulation that to check the status of the recharging_drone. If its charing a DeadCarrier then 
    * does not need to Update the recharging drone.
    * @return the boolean value that indicates reacharging drone is charging a DeadCarrier or not.
    */
    bool IsChargingACarrier();

    /**
    * @brief return the Route Strategy that the carrier uses, such as Smart Route, Beeline, 
    * or Parabolic Route
    * @return RouteStrategy pointer
    */
    RouteStrategy* GetRouteStrategy();
     /**
    * @brief This function checks the battery Capacity to see if it's full or not. This function should be called in 
    * IsChargingCarrierFull() to check if the DeadDrone need to be charged more.
    * @return the boolean value that indicates ss the battery full or not
    */
    bool BatteryFull();
  private:
    Battery battery;
    float speed;
    bool alreadyNotified = false;
    bool isCurrentlyCharging = false;
    std::vector<std::vector<float>> route;
    RouteStrategy* routeStrategy = NULL;
    std::vector<float> PositionOfStation;
    Carrier* DeadCarrier = NULL;

};

}  // namespace csci3081

#endif /* INC_RCGDRONE_H_ */