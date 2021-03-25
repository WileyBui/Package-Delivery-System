#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/customer.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class CustomerTest : public ::testing::Test {
 protected:
    picojson::object obj = JsonHelper::CreateJsonObject();
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    float radius = 1.0;
 public:
  virtual void SetUp() {
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(253.883);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStringToJsonObject(obj,"name","Lin");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(CustomerTest, ConstructorAndGetter) {
  // Normal constructor
  Customer Lin(obj);
  EXPECT_EQ(Lin.GetName(),"Lin") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(Lin.GetPosition()[0], position_to_add[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin.GetPosition()[1], position_to_add[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin.GetPosition()[2], position_to_add[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin.GetDirection()[0], direction_to_add[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin.GetDirection()[1], direction_to_add[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin.GetDirection()[2], direction_to_add[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_EQ(Lin.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_EQ(Lin.IsDynamic(),false) << "Normal Constructor or IsDynamic does not work";
  EXPECT_EQ(Lin.GetType(), "customer") << "Normal Constructor or GetType does not work";


  // Copy Constructor
  Customer Lin2(Lin);
  EXPECT_EQ(Lin2.GetId(),Lin.GetId()) << "Copy Constructor or GetId does not work";
  EXPECT_EQ(Lin2.GetName(),"Lin") << "Copy Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(Lin2.GetPosition()[0], position_to_add[0]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin2.GetPosition()[1], position_to_add[1]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin2.GetPosition()[2], position_to_add[2]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(Lin2.GetDirection()[0], direction_to_add[0]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin2.GetDirection()[1], direction_to_add[1]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin2.GetDirection()[2], direction_to_add[2]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(Lin2.GetRadius(), radius) << "Copy Constructor or GetRadius does not work";
  EXPECT_EQ(Lin2.GetType(), "customer") << "Normal Constructor or GetType does not work";
  EXPECT_EQ(Lin2.GetVersion(),0) << "Copy Constructor or GetVersion does not work";
  EXPECT_EQ(Lin2.IsDynamic(),false) << "Copy Constructor or IsDynamic does not work";
}

TEST_F(CustomerTest, PackageMethods) {
  Customer Lin(obj);
  EXPECT_EQ(Lin.GetNumPackageTotal(),0) << "GetNumPackageTotal is faulty";
  EXPECT_EQ(Lin.GetNumDeliverPackage(),0) << "GetNumDeliverPackage is faulty";
  EXPECT_EQ(Lin.GetNumUndeliverPackage(),0) << "GetNumUndeliverPackage is faulty";
  std::vector<int> packageID;
  packageID.push_back(1);
  packageID.push_back(2);
  packageID.push_back(3);
  for (int i=0; i<3; i++){
    Lin.AddPackage(i+1);
    EXPECT_EQ(Lin.GetNumPackageTotal(),i+1) << "GetNumPackageTotal is faulty";
    EXPECT_EQ(Lin.GetNumUndeliverPackage(),i+1) << "GetNumUndeliverPackage is faulty";
  }
  Lin.PackageDeliver(3);
  EXPECT_EQ(Lin.GetNumPackageTotal(),3) << "GetNumPackageTotal is faulty";
  EXPECT_EQ(Lin.GetNumUndeliverPackage(),2) << "GetNumUndeliverPackage is faulty";
  EXPECT_EQ(Lin.GetNumDeliverPackage(),1) << "GetNumDeliverPackage is faulty";
}


}  // namespace csci3081