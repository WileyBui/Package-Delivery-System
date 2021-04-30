#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/package.h"
#include "../include/recharge_drone.h"
#include "../include/drone.h"
#include "../include/customer.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class RechargeDroneTest : public ::testing::Test {
 protected:
    picojson::object obj = JsonHelper::CreateJsonObject();    
    picojson::object obj1 = JsonHelper::CreateJsonObject();
    picojson::object obj2 = JsonHelper::CreateJsonObject();
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    picojson::object obj4 = JsonHelper::CreateJsonObject();
    picojson::object obj5 = JsonHelper::CreateJsonObject();

    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    std::vector<float> position_to_add2;
    std::vector<float> direction_to_add2;
    float radius = 1.0;
    float speed = 3.0;
    float battery_capacity = 15000;
    float dead_battery_capacity = 0;
 public:
  virtual void SetUp() {
    position_to_add.push_back(100);
    position_to_add.push_back(253.883);
    position_to_add.push_back(431.292);
    position_to_add2.push_back(2253.883);
    position_to_add2.push_back(4938.292);
    position_to_add2.push_back(2533.883);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    direction_to_add2.push_back(0);
    direction_to_add2.push_back(1);
    direction_to_add2.push_back(0);

    JsonHelper::AddStringToJsonObject(obj, "type", "recharging_drone");
    JsonHelper::AddStringToJsonObject(obj,"name","Lin");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", battery_capacity);
    JsonHelper::AddFloatToJsonObject(obj, "speed", speed);


    JsonHelper::AddStringToJsonObject(obj1, "type", "recharging_drone");
    JsonHelper::AddStringToJsonObject(obj1,"name","Minho");
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj1, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj1, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj1, "speed", speed);

    JsonHelper::AddStringToJsonObject(obj2,"name","SHINeeCD");
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj2, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj2, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj2, "battery_capacity", battery_capacity);
    JsonHelper::AddStringToJsonObject(obj2, "path", "beeline");
    
    JsonHelper::AddStringToJsonObject(obj3, "type", "recharging_drone");
    JsonHelper::AddStringToJsonObject(obj3,"name","Minho");
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj3, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj3, "speed", speed);
    JsonHelper::AddStringToJsonObject(obj3, "path", "beeline");

    JsonHelper::AddStringToJsonObject(obj4, "type", "recharging_drone");
    JsonHelper::AddStringToJsonObject(obj4,"name","Minho");
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj4, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj4, "speed", speed);
    JsonHelper::AddStringToJsonObject(obj4, "path", "beeline");

    JsonHelper::AddStringToJsonObject(obj5, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj5,"name","Rose");
    JsonHelper::AddStdFloatVectorToJsonObject(obj5, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj5, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj5, "battery_capacity", dead_battery_capacity);
    JsonHelper::AddFloatToJsonObject(obj5, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj5, "speed", speed);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RechargeDroneTest, ConstructorAndGetter) {
  // Normal constructor
  // Customer Lin("Lin",position_to_add,direction_to_add,radius,obj);
  RechargeDrone SHINeeCD(obj2);
  EXPECT_EQ(SHINeeCD.GetName(),"SHINeeCD") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[0], direction_to_add2[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[1], direction_to_add2[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[2], direction_to_add2[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_EQ(SHINeeCD.GetType(), "recharging_drone") << "Normal Constructor or GetType does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(), speed) << "Normal Constructor or GetSpeed does not work";
  EXPECT_EQ(SHINeeCD.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_FALSE(SHINeeCD.IsDynamic()) << "Normal Constructor or IsDynamic does not work";
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "Normal Constructor or BatteryDead does not work";
  EXPECT_TRUE(SHINeeCD.Charging(1000)) << "Normal Constructor or Charging does not work";
}

TEST_F(RechargeDroneTest, CopyConstructorAndGetter) {
  // Normal constructor
  RechargeDrone SHINeeCD2(obj2);
  RechargeDrone SHINeeCD(SHINeeCD2);
  EXPECT_EQ(SHINeeCD.GetName(),"SHINeeCD") << "Copy Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], position_to_add2[0]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], position_to_add2[1]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], position_to_add2[2]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[0], direction_to_add2[0]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[1], direction_to_add2[1]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetDirection()[2], direction_to_add2[2]) << "Copy Constructor or GetDirection does not work";
  EXPECT_EQ(SHINeeCD.GetType(), "recharging_drone") << "Normal Constructor or GetType does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetRadius(), radius) << "Copy Constructor or GetRadius does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(), speed) << "Copy Constructor or GetSpeed does not work";
  EXPECT_EQ(SHINeeCD.GetVersion(),0) << "Copy Constructor or GetVersion does not work";
  EXPECT_FALSE(SHINeeCD.IsDynamic()) << "Copy Constructor or IsDynamic does not work";
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "Copy Constructor or BatteryDead does not work";
  EXPECT_FALSE(SHINeeCD.Charging(-1000)) << "Copy Constructor or Charging does not work";
}
 
TEST_F(RechargeDroneTest, Route) {
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
    }
    SHINeeCD.SetRoute(path);
    EXPECT_TRUE(SHINeeCD.IsDynamic()) << "SetRoute does not work";

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

TEST_F(RechargeDroneTest, IsWithin){
  RechargeDrone Lin(obj); 
  Drone SM(obj5);
  EXPECT_TRUE(Lin.IsWithin(&SM))<<"IsWithin does not work for RechargeDrone";  
}

TEST_F(RechargeDroneTest, SetPosition){
  RechargeDrone SHINeeCD(obj2);
  std::vector<float> placeHolder;
	placeHolder.push_back(12.0);
	placeHolder.push_back(15.0);
	placeHolder.push_back(16.0);
  SHINeeCD.SetPosition(placeHolder);
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[0], placeHolder[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[1], placeHolder[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(SHINeeCD.GetPosition()[2], placeHolder[2]) << "Normal Constructor or GetPosition does not work";   
}

TEST_F(RechargeDroneTest, UpdateAndBattery){
  RechargeDrone SHINeeCD(obj2);
  Customer Lin(obj2); 
  SHINeeCD.SetSpeed(0.0000000000001);
  SHINeeCD.Update(10);
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
  std::vector<std::vector<float>> path;
  path.push_back(position_to_add2);
  path.push_back(position_to_add);
  SHINeeCD.SetRoute(path);
  SHINeeCD.Update(20);
  EXPECT_FALSE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
  SHINeeCD.Update(20000);
  EXPECT_TRUE(SHINeeCD.BatteryDead()) << "BatteryDead does not work";
}

TEST_F(RechargeDroneTest, SetSpeed){
  RechargeDrone SHINeeCD(obj2);
  SHINeeCD.SetSpeed(2.4);
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
  SHINeeCD.SetSpeed(-10.5);
  EXPECT_FLOAT_EQ(SHINeeCD.GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
}

TEST_F(RechargeDroneTest, PathConstructor){
  RechargeDrone droneDefault(obj1);
  RechargeDrone droneBeeline(obj2);

  RouteStrategy* routeChoice = droneDefault.GetRouteStrategy();
  EXPECT_TRUE((dynamic_cast<BeelineRoute*> (routeChoice)) != nullptr) << "Default Constructor does not work for path choosing";

  routeChoice = droneBeeline.GetRouteStrategy();
  EXPECT_TRUE((dynamic_cast<BeelineRoute*> (routeChoice)) != nullptr) << "Default Constructor does not work for path choosing";

}

TEST_F(RechargeDroneTest,ChargeTheDroneAndGetDeadDrone){
  RechargeDrone droneDefault(obj1);
  Drone DeadDrone(obj5);
  droneDefault.SetDeadCarrier(&DeadDrone);
  droneDefault.IsChargingCarrierFull(10);
  EXPECT_TRUE((droneDefault.GetDeadCarrier() != nullptr))<<"RechargeDrone GetDeadCarrier function does not work";
  EXPECT_FALSE(DeadDrone.BatteryDead())<<"RechargeDrone Charging function does not work";
  EXPECT_FALSE(droneDefault.BatteryFull())<<"RechargeDrone Charging function does not work";
  EXPECT_TRUE(droneDefault.IsChargingACarrier())<<"RechargeDrone IsChargingACarrier function does not work";
  EXPECT_TRUE(DeadDrone.IsCurrentlyCharging())<<"Drone IsCharging function does not work";
}
}  // namespace csci3081