#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/package.h"
#include "../include/customer.h"
#include "../include/drone.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class PackageTest : public ::testing::Test {
 protected:
    picojson::object obj = JsonHelper::CreateJsonObject();
    picojson::object obj2 = JsonHelper::CreateJsonObject();
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    std::vector<float> position_to_add2;
    std::vector<float> direction_to_add2;
    float radius = 1.0;
    float speed = 3;
    float duration = 1.56;
 public:
  virtual void SetUp() {
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj2, "type", "package");
    JsonHelper::AddStringToJsonObject(obj2, "type", "drone");
    position_to_add.push_back(100);
    position_to_add.push_back(253.883);
    position_to_add.push_back(431.292);
    position_to_add2.push_back(2253.883);
    position_to_add2.push_back(4938.292);
    position_to_add2.push_back(2533.883);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add2);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    direction_to_add2.push_back(0);
    direction_to_add2.push_back(1);
    direction_to_add2.push_back(0);
    JsonHelper::AddStringToJsonObject(obj3,"name","drone");
    JsonHelper::AddStringToJsonObject(obj2,"name","SHINeeCD");
    JsonHelper::AddStringToJsonObject(obj,"name","Lin");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add2);
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj2, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj3, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj3, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj2, "duration", duration);
    JsonHelper::AddFloatToJsonObject(obj3, "duration", duration);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PackageTest, ConstructorAndGetter) {
  // Normal constructor
  Package SHINeeCD(obj2);
  EXPECT_EQ(SHINeeCD.GetName(),"SHINeeCD") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[0], direction_to_add2[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[1], direction_to_add2[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[2], direction_to_add2[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_EQ(SHINeeCD.GetType(), "package") << "Normal Constructor or GetType does not work";  
  EXPECT_FLOAT_EQ(SHINeeCD.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_EQ(SHINeeCD.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
}

TEST_F(PackageTest, CustomerAdding){
  Customer Lin(obj); 
  Package SHINeeCD(obj2);
  SHINeeCD.SetOwner(&Lin);
  EXPECT_EQ(SHINeeCD.IsDynamic(),false) << "Normal Constructor or IsDynamic does not work";
  EXPECT_TRUE(SHINeeCD.GetOwner()!=NULL) << "Customers are not set";
  EXPECT_EQ(SHINeeCD.GetOwner()->GetId(),Lin.GetId()) << "Customers are not the same";
  EXPECT_FALSE(SHINeeCD.IsDelivered()) << "IsDelivered is faulty";
  EXPECT_EQ(SHINeeCD.GetType(), "package") << "Normal Constructor or GetType does not work";  
}

TEST_F(PackageTest, CopyConstructorAndGetter) {
    Customer Lin(obj);
    Package SHINeeCD(obj2);
    SHINeeCD.SetOwner(&Lin);
    // Copy Constructor
    Package SHINeeCD2(SHINeeCD);
    EXPECT_EQ(SHINeeCD2.GetId(),SHINeeCD.GetId()) << "Copy Constructor or GetId does not work";
    EXPECT_EQ(SHINeeCD2.GetName(),"SHINeeCD") << "Copy Constructor or GetName does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetPosition()[0], position_to_add2[0]) << "Copy Constructor or GetPosition does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetPosition()[1], position_to_add2[1]) << "Copy Constructor or GetPosition does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetPosition()[2], position_to_add2[2]) << "Copy Constructor or GetPosition does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetDirection()[0], direction_to_add2[0]) << "Copy Constructor or GetDirection does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetDirection()[1], direction_to_add2[1]) << "Copy Constructor or GetDirection does not work";    
    EXPECT_FLOAT_EQ(SHINeeCD2.GetDirection()[2], direction_to_add2[2]) << "Copy Constructor or GetDirection does not work";
    EXPECT_FLOAT_EQ(SHINeeCD2.GetRadius(), radius) << "Copy Constructor or GetRadius does not work";
    EXPECT_EQ(SHINeeCD2.GetVersion(),0) << "Copy Constructor or GetVersion does not work";
    EXPECT_EQ(SHINeeCD2.IsDynamic(),false) << "Copy Constructor or IsDynamic does not work";
    EXPECT_EQ(SHINeeCD2.IsDelivered(),SHINeeCD.IsDelivered()) << "IsDelivered is faulty";
    EXPECT_EQ(SHINeeCD.GetOwner()->GetId(),SHINeeCD2.GetOwner()->GetId()) << "Owners for copy constructor are not the same";
}

TEST_F(PackageTest, SettersAndGetters) {
    // Set Destination
    std::vector<float> homie;
    homie.push_back(2912.21);
    homie.push_back(292.21);
    homie.push_back(912.21);
    Package SHINeeCD(obj2);
    Customer Lin(obj);
    SHINeeCD.SetOwner(&Lin);
    EXPECT_EQ(Lin.GetNumPackageTotal(), 1) << "GetNumPackageTotal of Customer is not updated";
    EXPECT_EQ(Lin.GetNumUndeliverPackage(), 1) << "GetNumUndeliverPackage of Customer is not updated";

    // Deliver 
    SHINeeCD.Deliver();
    EXPECT_TRUE(SHINeeCD.IsDelivered()) << "Deliver faulty";
    EXPECT_EQ(Lin.GetNumUndeliverPackage(),0) << "GetNumUndeliverPackage of Customer is not updated";
    EXPECT_EQ(Lin.GetNumDeliverPackage(),1) << "GetNumUndeliverPackage of Customer is not updated";
}

TEST_F(PackageTest, SetPosition){
  Package SHINeeCD(obj2);
  std::vector<float> placeHolder;
	placeHolder.push_back(12.0);
	placeHolder.push_back(15.0);
	placeHolder.push_back(16.0);
  SHINeeCD.SetPosition(placeHolder);
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], placeHolder[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], placeHolder[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], placeHolder[2]) << "Normal Constructor or GetPosition does not work";   
}


TEST_F(PackageTest, CarrierAndUpdate){
  Package SHINeeCD(obj2);
  Drone drone(obj3);
  SHINeeCD.SetCarrier(&drone);
  EXPECT_TRUE(SHINeeCD.GetCarrier()==(&drone)) << "SetCarrier or GetCarrier does not work";
  Customer Lin(obj);
  SHINeeCD.SetOwner(&Lin);
  SHINeeCD.SetDynamic(true);
  EXPECT_TRUE(SHINeeCD.IsDynamic()) << "SetDynamic or IsDynamic does not work";
  SHINeeCD.Update(5);
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Update does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Update does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Update does not work"; 
}

TEST_F(PackageTest, Deliver){
  Package SHINeeCD(obj2);
  Customer Lin(obj);
  SHINeeCD.SetOwner(&Lin);
  SHINeeCD.Deliver();
  std::vector<float> disappear;
  disappear.push_back(0);
  disappear.push_back(-10000);
  disappear.push_back(0);
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], disappear[0]) << "Deliver or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], disappear[1]) << "Deliver Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], disappear[2]) << "Deliver Constructor or GetPosition does not work";   
  EXPECT_TRUE(SHINeeCD.GetCarrier()==NULL) << "Deliver or GetCarrier does not work";
  EXPECT_TRUE(SHINeeCD.IsDelivered()) << "IsDelivered or Deliver does not work";
}

TEST_F(PackageTest, GetStatus){} //since this function relies heavily on Notify (which relies heavily on OnEvent) 
                                  //which is provided for us, we decided that we would not test it

}  // namespace csci3081