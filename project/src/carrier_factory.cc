#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "carrier_factory.h"

namespace csci3081 {
CarrierFactory::CarrierFactory() {
    AddFactory(new DroneFactory());
    AddFactory(new RobotFactory());
};

CarrierFactory::~CarrierFactory() {
    for (int i = 0; i<carrierFactories.size(); i++){
        delete carrierFactories.at(i);
    }
    carrierFactories.clear();
}

void CarrierFactory::AddFactory(IEntityFactory* n) {
    carrierFactories.push_back(n);
}

IEntity* CarrierFactory::CreateEntity(const picojson::object& val){
    IEntity* result = NULL;
    for (int i = 0; i<carrierFactories.size(); i++){
        result = carrierFactories.at(i)->CreateEntity(val);
        if (result!=NULL){
            return result;
        }
    }
    return NULL;
}

} // end of namespace csci2081