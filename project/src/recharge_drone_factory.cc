// #include "delivery_simulation.h"
// #include "entity_base.h"
// #include "json_helper.h"
// #include "recharge_drone_factory.h"
// #include "drone.h"


// namespace csci3081 {

// IEntity* RechargeDroneFactory::CreateEntity(const picojson::object& val){
//     if (JsonHelper::GetString(val, "type") == "recharge_drone") {
//         return new RechargeDrone(val);
//     }
//     return NULL;
// }

// } // end of namespace csci2081