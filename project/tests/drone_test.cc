#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/package.h"
#include "../include/drone.h"
#include "../include/customer.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class DroneTest : public ::testing::Test {
 protected:
    picojson::object obj = JsonHelper::CreateJsonObject();
    picojson::object obj2 = JsonHelper::CreateJsonObject();
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    std::vector<float> position_to_add2;
    std::vector<float> direction_to_add2;
    float radius = 1.0;
    float speed = 3.0;
    float battery_capacity = 1.56;
 public:
  virtual void SetUp() {
    JsonHelper::AddStringToJsonObject(obj, "type", "Drone");
    position_to_add.push_back(100);
    position_to_add.push_back(253.883);
    position_to_add.push_back(431.292);
    position_to_add2.push_back(2253.883);
    position_to_add2.push_back(4938.292);
    position_to_add2.push_back(2533.883);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    direction_to_add2.push_back(0);
    direction_to_add2.push_back(1);
    direction_to_add2.push_back(0);
    JsonHelper::AddStringToJsonObject(obj2,"name","SHINeeCD");
    JsonHelper::AddStringToJsonObject(obj,"name","Lin");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj2, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj2, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj2, "battery_capacity", battery_capacity);
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", battery_capacity);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(DroneTest, ConstructorAndGetter) {
  // Normal constructor
  // Customer Lin("Lin",position_to_add,direction_to_add,radius,obj);
  Drone SHINeeCD(obj2);
  EXPECT_EQ(SHINeeCD.GetName(),"SHINeeCD") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[0], direction_to_add2[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[1], direction_to_add2[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[2], direction_to_add2[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_EQ(SHINeeCD.GetType(), "carrier") << "Normal Constructor or GetType does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(), speed) << "Normal Constructor or GetSpeed does not work";
  EXPECT_EQ(SHINeeCD.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_FALSE(SHINeeCD.IsDynamic()) << "Normal Constructor or IsDynamic does not work";
  EXPECT_TRUE(SHINeeCD.GetPackage()==NULL) <<"Normal Constructor or GetPackageID does not work";
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "Normal Constructor or BatteryDead does not work";
  EXPECT_FALSE(SHINeeCD.HavePackage()) << "Normal Constructor or HavePackage does not work";
  EXPECT_TRUE(SHINeeCD.Charging(1000)) << "Normal Constructor or Charging does not work";
  EXPECT_TRUE(SHINeeCD.DropPackage()==NULL) << "Normal Constructor or BatteryDead does not work";
}

TEST_F(DroneTest, CopyConstructorAndGetter) {
  // Normal constructor
  Drone SHINeeCD2(obj2);
  Drone SHINeeCD(SHINeeCD2);
  EXPECT_EQ(SHINeeCD.GetName(),"SHINeeCD") << "Copy Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[0], direction_to_add2[0]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[1], direction_to_add2[1]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[2], direction_to_add2[2]) << "Copy Constructor or GetDirection does not work";
  EXPECT_EQ(SHINeeCD.GetType(), "carrier") << "Normal Constructor or GetType does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetRadius(), radius) << "Copy Constructor or GetRadius does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(), speed) << "Copy Constructor or GetSpeed does not work";
  EXPECT_EQ(SHINeeCD.GetVersion(),0) << "Copy Constructor or GetVersion does not work";
  EXPECT_FALSE(SHINeeCD.IsDynamic()) << "Copy Constructor or IsDynamic does not work";
  EXPECT_TRUE(SHINeeCD.GetPackage()==NULL) <<"Copy Constructor or GetPackageID does not work";
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "Copy Constructor or BatteryDead does not work";
  EXPECT_FALSE(SHINeeCD.HavePackage()) << "Copy Constructor or HavePackage does not work";
  EXPECT_FALSE(SHINeeCD.Charging(-1000)) << "Copy Constructor or Charging does not work";
  EXPECT_TRUE(SHINeeCD.DropPackage()==NULL) << "Copy Constructor or BatteryDead does not work";
}

TEST_F(DroneTest, AddingPackage){
  Customer Lin(obj); 
  Drone SM(obj2);
  Package SHINeeCD(obj2);
  EXPECT_FLOAT_EQ(SM.DistanceBetween(&SHINeeCD), 0) << "DistanceBetween does not work";
  EXPECT_FLOAT_EQ(SM.DistanceBetween(&Lin), 5568.104575) << "DistanceBetween does not work";

  SHINeeCD.SetOwner(&Lin);

  EXPECT_TRUE(SM.AddPackage(&SHINeeCD)) << "Add AddPackage does not work";  
  EXPECT_EQ(SM.GetPackage()->GetId(),SHINeeCD.GetId()) << "GetPackageID does not work";
  EXPECT_TRUE(SM.HavePackage()) << "Add HavePackage does not work";  
  
  // Add another package
  Package SummerPackage(obj2);
  EXPECT_FALSE(SM.AddPackage(&SummerPackage)) << "Add HavePackage does not work";  
  SM.DropPackage();
  EXPECT_TRUE(SM.AddPackage(&SummerPackage)) << "Add HavePackage does not work";  
}
 
TEST_F(DroneTest, Route) {
    // SetPosition
    srand(0);
    std::vector<float> homie;
    std::vector<std::vector<float>> path;
    Drone SHINeeCD(obj2);
    homie.push_back(1);
    homie.push_back(2);
    homie.push_back(3);
    for (int j = 0; j<9; j++){
      for (int i = 0; i<3; i++){
        homie.at(i) = rand()%100;
      }
      path.push_back(homie);
      SHINeeCD.SetPosition(homie);
      EXPECT_TRUE(SHINeeCD.IsDynamic()) << "SetPosition does not work";
    }

    int j = 0;
    for (int i = 0; i<9; i++){
      std::vector<float> placeHolder = SHINeeCD.NextPosition();
      EXPECT_FLOAT_EQ(placeHolder[0], path[j][0]) << "NextPosition does not work";
      EXPECT_FLOAT_EQ(placeHolder[1], path[j][1]) << "NextPosition does not work";
      EXPECT_FLOAT_EQ(placeHolder[2], path[j][2]) << "NextPosition does not work";
      SHINeeCD.PopPosition();
      j++;
    }
    EXPECT_FALSE(SHINeeCD.IsDynamic()) << "SetPosition does not work";
}

TEST_F(DroneTest, IsWithin){
  Customer Lin(obj); 
  Drone SM(obj2);
  Package SHINeeCD(obj2);
  EXPECT_FALSE(SM.IsWithin(&Lin));
  EXPECT_TRUE(SM.IsWithin(&SHINeeCD));  
}

TEST_F(DroneTest, SetPosition){
  Drone SHINeeCD(obj2);
  std::vector<float> placeHolder;
	placeHolder.push_back(12.0);
	placeHolder.push_back(15.0);
	placeHolder.push_back(16.0);
  SHINeeCD.SetPosition(placeHolder);
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], placeHolder[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], placeHolder[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], placeHolder[2]) << "Normal Constructor or GetPosition does not work";   
}

TEST_F(DroneTest, UpdateAndBattery){
  Drone SHINeeCD(obj2);
  Customer Lin(obj2); 
  SHINeeCD.SetSpeed(0.0000000000001);
  SHINeeCD.Update(10);
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
  Package SM(obj);
  SM.SetOwner(&Lin);
  EXPECT_TRUE(SHINeeCD.AddPackage(&SM)) << "AddPackage faulty";
  EXPECT_TRUE(SHINeeCD.HavePackage()) << "AddPackage faulty";
  SHINeeCD.Update(10000);
  EXPECT_TRUE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
  SHINeeCD.DropPackage();
  SHINeeCD.Update(10000);
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
}


TEST_F(DroneTest, SetSpeed){
  Drone SHINeeCD(obj2);
  SHINeeCD.SetSpeed(2.4);
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
  SHINeeCD.SetSpeed(-10.5);
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
}

}  // namespace csci3081