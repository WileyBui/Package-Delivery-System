#include "../include/smart_route.h"

namespace csci3081 {
    std::vector <std::vector<float>> SmartRoute::GetRoute(const IGraph* graph, std::vector<float> location, std::vector<float> dest){
        return graph->GetPath(location, dest);
    }
}