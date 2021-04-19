#include "../include/parabolic_route.h"

namespace csci3081 {
    std::vector <std::vector<float>> ParabolicRoute::GetRoute(const IGraph* graph, std::vector<float> location, std::vector<float> dest){
        float j = 300.00;//(j) is a tuning parameter that we can use to avoid building collision and scale the parabola's slope.
        int steps =50;
        Vector3D start(location);
        Vector3D end(dest);
        Vector3D middle = (start + end)/2;
        Vector3D dV = (end - start)/steps;//delta Vector
        float dis_mid_source = Distance(start,middle);
        std::vector <std::vector<float>> path;
        Vector3D current = start;
        path.push_back(location);
        for(int i = 0;i < steps-1; i++){
            current = current + dV;//update the current position 
            std::vector<float> converted = toVectorFloat(current);
            float dis_mid_cur = Distance(middle,current);//calculate the distance between current position to the middle point
            float dY = (1 - (dis_mid_cur*dis_mid_cur)/(dis_mid_source*dis_mid_source))*j;//caculate the delta height that using the forumla from lab14 
            converted[1]+=dY;
            path.push_back(converted);//add point to the path
        }
        path.push_back(dest);
        return path;

        ;//Logic for generating the parabolic path points goes here
    
    }
}