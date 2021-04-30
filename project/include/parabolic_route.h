/**
 * @file Parabolic_Route
 */
#ifndef PARABOLICROUTE_H_
#define PARABOLICROUTE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include <vector>
#include "route_strategy.h"
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the Parabolic Route class where we can use the strategy pattern to implement a parabolic route
 */
    class ParabolicRoute : public csci3081::RouteStrategy {
        public:
            /**
             * @brief This function 
             * allows the moving item to get the desired route. In this class, the function will return a 
             * route that follows the parabolic path. However a pure parabolic path will make the drone clips the building at the end. 
               What we did is raise the drone to a certain height first,then do parabolic in the air and descend veritcally.
             * @param const IGraph* graph
             * @param std::vector<float> location
             * @param std::vector<float> dest
             * @return std::vector <std::vector<float>>
             */
            std::vector <std::vector<float>> GetRoute(const IGraph* graph, std::vector<float> location, std::vector<float> dest);
    };
} // namespace 3081

#endif 