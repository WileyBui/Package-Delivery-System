#include "../include/entity_base.h"
#include "../include/generate_id.h"
#include "json_helper.h"
#include <EntityProject/entity.h>
#include "../include/vector.h"
#include "../include/customer.h"

namespace csci3081 {
Customer::Customer(const picojson::object& val) {
  position = JsonHelper::GetStdFloatVector(val, "position");
  direction = JsonHelper::GetStdFloatVector(val, "direction");
  name = JsonHelper::GetString(val, "name");
  radius = radius = JsonHelper::GetDouble(val, "radius");
  dynamic = false;
  version = 0;
  ID = GenerateId::GenerateNewId();
  details = val;
  numPackageTotal = 0;
  numDeliveredPackage = 0;
  type = "customer";
}

Customer::Customer(Customer& customer){
  for (int i = 0; i<customer.GetPosition().size(); i++) {
    this->position.push_back(customer.GetPosition()[i]);
  }
  for (int i = 0; i<customer.GetDirection().size(); i++) {
    this->direction.push_back(customer.GetDirection()[i]);
  }
  name = customer.GetName();
  radius = customer.GetRadius();
  dynamic = customer.IsDynamic();
  version = customer.GetVersion();
  ID = customer.GetId();
  details = customer.GetDetails();
  numPackageTotal = customer.GetNumPackageTotal();
  numDeliveredPackage = customer.GetNumDeliverPackage();
  type = "customer";
}

void Customer::AddPackage(int packageID) {
    packageIDVector.push_back(packageID);
    deliveredPackage.push_back(false);
    numPackageTotal++;
}

int Customer::GetNumPackageTotal() const {
    return numPackageTotal;
}

int Customer::GetNumDeliverPackage() const{
    return numDeliveredPackage;
}

int Customer::GetNumUndeliverPackage() const {
    return numPackageTotal-numDeliveredPackage;
}

bool Customer::PackageDeliver(int packageID){
  for (int i = 0; i<numPackageTotal; i++) {
      if (packageID == packageIDVector.at(i)) {
          deliveredPackage.at(i) = true;
          numDeliveredPackage++;
          break;
      }
  }
  return false;
}

}