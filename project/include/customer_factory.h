/**
 * @file composite_factory.h
 */
#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the CustomerFactory, responsible for making Customer object
 */

// DO NOT MODIFY (unless you really know what you are doing)
class CustomerFactory : public IEntityFactory {
 public:
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

  * @param[in] val the picojson::object that constains all of the necessary
  *                 information above in a json format
  * @return IEntity pointer if the object has type "customer"; NULL otherwise
  */
  IEntity* CreateEntity(const picojson::object& val);
};

}  // namespace csci3081


#endif  // CUSTOMER_FACTORY_H
