/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */
class EntityBase : public IEntity {
 public:
  virtual ~EntityBase() {}
  const picojson::object& GetDetails(); 
  /**
    * Return the unique ID of the drone
    * param [out]: ID of the drone
    **/
  int GetId() const;

  /**
    * Return the name of the drone
    * param [out]: name of the drone
    **/
  const std::string& GetName();

  /**
    * Return the position of the drone
    * param [out]: position of the drone as vector of float
    **/
  const std::vector<float>& GetPosition() const;

  /**
    * Return the direction of the drone
    * param [out]: direction of the drone as vector of float
    **/
  const std::vector<float>& GetDirection() const;

  /**
    * Return the radius of the drone
    * param [out]: radius of the drone as vector of float
    **/
  float GetRadius() const;

  /**
    * Return the version of the drone
    * param [out]: version of the drone as vector of float
    **/
  int GetVersion() const;

  /**
    * Return the dynamic of the drone
    * param [out]: dynamic of the drone as vector of float
    **/
  bool IsDynamic() const;

  float DistanceBetween(IEntity* another);

  bool IsWithin(IEntity* another);

  std::string GetType();

 protected:
    std::string name;
    int ID;
    std::vector<float> position;
    std::vector<float> direction;
    bool dynamic;
    int version;
    float radius;
    std::string type;
    picojson::object details;
};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
