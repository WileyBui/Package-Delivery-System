#include "entity_base.h"
#include "json_helper.h"
#include "robot_factory.h"
#include "robot.h"

namespace csci3081 {

IEntity* RobotFactory::CreateEntity(const picojson::object& val){
    if (JsonHelper::GetString(val, "type") == "robot") {
        return new Robot(val);
    }
    return NULL;
}

} // end of namespace csci3081