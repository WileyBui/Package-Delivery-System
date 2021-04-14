// /**
//  * @file Context.h
//  */
// /*******************************************************************************
//  * Includes
//  ******************************************************************************/
// #include <string>
// #include <vector>
// // #include "route_strategy.h"
// #include "json_helper.h"
// #include "beeline_route.h"
// #include "smart_route.h"
// #include "parabolic_route.h"

// namespace csci3081 {

// /*******************************************************************************
//  * Class Definitions
//  ******************************************************************************/
// /**
//  * @brief This is the Beeline Route class where we can use the strategy pattern to implement a Beeline route for carriers
//  */
//     class Context{
//         public:
//             /**
//              * @brief This is the default constructor of the Beeline Path Class
//              */
//             Context(RouteStrategy* strategy){routeStrategy = strategy;}
//             /**
//              * @brief This function 
//              * allows the moving item to get the desired route. In this class, the function will return a 
//              * route that follows the Beeline path
//              * @param IGraph* graph
//              * @param std::vector<float> location
//              * @param std::vector<float> dest
//              * @return std::vector <std::vector<float>>
//              */
//             std::vector<std::vector<float>> executeStrategy()
//             private:
//             RouteStrategy* routeStrategy;
//     };
// } // namespace 3081