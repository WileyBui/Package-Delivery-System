/**
 * @file carrier_factory.h
 */
#ifndef CARRIER_FACTORY_H
#define CARRIER_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include "drone_factory.h"
#include <vector>
#include <string>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is a derived class from IEntityFactory to manage all other factories
 * (e.g. DroneFactory, PackageFactory, CustomerFactory...)
 *
 */
class CarrierFactory : public IEntityFactory {
 public:
  /**
   * @brief Constructor: this can do any setup your system necessitates.
   */
  CarrierFactory();

  /**
  * @brief Destructor: this tear down/reset the memory space related to pointers
  */
  ~CarrierFactory();

  /**
  * @brief This adds an IEntityFactory factory into the vector factories of
  * carrier class
  * @param[in] n a IEntityFactory pointer that want to be added into the vector
  */
  void AddFactory(IEntityFactory*);

  /**
  * @brief This is an inheritance function from IEntityFactory to create 
  * an approxiate Entity object based on the argument pass in 
  * Given the picojson::object val, this should create an entity.
  * Based on the type of entity, there may be different fields.
  * You can see the vals that will be passed in the project/web/scenes
  * directory. Some of the fields are for our backend system and you don't
  * need to worry about them. (for instance, mesh, rotation, offset, etc.)
  Some fields in val that you will need to create the entity correctly:

    type: string (could be "drone/customer/package")

    name: string

    position: array (contains [x_position, y_position, z_position])

    direction: array (contains [x, y, z])

    speed: float

    battery_capacity: float
  * @param[in] val the picojson::object that constains all of the necessary
  * @return IEntity pointer
  * information above in a json format
  */
  IEntity* CreateEntity(const picojson::object& val);

 private:
  std::vector<IEntityFactory*> carrierFactories; 
};

}  // namespace csci3081


#endif  // CARRIER_FACTORY_H
