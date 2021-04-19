#include "../include/beeline_route.h"

namespace csci3081 {

std::vector<std::vector<float>> BeelineRoute::GetRoute(const IGraph* graph, std::vector<float> location, std::vector<float> dest) {
  vector<vector<float>> path;

  Vector3D srcPosition = Vector3D(location);    // current position of the drone
  Vector3D destPosition = Vector3D(dest);  // destination position of the drone
  Vector3D flyToPosition;

  float heightToAvoidCollision = 400;  // height where the drone must not touch any building

  path.push_back(toVectorFloat(srcPosition));

  // Go up to heightToAvoidCollision from the source location
  flyToPosition = srcPosition;
  flyToPosition.SetY(heightToAvoidCollision);
  path.push_back(toVectorFloat(flyToPosition));

  // Go horizontally to the destination location
  flyToPosition = destPosition;
  flyToPosition.SetY(heightToAvoidCollision);
  path.push_back(toVectorFloat(flyToPosition));

  // Go down to reach the source location
  flyToPosition = destPosition;
  path.push_back(toVectorFloat(flyToPosition));

  return path;
}

}  // namespace csci3081