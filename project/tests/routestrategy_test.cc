#include <EntityProject/entity.h>

#include <iostream>

#include "../include/beeline_route.h"
#include "../include/parabolic_route.h"
#include "../include/route_strategy.h"
#include "../include/smart_route.h"
#include "gtest/gtest.h"
#include "json_helper.h"

namespace csci3081 {

// using RouteStrategy;

class RouteStrategyTest : public ::testing::Test {
 protected:
  const entity_project::IGraph* graph;
  std::vector<float> start;
  std::vector<float> des;

 public:
  virtual void SetUp() {
    start.push_back(245.33);
    start.push_back(300.4);
    start.push_back(137.9);
    des.push_back(543.65);
    des.push_back(300.4);
    des.push_back(320.68);
  }
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteStrategyTest, GetRouteBeelineTest) {
  float maxBuildingHeight = 400;
  BeelineRoute bRoute;
  std::vector<std::vector<float>> path1 = bRoute.GetRoute(graph, start, des);

  // start
  std::vector<std::vector<float>> myPath;
  myPath.push_back(start);

  // start, but height = maxBuildingHeight
  std::vector<float> current = start;
  current[1] = maxBuildingHeight;
  myPath.push_back(current);

  // destination, but height = maxBuildingHeight
  current = des;
  current[1] = maxBuildingHeight;
  myPath.push_back(current);

  // destination
  myPath.push_back(des);

  EXPECT_EQ(myPath.size(), path1.size()) << "myPath and path1 size do not match";

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(path1[i][j], myPath[i][j]) << "Beeline path does not work";
    }
  }
}

}  // namespace csci3081