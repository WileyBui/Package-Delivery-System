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
#include <iostream>
#include <string>
#include <vector>  // Used for vector like vector3D and vector2D

#include "battery.h"
#include "carrier.h"
#include "entity_base.h"
#include "package.h"
#include "vector.h"

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
  // class Drone : public csci3081::Carrier{

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

  /**
    * @brief Gets the beeline path (go up a certain height and fly horizontally across to the destination)
    * This method gets the beeline path, which includes a point where the drone needs to go up to
    * by a certain height from where it is at, then another point to the destination location with the
    * same certain height, then another point to the final destination location.
    * @param[in] src    Current drone location
    * @param[in] dest   Final location where the drone needs to be
    * 
    * @return           The path of the beeline
    */
  vector<vector<float>> GetBeelinePath(std::vector<float> src, std::vector<float> dest);
};

}  // namespace csci3081

#endif /* INC_DRONE_H_ */