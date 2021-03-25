#include "../include/entity_base.h"
#include "../include/vector.h"

namespace csci3081 {

int EntityBase::GetId() const {
    return ID;
}

const picojson::object& EntityBase::GetDetails() { 
    return details; 
}

const std::string& EntityBase::GetName() {
    return name;
}

const std::vector<float>& EntityBase::GetPosition() const {
    return position;
}

const std::vector<float>& EntityBase::GetDirection() const {
    return direction;
} 

float EntityBase::GetRadius() const {
    return radius;
}

int EntityBase::GetVersion() const {
    return version;
}

bool EntityBase::IsDynamic() const {
    return dynamic;
}

float EntityBase::DistanceBetween(IEntity* another){
  Vector3D oneThing(position);
  Vector3D vec(another->GetPosition());
  return Distance(oneThing,vec);
}

bool EntityBase::IsWithin(IEntity* another){
  if (DistanceBetween(another)<radius+another->GetRadius()){
    return true;
  }
  return false;
}
}