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
             * @brief This function allows the moving item to get the desired route. In this class, the function
             * will return a route that follows the Beeline path.
             * 
             * The route includes a point where the drone needs to go up to by a certain height from where it is at,
             * then another point to the destination location with the same certain height, then another point to
             * the final destination location.
             * 
             * @param const IGraph* graph; we don't need to use this parameter
             * @param std::vector<float> location   Current drone location
             * @param std::vector<float> dest       Final location where the drone needs to be
             * @return std::vector <std::vector<float>> The path of the beeline
             */

            std::vector <std::vector<float>> GetRoute(const IGraph* graph, std::vector<float> location, std::vector<float> dest);
    };
} // namespace 3081