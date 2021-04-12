#include "smart_route.h"

namespace csci3081 {
    std::vector <std::vector<float>> SmartRoute::GetRoute(IGraph* graph, std::vector<float> location, std::vector<float> dest){
        return graph->GetPath(location, dest);
    }
}