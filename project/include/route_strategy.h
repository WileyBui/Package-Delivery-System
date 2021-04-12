/**
 * @file Route_Strategy
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
// #include <EntityProject/facade/graph.h>
#include <EntityProject/facade/delivery_system.h>

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
             * @param IGraph* graph
             * @param std::vector<float> location
             * @param std::vector<float> dest
             * @return std::vector <std::vector<float>>
             */
            virtual std::vector <std::vector<float>> GetRoute(IGraph* graph, std::vector<float> location, std::vector<float> dest) = 0;
    };
} // namespace 3081