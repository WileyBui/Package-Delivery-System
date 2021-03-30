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
    float battery_capacity = 10000;
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

TEST_F(DroneTest, ConstructorAndGetter) {}

}//namespace csci3081