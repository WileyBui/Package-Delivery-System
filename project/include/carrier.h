/**
 * @file carrier.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef INC_CARRIER_H_
#define INC_CARRIER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include <iostream>
#include "battery.h"
#include "package.h"
#include "asubject.h"

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a carrier
 * An abstract base class for delivery transportation clases like Drone or Robot.
 * Robot and Drone inherited from Carrier
 */
class Carrier : public csci3081::EntityBase, public csci3081::ASubject {
  public:
    /**
    * @brief This links a package object to the carrier if the carrier is not  
    * already linking to another package (carrier can only carry one package
    * at a time)
    * @param[in] arg    a Package pointer
    * @return True upon succeeding linking the package to the carrier
    *         False otherwise (e.g. carrier is already linked to another package)
    */
    bool AddPackage(Package* arg);

    /**
    * @brief This checks if the carrier is already linked to a package
    * @return True if the carrier is already linked to a package 
    *                     (package pointer of the carrier is not NULL)
    *         False otherwise
    */
    bool HavePackage();

    /**
    * @brief This releases the link of the package from the carrier, making the
    * package pointer of the carrier NULL, and return a pointer to the just 
    * dropped/delivered package
    * @return a Package pointer to the just dropped/delivered package
    */
    Package* DropPackage();
    
    /**
    * @brief This returns a Package pointer to the package that the carrier is
    * linking to, and returns NULL if the carrier is not linking to any package. 
    */
    Package* GetPackage();

    /**
    * @brief This checks if the carrier is out of battery
    * @return TRUE if the battery of the carrier is out 
    *         FALSE otherwise
    */
    bool BatteryDead();

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
    * @brief This returns the time in secs left in the carrier's battery
    */
    float GetBattery();

    void GetStatus();

  protected: 
    Battery battery;
    Package* package;
    float speed;
    std::vector<std::vector<float>> route;
};

}

#endif /* INC_CARRIER_H_ */