/**
 * @file Route_Strategy
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the Route Strategy class where we can use the interface to decide which type of route behaviour to implement
 * using a strategy pattern
 */
    class RouteStrategy{
        public:
            /**
             * @brief Pure virtual function that will be overridden in derived classes. This function 
             * allows the moving item to get the desired route.
             * @return std::vector <std::vector<float>>
             */
            std::vector <std::vector<float>> GetRoute() = 0;
    };
} // namespace 3081