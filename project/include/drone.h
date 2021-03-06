/**
 * @file drone.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef INC_DRONE_H_
#define INC_DRONE_H_

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
class Drone : public csci3081::Carrier {
 public:
  /**
    * Constructor, creates a Package object
    * param[in] val    a picojson::object object that has the detail of the 
    *                   package including name, position, direction, radius,
    *                   and speed 
  **/
  Drone(const picojson::object& val);

  /**
    * @brief Copy Constructor.
    * This creates a new instance of Package that has the same content
    * as the Package argument
    * @param[in] cpy    Drone instance that wants to be copied
    */
  Drone(Drone&);

  // /**
  // * @brief Destructor.
  // * This destructor is used to delete the routeStrategy pointer attribute when a Drone obj goes out of scope.
  // */
  // ~Drone();
  // /**
  // * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
  // * This updates the position of the drone on the simulation if the position changes
  // * and its dynamic is set to true. In addition, this function also checks if the
  // * drone is in within distance with the package to pick it up, or within distance
  // * with the customer to drop off the package
  // */
  // void Update(float dt);
};

}  // namespace csci3081

#endif /* INC_DRONE_H_ */