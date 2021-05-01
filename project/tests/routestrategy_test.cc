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
TEST_F(RouteStrategyTest, ParabolicPathTest) {
  ParabolicRoute pRoute;
  std::vector<std::vector<float>> path1 = pRoute.GetRoute(graph, start, des);
  float j = 300.00;  //(j) is a tuning parameter that we can use to avoid building collision and scale the parabola's slope.
  int steps = 50;
  vector<float> startInAir = start;
  startInAir[1]+=50;
  Vector3D startV(startInAir);
  vector<float> endInAir = des;
  endInAir[1]+=50;
  Vector3D end(endInAir);
  Vector3D middle = (startV + end) / 2;
  Vector3D dV = (end - startV) / steps;
  float dis_mid_source = Distance(startV, middle);
  std::vector<std::vector<float>> path;
  Vector3D current = startInAir;
  path.push_back(start);
  path.push_back(startInAir);
  for (int i = 0; i < steps - 1; i++) {
    current = current + dV;
    std::vector<float> converted = toVectorFloat(current);
    float dis_mid_cur = Distance(middle, current);
    float dY = (1 - (dis_mid_cur * dis_mid_cur) / (dis_mid_source * dis_mid_source)) * j;
    converted[1] += dY;
    path.push_back(converted);
  }
  path.push_back(endInAir);
  path.push_back(des);

  EXPECT_EQ(path.size(), path1.size()) << "path and path1 size do not match";

  for (int i = 0; i < path.size(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(path[i][j], path1[i][j]) << "Parabolic path does not work";
    }
  }

}

}  // namespace csci3081