#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "charging_station_factory.h"
#include "charging_station.h"


namespace csci3081 {

IEntity* ChargingStationFactory::CreateEntity(const picojson::object& val){
    if (JsonHelper::GetString(val, "type") == "recharge_station") {
        return new ChargingStation(val);
    }
    return NULL;
}

} // end of namespace csci2081