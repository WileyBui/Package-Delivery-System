#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/


TEST_F(FactoryTest, CarrierFactoryDrone) {
  // Drone
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  JsonHelper::AddStringToJsonObject(obj, "name", "drone");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);
  ASSERT_FLOAT_EQ(dynamic_cast<Carrier*> (entity)->GetBattery(), 10000);
  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

TEST_F(FactoryTest, CarrierFactoryRobot) {
  // Drone
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "robot");
  JsonHelper::AddStringToJsonObject(obj, "name", "robot");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);
  ASSERT_FLOAT_EQ(dynamic_cast<Carrier*> (entity)->GetBattery(), 10000);
  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

TEST_F(FactoryTest, PackageFactory) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "package");
  JsonHelper::AddStringToJsonObject(obj, "name", "package");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

TEST_F(FactoryTest, CustomerFactory) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "customer");
  JsonHelper::AddStringToJsonObject(obj, "name", "customer");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
}

TEST_F(FactoryTest, ChargingStationTest) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "recharge_station");
  JsonHelper::AddStringToJsonObject(obj, "name", "recharge_station");
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

  IEntity* entity = system->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  system->AddEntity(entity);
  ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());
}

}  // namespace csci3081
