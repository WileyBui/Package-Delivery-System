#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/charging_station.h"
#include "../include/recharge_drone.h"
#include "../include/drone.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class ChargingStationTest : public ::testing::Test {
 protected:
    picojson::object obj  = JsonHelper::CreateJsonObject();
    picojson::object obj2 = JsonHelper::CreateJsonObject();
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    picojson::object obj4 = JsonHelper::CreateJsonObject();
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    std::vector<float> position_to_add2;
    std::vector<float> direction_to_add2;
    float radius = 1.0;
    float speed = 3.0;
    float battery_capacity = 10000;
    float rechargingDroneBatteryCapacity = 20000;
 public:
  virtual void SetUp() {
    JsonHelper::AddStringToJsonObject(obj, "type", "recharge_station");
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(253.883);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStringToJsonObject(obj,"name","recharge_station");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);

    JsonHelper::AddStringToJsonObject(obj2, "type", "recharging_drone");
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add);
    JsonHelper::AddStringToJsonObject(obj2,"name","recharging_drone");
    JsonHelper::AddFloatToJsonObject(obj2, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj2, "radius", radius);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj2, "battery_capacity", rechargingDroneBatteryCapacity);

    JsonHelper::AddStringToJsonObject(obj3, "type", "recharging_drone");
    position_to_add2.push_back(-951.412);
    position_to_add2.push_back(254.665);
    position_to_add2.push_back(298.271);
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add2);
    direction_to_add2.push_back(1);
    direction_to_add2.push_back(0);
    direction_to_add2.push_back(0);
    JsonHelper::AddStringToJsonObject(obj3,"name","recharging_drone");
    JsonHelper::AddFloatToJsonObject(obj3, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj3, "radius", radius);
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj3, "battery_capacity", rechargingDroneBatteryCapacity);

    JsonHelper::AddStringToJsonObject(obj4, "type", "drone");
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "position", position_to_add2);
    JsonHelper::AddStringToJsonObject(obj4,"name","drone");
    JsonHelper::AddFloatToJsonObject(obj4, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj4, "radius", radius);
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "direction", direction_to_add2);
    JsonHelper::AddFloatToJsonObject(obj4, "battery_capacity", battery_capacity);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ChargingStationTest, ConstructorAndGetter) {
  // Normal constructor
  ChargingStation station(obj);
  EXPECT_EQ(station.GetName(),"recharge_station") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(station.GetPosition()[0], position_to_add[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station.GetPosition()[1], position_to_add[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station.GetPosition()[2], position_to_add[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station.GetDirection()[0], direction_to_add[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station.GetDirection()[1], direction_to_add[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station.GetDirection()[2], direction_to_add[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_EQ(station.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_EQ(station.IsDynamic(),false) << "Normal Constructor or IsDynamic does not work";
  EXPECT_EQ(station.GetType(), "charging_station") << "Normal Constructor or GetType does not work";

  // Copy Constructor
  ChargingStation station2(station);
  EXPECT_EQ(station2.GetId(),station.GetId()) << "Copy Constructor or GetId does not work";
  EXPECT_EQ(station2.GetName(),"recharge_station") << "Copy Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(station2.GetPosition()[0], position_to_add[0]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station2.GetPosition()[1], position_to_add[1]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station2.GetPosition()[2], position_to_add[2]) << "Copy Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(station2.GetDirection()[0], direction_to_add[0]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station2.GetDirection()[1], direction_to_add[1]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station2.GetDirection()[2], direction_to_add[2]) << "Copy Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(station2.GetRadius(), radius) << "Copy Constructor or GetRadius does not work";
  EXPECT_EQ(station2.GetType(), "charging_station") << "Normal Constructor or GetType does not work";
  EXPECT_EQ(station2.GetVersion(),0) << "Copy Constructor or GetVersion does not work";
  EXPECT_EQ(station2.IsDynamic(),false) << "Copy Constructor or IsDynamic does not work";


  RechargeDrone rechargeDrone(obj2);
  EXPECT_EQ(rechargeDrone.GetName(),"recharging_drone") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetPosition()[0], position_to_add[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetPosition()[1], position_to_add[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetPosition()[2], position_to_add[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetDirection()[0], direction_to_add[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetDirection()[1], direction_to_add[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetDirection()[2], direction_to_add[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(rechargeDrone.GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_EQ(rechargeDrone.GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_EQ(rechargeDrone.IsDynamic(),false) << "Normal Constructor or IsDynamic does not work";
  EXPECT_EQ(rechargeDrone.GetType(), "recharging_drone") << "Normal Constructor or GetType does not work";
}

TEST_F(ChargingStationTest, AddAndPopAndHasDeadCarrierTest) {
  ChargingStation station(obj);
  Carrier drone1;
  Carrier drone2;
  Carrier drone3;
  Carrier robot1;
  Carrier robot2;
  Carrier robot3;

  station.AddDeadCarrier(&drone1);
  station.AddDeadCarrier(&robot1);
  station.AddDeadCarrier(&drone2);
  station.AddDeadCarrier(&robot2);
  EXPECT_TRUE(station.HasDeadCarrier(&drone1)) << "HasDeadCarrier is faulty (drone1)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot1)) << "HasDeadCarrier is faulty (drone2)";
  EXPECT_TRUE(station.HasDeadCarrier(&drone2)) << "HasDeadCarrier is faulty (drone3)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot2)) << "HasDeadCarrier is faulty (robot1)";
  EXPECT_FALSE(station.HasDeadCarrier(&drone3)) << "HasDeadCarrier is faulty (robot2)";
  EXPECT_FALSE(station.HasDeadCarrier(&robot3)) << "HasDeadCarrier is faulty (robot3)";

  station.AddDeadCarrier(&drone3);
  station.AddDeadCarrier(&robot3);
  EXPECT_TRUE(station.HasDeadCarrier(&drone1)) << "HasDeadCarrier is faulty (drone1)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot1)) << "HasDeadCarrier is faulty (drone2)";
  EXPECT_TRUE(station.HasDeadCarrier(&drone2)) << "HasDeadCarrier is faulty (drone3)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot2)) << "HasDeadCarrier is faulty (robot1)";
  EXPECT_TRUE(station.HasDeadCarrier(&drone3)) << "HasDeadCarrier is faulty (robot2)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot3)) << "HasDeadCarrier is faulty (robot3)";

  station.PopDeadCarrier();
  station.PopDeadCarrier();

  EXPECT_FALSE(station.HasDeadCarrier(&drone1)) << "HasDeadCarrier is faulty (drone1)";
  EXPECT_FALSE(station.HasDeadCarrier(&robot1)) << "HasDeadCarrier is faulty (drone2)";
  EXPECT_TRUE(station.HasDeadCarrier(&drone2)) << "HasDeadCarrier is faulty (drone3)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot2)) << "HasDeadCarrier is faulty (robot1)";
  EXPECT_TRUE(station.HasDeadCarrier(&drone3)) << "HasDeadCarrier is faulty (robot2)";
  EXPECT_TRUE(station.HasDeadCarrier(&robot3)) << "HasDeadCarrier is faulty (robot3)";

  station.PopDeadCarrier();
  station.PopDeadCarrier();
  station.PopDeadCarrier();
  station.PopDeadCarrier();
  EXPECT_FALSE(station.HasDeadCarrier(&drone1)) << "HasDeadCarrier is faulty (drone1)";
  EXPECT_FALSE(station.HasDeadCarrier(&robot1)) << "HasDeadCarrier is faulty (drone2)";
  EXPECT_FALSE(station.HasDeadCarrier(&drone2)) << "HasDeadCarrier is faulty (drone3)";
  EXPECT_FALSE(station.HasDeadCarrier(&robot2)) << "HasDeadCarrier is faulty (robot1)";
  EXPECT_FALSE(station.HasDeadCarrier(&drone3)) << "HasDeadCarrier is faulty (robot2)";
  EXPECT_FALSE(station.HasDeadCarrier(&robot3)) << "HasDeadCarrier is faulty (robot3)";
}

TEST_F(ChargingStationTest, AddChargingDrone) {
  ChargingStation station(obj);
  RechargeDrone rechargeDrone(obj2);
  RechargeDrone rechargeDrone2(obj3);

  EXPECT_TRUE(station.AddChargingDrone(&rechargeDrone)) << "AddChargingDrone is faulty (rechargeDrone)";
  EXPECT_FALSE(station.AddChargingDrone(&rechargeDrone)) << "AddChargingDrone is faulty (rechargeDrone)";
  
  EXPECT_TRUE(station.AddChargingDrone(&rechargeDrone2)) << "AddChargingDrone is faulty (rechargeDrone2)";
  EXPECT_FALSE(station.AddChargingDrone(&rechargeDrone2)) << "AddChargingDrone is faulty (rechargeDrone2)";
}

TEST_F(ChargingStationTest, UpdateTest) {
  ChargingStation station(obj);
  RechargeDrone rechargeDrone(obj2);
  Drone drone(obj4);

  EXPECT_TRUE(station.IsWithin(&rechargeDrone)) << "IsWithin is faulty; charging station & rechare drone should be at the same location";
  EXPECT_TRUE(station.AddChargingDrone(&rechargeDrone)) << "AddChargingDrone is faulty (rechargeDrone)";

  EXPECT_FALSE(drone.BatteryDead()) << "drone.BatteryDead() is faulty";
  Battery* droneBattery = drone.GetBatteryObj();
  droneBattery->Depleting(droneBattery->GetRemainingLife());

  station.AddDeadCarrier(&drone);
  EXPECT_TRUE(station.HasDeadCarrier(&drone)) << "HasDeadCarrier is faulty (drone)";

  station.Update(100);
  EXPECT_TRUE(drone.BatteryDead()) << "drone.BatteryDead() is faulty";
  EXPECT_FALSE(station.HasDeadCarrier(&drone)) << "HasDeadCarrier is faulty (drone)";

  station.Update(1500);
  EXPECT_TRUE(drone.BatteryDead()) << "drone.BatteryDead() is faulty";
  EXPECT_FLOAT_EQ(station.GetPosition()[0], rechargeDrone.GetPosition()[0]) << "GetPosition() does not match";
  EXPECT_FLOAT_EQ(station.GetPosition()[1], rechargeDrone.GetPosition()[1]) << "GetPosition() does not match";
  EXPECT_FLOAT_EQ(station.GetPosition()[2], rechargeDrone.GetPosition()[2]) << "GetPosition() does not match";
}

}  // namespace csci3081