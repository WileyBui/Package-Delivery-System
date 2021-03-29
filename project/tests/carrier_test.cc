#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/package.h"
#include "../include/carrier.h"
#include "../include/customer.h"
#include "../include/drone.h"
#include "json_helper.h"
#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class CarrierTest : public ::testing::Test {
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
    JsonHelper::AddStringToJsonObject(obj, "type", "Carrier");
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
    JsonHelper::AddFloatToJsonObject(obj, "battery_capacity", battery_capacity);
    JsonHelper::AddFloatToJsonObject(obj2, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj2, "speed", speed);
    JsonHelper::AddFloatToJsonObject(obj2, "battery_capacity", battery_capacity);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(CarrierTest, Getter) {
  // Normal constructor
  // Customer Lin("Lin",position_to_add,direction_to_add,radius,obj);
  Drone SHINeeCD(obj2);
  Carrier*carrier = &SHINeeCD;
  EXPECT_EQ(carrier->GetName(),"SHINeeCD") << "Normal Constructor or GetName does not work";
  EXPECT_FLOAT_EQ(carrier->GetPosition()[0], position_to_add2[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(carrier->GetPosition()[1], position_to_add2[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(carrier->GetPosition()[2], position_to_add2[2]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(carrier->GetDirection()[0], direction_to_add2[0]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(carrier->GetDirection()[1], direction_to_add2[1]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(carrier->GetDirection()[2], direction_to_add2[2]) << "Normal Constructor or GetDirection does not work";
  EXPECT_FLOAT_EQ(carrier->GetRadius(), radius) << "Normal Constructor or GetRadius does not work";
  EXPECT_FLOAT_EQ(carrier->GetSpeed(), speed) << "Normal Constructor or GetSpeed does not work";
  EXPECT_FLOAT_EQ(carrier->GetBattery(), battery_capacity) << "Normal Constructor or GetSpeed does not work";
  EXPECT_EQ(carrier->GetType(), "carrier") << "Normal Constructor or GetBattery does not work";
  EXPECT_EQ(carrier->GetVersion(),0) << "Normal Constructor or GetVersion does not work";
  EXPECT_FALSE(carrier->IsDynamic()) << "Normal Constructor or IsDynamic does not work";
  EXPECT_TRUE(carrier->GetPackage()==NULL) <<"Normal Constructor or GetPackageID does not work";
  EXPECT_FALSE(carrier->BatteryDead()) << "Normal Constructor or BatteryDead does not work";
  EXPECT_FALSE(carrier->HavePackage()) << "Normal Constructor or HavePackage does not work";
  EXPECT_TRUE(carrier->Charging(1000)) << "Normal Constructor or Charging does not work";
  EXPECT_TRUE(carrier->DropPackage()==NULL) << "Normal Constructor or BatteryDead does not work";
}

TEST_F(CarrierTest, AddingPackage){
  Customer Lin(obj); 
  Carrier* carrier;
  Drone SM(obj2);
  carrier = &SM;
  Package SHINeeCD(obj2);
  EXPECT_FLOAT_EQ(carrier->DistanceBetween(&SHINeeCD), 0) << "DistanceBetween does not work";
  EXPECT_FLOAT_EQ(carrier->DistanceBetween(&Lin), 5568.104575) << "DistanceBetween does not work";

  SHINeeCD.SetOwner(&Lin);

  EXPECT_TRUE(carrier->AddPackage(&SHINeeCD)) << "Add AddPackage does not work";  
  EXPECT_EQ(carrier->GetPackage()->GetId(),SHINeeCD.GetId()) << "GetPackageID does not work";
  EXPECT_TRUE(carrier->HavePackage()) << "Add HavePackage does not work";  
  
  // Add another package
  Package SummerPackage(obj2);
  EXPECT_FALSE(carrier->AddPackage(&SummerPackage)) << "Add HavePackage does not work";  
  carrier->DropPackage();
  EXPECT_TRUE(carrier->AddPackage(&SummerPackage)) << "Add HavePackage does not work";  
}
 
TEST_F(CarrierTest, Route) {
    // AddPosition
    srand(0);
    std::vector<float> homie;
    std::vector<std::vector<float>> path;
    Drone SHINeeCD(obj2);
    Carrier* carrier = &SHINeeCD;
    homie.push_back(1);
    homie.push_back(2);
    homie.push_back(3);
    for (int j = 0; j<9; j++){
      for (int i = 0; i<3; i++){
        homie.at(i) = rand()%100;
      }
      path.push_back(homie);
    }

    carrier->SetRoute(path);
    EXPECT_TRUE(carrier->IsDynamic()) << "SetRoute does not work";

    int j = 0;
    for (int i = 0; i<9; i++){
      std::vector<float> placeHolder = carrier->NextPosition();
      EXPECT_FLOAT_EQ(placeHolder[0], path[j][0]) << "NextPosition does not work";
      EXPECT_FLOAT_EQ(placeHolder[1], path[j][1]) << "NextPosition does not work";
      EXPECT_FLOAT_EQ(placeHolder[2], path[j][2]) << "NextPosition does not work";
      carrier->PopPosition();
      j++;
    }
    EXPECT_FALSE(carrier->IsDynamic()) << "SetRoute does not work";
}

TEST_F(CarrierTest, IsWithin){
  Customer Lin(obj); 
  Drone SM(obj2);
  Carrier* carrier = &SM;
  Package SHINeeCD(obj2);
  EXPECT_FALSE(carrier->IsWithin(&Lin));
  EXPECT_TRUE(carrier->IsWithin(&SHINeeCD));  
}

TEST_F(CarrierTest, SetPosition){
  Drone SHINeeCD(obj2);
  Carrier* carrier = &SHINeeCD;
  std::vector<float> placeHolder;
	placeHolder.push_back(12.0);
	placeHolder.push_back(15.0);
	placeHolder.push_back(16.0);
  carrier->SetPosition(placeHolder);
  EXPECT_FLOAT_EQ(carrier->GetPosition()[0], placeHolder[0]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(carrier->GetPosition()[1], placeHolder[1]) << "Normal Constructor or GetPosition does not work";
  EXPECT_FLOAT_EQ(carrier->GetPosition()[2], placeHolder[2]) << "Normal Constructor or GetPosition does not work";   
}

TEST_F(CarrierTest, UpdateAndBattery){
  Drone SHINeeCD(obj2);
  Carrier*carrier = &SHINeeCD;
  Customer Lin(obj2); 
  carrier->SetSpeed(0.0000000000001);
  carrier->Update(10);
  EXPECT_FALSE(carrier->BatteryDead()) << "BatteryDead does not work";
  Package SM(obj);
  SM.SetOwner(&Lin);
  EXPECT_TRUE(carrier->AddPackage(&SM)) << "AddPackage faulty";
  EXPECT_TRUE(carrier->HavePackage()) << "AddPackage faulty";
  carrier->Update(10000);
  EXPECT_TRUE(carrier->BatteryDead()) << "BatteryDead does not work";
  carrier->DropPackage();
  carrier->Update(10000);
  EXPECT_FALSE(carrier->BatteryDead()) << "BatteryDead does not work";
}


TEST_F(CarrierTest, SetSpeed){
  Drone SHINeeCD(obj2);
  Carrier*carrier = &SHINeeCD;
  carrier->SetSpeed(2.4);
  EXPECT_FLOAT_EQ(carrier->GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
  carrier->SetSpeed(-10.5);
  EXPECT_FLOAT_EQ(carrier->GetSpeed(),2.4) << "SetSpeed or GetSpeed is faulty";
}

}  // namespace csci3081