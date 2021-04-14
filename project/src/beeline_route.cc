#include "../include/beeline_route.h"

namespace csci3081 {

    std::vector <std::vector<float>> BeelineRoute::GetRoute(IGraph* graph, std::vector<float> location, std::vector<float> dest){
        // logic for generating beeline path goes here
        return graph->GetPath(location, dest);
    }
}