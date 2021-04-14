#include "parabolic_route.h"

namespace csci3081 {
    std::vector <std::vector<float>> ParabolicRoute::GetRoute(IGraph* graph, std::vector<float> location, std::vector<float> dest){
        //Logic for generating the parabolic path points goes here
        return graph->GetPath(location, dest);
    }
}