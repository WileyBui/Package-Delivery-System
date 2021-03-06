/**
 * @file robot.h
 *
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include <iostream>
#include "battery.h"
#include "package.h"
#include "carrier.h"
#include "vector.h"


namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a robot
 * It stores the robot's name, ID, version, position, direction, speed, and 
 * dynamic mode.
 */
class Robot : public csci3081::Carrier {
  public:
    /**
      * Constructor, creates a Package object
      * param[in] val     a picojson::object object that has the detail of the 
      *                   package including name, position, direction, radius,
      *                   and speed 
    **/
    Robot(const picojson::object& val);

    /**
    * @brief Copy Constructor.
    * This creates a new instance of Package that has the same content
    * as the Package argument
    * @param[in] cpy      Robot instance that wants to be copied
    */
    Robot(Robot&);
    // /**
    // * @brief Destructor.
    // * This destructor is used to delete the routeStrategy pointer attribute when a Robot obj goes out of scope.
    // */
    // ~Robot();
};

}

#endif /* INC_ROBOT_H_ */