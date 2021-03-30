#include "gtest/gtest.h"
#include <EntityProject/entity.h>
#include "../include/drone.h"
#include "json_helper.h"
#include "../include/asubject.h"

#include <EntityProject/web_scene_viewer.h>
#include <EntityProject/entity_console_logger.h>

#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class ASubjectTest : public ::testing::Test {
 protected:
    picojson::object obj = JsonHelper::CreateJsonObject();
    std::vector<float> position_to_add;
    std::vector<float> direction_to_add;
    float radius = 1.0;
    float speed = 3.0;
 public:
  virtual void SetUp() {
    JsonHelper::AddStringToJsonObject(obj, "type", "Drone");
    position_to_add.push_back(100);
    position_to_add.push_back(253.883);
    position_to_add.push_back(431.292);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStringToJsonObject(obj,"name","Aunya");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ASubjectTest, AttachTest) {
  IEntitySystem* entitySystem = GetEntitySystem("default");
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(entitySystem);

  // Create the web scene viewer
  WebSceneViewer viewer(8081, web, scenes/all_features.json);
  viewer.SetEntitySystem(entitySystem);

  entity_project::EntityConsoleLogger logger;
    if (deliverySystem) {
      deliverySystem->AddObserver(&logger);
      deliverySystem->AddObserver(&viewer);
    }

  
}

}//namespace csci3081