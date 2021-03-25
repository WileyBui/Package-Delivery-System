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
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include <iostream>
#include "battery.h"
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
class Drone : public csci3081::EntityBase {
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
    * @brief This links a package object to the drone if the drone is not  
    * already linking to another package (drone can only carry one package
    * at a time)
    * @param[in] arg    a Package pointer
    * @return True upon succeeding linking the package to the drone
    *         False otherwise (e.g. drone is already linked to another package)
    */
    bool AddPackage(Package* arg);

    /**
    * @brief This checks if the drone is already linked to a package
    * @return True if the drone is already linked to a package 
    *                     (package pointer of the drone is not NULL)
    *         False otherwise
    */
    bool HavePackage();

    /**
    * @brief This releases the link of the package from the drone, making the
    * package pointer of the drone NULL, and return a pointer to the just 
    * dropped/delivered package
    * @return a Package pointer to the just dropped/delivered package
    */
    Package* DropPackage();
    
    /**
    * @brief This returns a Package pointer to the package that the drone is
    * linking to, and returns NULL if the drone is not linking to any package. 
    */
    Package* GetPackage();

    /**
    * @brief This checks if the drone is out of battery
    * @return TRUE if the battery of the drone is out 
    *         FALSE otherwise
    */
    bool BatteryDead();

    /**
    * @brief This function is used to charge the battery of the drone for 
    * a certain amount of time in seconds
    * @param[in] sec  amount of time in secs to charge the battery
    * @return TRUE if the battery can be charged
    *         FALSE otherwise
    */
    bool Charging(float);

    /**
    * @brief This sets the speed of the drone. Change the speed of the drone
    * if the argument is a non-negative float number
    * @param[in] s    a non-negative float value for the drone's speed
    */
    void SetSpeed(float);

    /**
    * @brief return the current speed of the drone
    */
    float GetSpeed();
    
    /**
    * @brief This function uses to set the new position of the drone. However, 
    * drone only moves in simulation if its dynamic attribute is set to true
    * @param agr    a std::vector<float> that has the new position of the drone
    */  
    void SetPosition(std::vector<float> v);

    /**
    * @brief This function adds a position to the drone queue of position need 
    * to move to. This is useful when use for the GetPath() function from 
    * IGraph class
    * @param agr    a std::vector<float> that has the position need to be added
    */ 
    void AddPosition(std::vector<float>); 

    /**
    * @brief This function returns the next position in std::vector<float> in 
    * the queue that the drone needs to move to
    */
    std::vector<float> NextPosition();

    /**
    * @brief This function pops the first element/position in the position 
    * queue of the drone
    */
    void PopPosition();

    /**
    * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
    * This updates the position of the drone on the simulation if the position changes
    * and its dynamic is set to true. In addition, this function also checks if the
    * drone is in within distance with the package to pick it up, or within distance
    * with the customer to drop off the package
    */
    void Update(float dt);
  private: 
    Battery battery;
    Package* package;
    float speed;
    std::vector<std::vector<float>> route;
};

}

#endif /* INC_DRONE_H_ */