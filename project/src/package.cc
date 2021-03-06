#include "../include/entity_base.h"
#include "../include/generate_id.h"
#include "json_helper.h"
#include <EntityProject/entity.h>
#include "../include/vector.h"
#include "../include/package.h"

namespace csci3081 {
Package::Package(const picojson::object& detail) {
  position = JsonHelper::GetStdFloatVector(detail, "position");
  direction = JsonHelper::GetStdFloatVector(detail, "direction");
  name = JsonHelper::GetString(detail, "name");
  radius = JsonHelper::GetDouble(detail, "radius");
  dynamic = false;
  version = 0;
  ID = GenerateId::GenerateNewId();
  details = detail;
  owner = NULL;
  carrier = NULL;
  delivered = false;
  type = "package";
}

Package::Package(Package& package){
  this->position = package.GetPosition();
  this->direction = package.GetDirection();
  name = package.GetName();
  radius = package.GetRadius();
  dynamic = package.IsDynamic();
  version = package.GetVersion();
  ID = package.GetId();
  details = package.GetDetails();
  owner = package.owner;
  carrier = package.carrier;
  delivered = package.delivered;
  type = "package";
}

void Package::SetOwner(Customer* o){
  owner = o;
  owner->AddPackage(ID);
}

bool Package::IsDelivered(){
  return delivered;
}

void Package::Deliver(){
  // Set position out of the camera
  std::vector<float> disappear;
  disappear.push_back(0);
  disappear.push_back(-10000);
  disappear.push_back(0);
  delivered = true;
  carrier = NULL;
  GetStatus();
  owner->PackageDeliver(ID);
  SetPosition(disappear);
}

void Package::SetDynamic(bool n){
  dynamic = n;
}

Customer* Package::GetOwner(){
    return owner;
}

void Package::SetPosition(std::vector<float> agr){
  position.clear();
  for (int i = 0; i<agr.size(); i++) {
    this->position.push_back(agr.at(i));
  }  
}

void Package::SetCarrier(IEntity* ve){
  carrier = ve;
}

IEntity* Package::GetCarrier(){
  return carrier;
}

void Package::GetStatus() {
  picojson::object notification_builder = JsonHelper::CreateJsonNotification();
  if (carrier != NULL){
    if (IsDynamic()){
      JsonHelper::AddStringToJsonObject(notification_builder,"value","en route");
    }
    else{
      JsonHelper::AddStringToJsonObject(notification_builder,"value","scheduled");
    }
    picojson::value notification_to_send = JsonHelper::ConvertPicojsonObjectToValue(notification_builder);
    Notify(notification_to_send,*this);
  }
  else if (delivered == true){
    JsonHelper::AddStringToJsonObject(notification_builder,"value","delivered");
    picojson::value notification_to_send = JsonHelper::ConvertPicojsonObjectToValue(notification_builder);
    Notify(notification_to_send,*this);
  }
}

void Package::Update(float dt){
  if ((delivered==false) && (owner!=NULL) && (IsDynamic()) && (GetCarrier()!=NULL)) {
        SetPosition(carrier->GetPosition());
  }
}

}