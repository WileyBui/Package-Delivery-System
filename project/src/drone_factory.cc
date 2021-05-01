#include "entity_base.h"
#include "json_helper.h"
#include "drone_factory.h"
#include "drone.h"
#include <iostream>
namespace csci3081 {

IEntity* DroneFactory::CreateEntity(const picojson::object& val){
    if (JsonHelper::GetString(val, "type") == "drone") {
        return new Drone(val);
    }
    return NULL;
}

} // end of namespace csci2081