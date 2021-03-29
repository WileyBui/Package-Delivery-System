/**
 * @file Package.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include "customer.h"
#include "asubject.h"

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a Package, inherited from EntityBase
 * It stores the Package's name, ID, version, position, direction, and dynamic mode.
 */
class Package : public csci3081::EntityBase, public csci3081::ASubject{
  public:
    /**
      * Constructor, creates a Package object
      * param[in] detail    a picojson::object object that has the detail of the 
      *                   package including name, position, direction, and radius 
    **/
    Package(const picojson::object& detail);
    
    /**
    * @brief Copy Constructor.
    * This creates a new instance of Package that has the same content
    * as the Package argument
    * @param[in] package    Package instance that wants to be copied
    */
    Package(Package& package);

    /**
    * @brief This links a customer object to the package object if the package 
    * has not already had a customer
    * @param[in] o    a Customer pointer
    */
    void SetOwner(Customer*);

    /**
    * @brief This returns a customer object of the package object if there is one, 
    * return NULL otherwise
    */
    Customer* GetOwner();

    /**
    * @brief This function uses to set the new position of the package. However, 
    * package only moves in simulation if its dynamic attribute is set to true
    * @param agr    a std::vector<float> that has the new position of the package
    */    
    void SetPosition(std::vector<float> agr);

    /**
    * @brief This links a carrier Entity object (drone, truck, robot, etc) to 
    * the package object if the package has not already had a one
    * @param[in] o    a IEntity pointer
    */
    void SetCarrier(IEntity*);

    /**
    * @brief This returns the pointer that points to the carrier carrying the 
    * package if there is one; return NULL otherwise
    */
    IEntity* GetCarrier();

    /**
    * @brief This changes the dynamic of the drone. Note that for the drone to
    * move on the simulation, dynamic of the drone must be set to true
    * @param[in]  n     True if the drone is actively moving in the simulation
    *                 False otherwise
    */
    void SetDynamic(bool n);
    
    /**
    * @brief This sets the deliverd attribute of the package to true, signaling 
    * that the package has already been delivered. Change the carrier of the 
    * package to NULL. Change the position of the package to out of the camera 
    * of the simulation to "teleport" out of the scene when delivered.
    */
    void Deliver();
    
    /**
    * @brief This returns a TRUE if the package has been delivered, FALSE otherwise
    */
    bool IsDelivered();
    
    void GetStatus();
    /**
    * @brief This is an inherited method from EntityBase to use for DeliverySimulation.
    * This updates the position of the package on the simulation if the position changes
    * and its dynamic is set to true
    */
    void Update(float dt);

  private: 
    Customer* owner;
    IEntity* carrier;
    bool delivered;
};

}

#endif /* PACKAGE_H_ */