/**
 * @file Beeline_Route
 */
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
 * @brief This is the Beeline Route class where we can use the strategy pattern to implement a Beeline route for carriers
 */
    class BeelineRoute : public csci3081::RouteStrategy {
        public:
            /**
             * @brief This function 
             * allows the moving item to get the desired route. In this class, the function will return a 
             * route that follows the Beeline path
             * @param IGraph* graph
             * @param std::vector<float> location
             * @param std::vector<float> dest
             * @return std::vector <std::vector<float>>
             */
            std::vector <std::vector<float>> GetRoute(IGraph* graph, std::vector<float> location, std::vector<float> dest);
    };
} // namespace 3081