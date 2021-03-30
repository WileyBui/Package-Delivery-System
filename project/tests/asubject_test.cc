#include "gtest/gtest.h"
#include "../include/drone.h"
#include "../include/robot.h"
#include "json_helper.h"
//#include "../include/asubject.h"

#include <EntityProject/entity.h>
#include <EntityProject/project_settings.h>
#include <EntityProject/web_scene_viewer.h>
#include <EntityProject/osm_graph_parser.h>
#include <EntityProject/graph.h>
#include <EntityProject/facade/delivery_system.h>
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
    //JsonHelper::AddStringToJsonObject(obj, "type", "Drone");
    position_to_add.push_back(100);
    position_to_add.push_back(253.883);
    position_to_add.push_back(431.292);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(1);
    JsonHelper::AddStringToJsonObject(obj,"name","Aunya");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", radius);
    JsonHelper::AddFloatToJsonObject(obj, "speed", speed);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ASubjectTest, AttachTest) {
  Drone drone(obj);
  Package pack(obj);
  Robot robo(obj); 

  entity_project::IEntitySystem* entitySystem = GetEntitySystem("default");
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(entitySystem);

  // Create and set the graph
  if (deliverySystem) {
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    deliverySystem->SetGraph(graph);
  }

  // Create the web scene viewer
  entity_project::WebSceneViewer viewer(8081, "web", "scenes/all_features.json");
  viewer.SetEntitySystem(entitySystem);

  entity_project::EntityConsoleLogger logger;
    if (deliverySystem) {
    //   deliverySystem->AddObserver(&logger);
    //   deliverySystem->AddObserver(&viewer);
    // }
      ASSERT_EQ(drone.GetList().size(), 0)<< "List should not be populated yet in attach, for drone";
      drone.Attach(&logger);
      ASSERT_EQ(drone.GetList().size(), 1)<< "List should be populated to 1 in attach, for drone";
      drone.Attach(&viewer);
      ASSERT_EQ(drone.GetList().size(), 2)<< "List should be populated to 2 in attach, for drone";

      ASSERT_EQ(pack.GetList().size(), 0)<< "List should not be populated yet in attach, for pack";
      pack.Attach(&logger);
      ASSERT_EQ(pack.GetList().size(), 1)<< "List should be populated to 1 in attach, for pack";
      pack.Attach(&viewer);
      ASSERT_EQ(pack.GetList().size(), 2)<< "List should be populated to 2 in attach, for pack";

      ASSERT_EQ(robo.GetList().size(), 0)<< "List should not be populated yet in attach, for robo";
      robo.Attach(&logger);
      ASSERT_EQ(robo.GetList().size(), 1)<< "List should be populated to 1 in attach, for robo";
      robo.Attach(&viewer);
      ASSERT_EQ(robo.GetList().size(), 2)<< "List should be populated to 2 in attach, for robo";
    }

  
}

}//namespace csci3081