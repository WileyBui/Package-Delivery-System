#include "delivery_simulation.h"
#include "entity_base.h"
#include "vector.h"
#include "json_helper.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	numEntities = 0;
	composite = new CompositeFactory();	
	AddFactory(new PackageFactory());
	AddFactory(new DroneFactory());
	AddFactory(new CustomerFactory());
}

DeliverySimulation::~DeliverySimulation() {
	delete composite;
	for (int i = 0; i<numEntities; i++){
		delete entities_.at(i);
	}
	entities_.clear();
}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
	IEntity* result = composite->CreateEntity(val); 
  	if (result!=NULL){
		numEntities++;
	}
	return result;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	composite->AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
  	entities_.push_back(entity);
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	this->graph = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	Customer* owner = dynamic_cast<Customer*> (dest);
	Package* pack = dynamic_cast<Package*> (package);
	pack->SetOwner(owner);
	owner->AddPackage(pack->GetId());
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { 
	return entities_; 
}

void DeliverySimulation::Update(float dt) {
	// Placeholder pointer
	EntityBase *entity;
	Package* package;
	Customer* owner;

	picojson::object val;
	for (int i = 0; i<numEntities; i++) {
		// Update dynamic entities_	
		entity = dynamic_cast<EntityBase*> (entities_.at(i));
		if (entity->IsDynamic()){
			entity->Update(dt);
		}
		// See if there is any undeliverered package
		if (entity->GetType() == "package") {
			package = dynamic_cast<Package*> (entities_.at(i));
			owner = package->GetOwner();
			if ((!package->IsDynamic()) && (owner!=NULL)) {
				Carrier* carrier = AvailableCarrier(package);
				if (carrier!=NULL){
					// Establish relationship between objects
					carrier->AddPackage(package);
					package->SetCarrier(carrier);
					
					// Adding path to package
					std::vector<vector<float>> path = graph->GetPath(carrier->GetPosition(),package->GetPosition());
					for (int j = 0; j<path.size(); j++){
						carrier->AddPosition(path.at(j));
					}
					// Adding path to customer
					path = graph->GetPath(package->GetPosition(),owner->GetPosition());
					for (int j = 0; j<path.size(); j++){
						carrier->AddPosition(path.at(j));
					}
				}
			}
		}
	}
}

Carrier* DeliverySimulation::AvailableCarrier(IEntity* package){
	float minDist;
	float instance;
	int carrierIndex = -1;
	picojson::object val;
	Carrier* carrier;
	EntityBase* entity;
	for (int j = 0; j<numEntities; j++){
		entity = dynamic_cast<EntityBase*> (entities_.at(j));
		if (entity->GetType() == "carrier") {
			carrier = dynamic_cast<Carrier*> (entity);
			if ((!carrier->HavePackage()) && (!carrier->BatteryDead())) {
			// if a carrier and is not busy with another package and have enough battery
			instance = carrier->DistanceBetween(package);
			if (carrierIndex == -1) {
				minDist = instance;
				carrierIndex = j;
			}
			else {
				if (minDist>instance){
					minDist = instance;
					carrierIndex = j;
				}
			}
			}
		}
	}	// find a carrier
	if (carrierIndex!=-1) {
		carrier = dynamic_cast<Carrier*> (entities_.at(carrierIndex));
		return carrier;
	}
	return NULL;
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
