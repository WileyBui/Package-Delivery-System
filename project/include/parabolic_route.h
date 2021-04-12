/**
 * @file Parabolic_Route
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
 * @brief This is the Route Strategy class where we can use the interface to decide which type of route behaviour to implement
 * using a strategy pattern
 */
    class ParabolicRoute : public csci3081::RouteStrategy {
        public:
            /**
             * @brief This function 
             * allows the moving item to get the desired route. In this class, the function will return a 
             * route that follows the parabolic path
             * @return std::vector <std::vector<float>>
             */
            std::vector <std::vector<float>> GetRoute();
    };
} // namespace 3081