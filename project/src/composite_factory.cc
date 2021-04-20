#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "composite_factory.h"

namespace csci3081 {
CompositeFactory::CompositeFactory() {};

CompositeFactory::~CompositeFactory() {
    for (int i = 0; i<factories.size(); i++){
        delete factories.at(i);
    }
    factories.clear();
}

void CompositeFactory::AddFactory(IEntityFactory* n) {
    factories.push_back(n);
}

IEntity* CompositeFactory::CreateEntity(const picojson::object& val){
    IEntity* result = NULL;
    for (int i = 0; i<factories.size(); i++){
        result = factories.at(i)->CreateEntity(val);
        if (result!=NULL){
            return result;
        }
    }
    return NULL;
}

} // end of namespace csci2081