#include "entity_base.h"
#include "json_helper.h"
#include "package_factory.h"
#include "package.h"

namespace csci3081 {

IEntity* PackageFactory::CreateEntity(const picojson::object& val){
    if (JsonHelper::GetString(val, "type") == "package") {
        return new Package(val);
    }
    return NULL;
}

} // end of namespace csci2081