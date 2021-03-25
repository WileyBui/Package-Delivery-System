/**
 * @file Customer.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A representation of a Customer, inherited from EntityBase
 * It stores the Customer's name, ID, version, position, direction, and dynamic mode.
 */
class Customer : public csci3081::EntityBase {
  public:
    /**
      * Constructor
      * param[in] val: the json object of the Customer
    **/
    Customer(const picojson::object& val);
    
    /**
    * @brief Copy Constructor.
    * This creates a new instance of Customer that has the same content
    * as the Customer argument
    * @param[in] customer    Customer instance that wants to be copied
    */
    Customer(Customer& customer);

    /**
    * @brief This return the number of packages the customer has in total
    */
    int GetNumPackageTotal() const;

    /**
    * @brief This return the number of packages the customer has in total
    */
    int GetNumDeliverPackage() const;

    /**
    * @brief This adds a package ID into the customer's tracked packageID vector
    * if the package has not already been added. This would help check package
    * delivery for the customer
    * @param[in] packageID    the int for the ID of the package
    */
    void AddPackage(int packageID);

    /**
    * @brief This returns TRUE if the package with the ID passed in has already 
    * been delivered; FALSE otherwise
    * @param[in] packageID    the int for the ID of the package
    */
    bool PackageDeliver(int packageID);

    /**
    * @brief This return the number of undelivered packages the customer has
    */
    int GetNumUndeliverPackage() const;

    /**
    * @brief Empty function Update. Have to be here because Update(float) in
    * EntityBase is pure virtual
    * @param[in] dt    time in float
    */
    void Update(float dt);

  private: 
    std::vector<int> packageIDVector;     
    std::vector<bool> deliveredPackage;
    int numPackageTotal;
    int numDeliveredPackage;
};

}

#endif /* INC_Customer_H_ */