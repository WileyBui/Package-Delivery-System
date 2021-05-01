#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "customer_factory.h"
#include "customer.h"


namespace csci3081 {

IEntity* CustomerFactory::CreateEntity(const picojson::object& val){
    if (JsonHelper::GetString(val, "type") == "customer") {
        return new Customer(val);
    }
    return NULL;
}

} // end of namespace csci2081
