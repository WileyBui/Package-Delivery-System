#include "delivery_simulation.h"
#include "entity_base.h"
#include "vector.h"
#include "json_helper.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	numEntities = 0;
	composite = new CompositeFactory();	
	AddFactory(new PackageFactory());
	AddFactory(new CustomerFactory());
	AddFactory(new CarrierFactory());
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
	// Adding into subjects_ if entity is a derived class of ASubject
	ASubject* subject;
	if ((subject = dynamic_cast<ASubject*> (entity))!=0){
		subjects_.push_back(subject);
		for (int i = 0; i<observers_.size(); i++){
			subject->Attach(observers_.at(i));
		}
	}
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	this->graph = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	Customer* owner = dynamic_cast<Customer*> (dest);
	Package* pack = dynamic_cast<Package*> (package);
	pack->SetOwner(owner);
	pack->GetStatus();
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	EntityBase* entity;
	ASubject* subject;
	// Adding new observe into the tracked list
	observers_.push_back(observer);
	for (int i = 0; i<subjects_.size(); i++) {
		std::cout << i << std::endl;
		subjects_.at(i)->Attach(observer); 
	}
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	// Deleting from the observers list of DeliverySimulation
	observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
	// Deleting from each subjects
	EntityBase* entity;
	ASubject* subject;
	for (int i = 0; i<numEntities; i++) {
		entity = dynamic_cast<EntityBase*> (entities_.at(i));
		// Right now only carrier has GetStatus, later can change condition to != "customer"
		if (entity->GetType() == "carrier") {
			subject = dynamic_cast<ASubject*> (entity);
			subject->Detach(observer); 
		}
	}
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { 
	return entities_;
}

vector<vector<float>> DeliverySimulation::GetBeelinePath(std::vector<float> src, 
														 std::vector<float> dest,
														 float droneSpeed,
														 float dt) {

    vector<vector<float>> path;

	Vector3D srcPosition  = Vector3D(src);
	Vector3D destPosition = Vector3D(dest);

	bool hasFlownUp 		= false;
	bool hasFlownHorizontal = false;
	bool hasFlownDown 		= false;
	float heightToAvoidCollision = 400;

	Vector3D nextPosition = Vector3D(src); // sets to the current position, for now
	Vector3D flyToPosition;

	while (true) {
		if (!hasFlownUp) {
			if (nextPosition.GetY() >= heightToAvoidCollision) {
				// successfully moved up
				hasFlownUp = true;
			} else { 
				// move current position up until heightToAvoidCollision 
				flyToPosition = nextPosition;
				flyToPosition.SetY(heightToAvoidCollision);
			}
		}

		if (hasFlownUp && !hasFlownHorizontal) {
			if (nextPosition.IsWithinXandZRange(destPosition)) {
				// successfully flown to destination position (with y = heightToAvoidCollision)
				hasFlownHorizontal = true;
			} else {
				// move from source position (with y = heightToAvoidCollision)
				// to destination position (with y = heightToAvoidCollision)
				flyToPosition = destPosition;
				flyToPosition.SetY(heightToAvoidCollision);
			}
		}

		if (hasFlownHorizontal && !hasFlownDown) {
			if (Distance(nextPosition, destPosition) <= 5) {
				// successfully flown to destination position
				hasFlownDown = true;
			} else {
				// move toward the destination
				flyToPosition = destPosition;
			}
		}

		// calculate the direction
		Vector3D direction = flyToPosition - nextPosition;

		// normalize the direction
		direction = direction.Normalize();

		// calculate the velocity of the drone
		Vector3D velocity = direction * droneSpeed;

		// calculate the distance traveled over this time step: s = v*dt
		nextPosition = nextPosition + velocity * dt;

		path.push_back(toVectorFloat(nextPosition));

		if (hasFlownDown) {
			return path;
		}
	}
}

void DeliverySimulation::Update(float dt) {
	// Placeholder pointer
	EntityBase *entity;
	ASubject *subject;
	Package* package;
	Customer* owner;

	picojson::object val;
	for (int i = 0; i<numEntities; i++) {
		// Update dynamic entities_	
		entity = dynamic_cast<EntityBase*> (entities_.at(i));
		subject = dynamic_cast<ASubject*> (entities_.at(i));

		if (entity->IsDynamic()){
			// Only updating the carrier (drone & robot) and the package, customer doesn't need to move
			subject->Update(dt); 
		}
		// See if there is any undeliverered package
		if (entity->GetType() == "package") {
			package = dynamic_cast<Package*> (entities_.at(i));
			owner = package->GetOwner();
			if ((!package->IsDynamic()) && (owner!=NULL) && (package->GetCarrier()==NULL)) {
				Carrier* carrier = AvailableCarrier(package);
				if (carrier!=NULL){
					// Establish relationship between objects
					carrier->AddPackage(package);
					package->SetCarrier(carrier);
					
					// Adding path to package

					// Uses GetPath() route
					// std::vector<vector<float>> path = graph->GetPath(carrier->GetPosition(),
					// 												 package->GetPosition());
					
					// Uses GetBeelinePath() route
					std::vector<vector<float>> path = GetBeelinePath(carrier->GetPosition(),
																	 package->GetPosition(),
																	 carrier->GetSpeed(), 
																	 dt);
					
					carrier->SetRoute(path);
					package->GetStatus();
					carrier->GetStatus();
				}
			}
		}
		else if (entity->GetType() == "carrier") {
			Carrier* carrier = dynamic_cast<Carrier*> (entities_.at(i));
			if (carrier->HavePackage() && carrier->NextPosition() == carrier->GetPosition()){
				// Adding path to customer

				// Uses GetPath() route
				std::vector<vector<float>> path = graph->GetPath(carrier->GetPosition(),
																 carrier->GetPackage()->GetOwner()->GetPosition());
				
				// Uses GetBeelinePath() route
				// std::vector<vector<float>> path = GetBeelinePath(carrier->GetPosition(),
				// 												 carrier->GetPackage()->GetOwner()->GetPosition(),
				// 												 carrier->GetSpeed(),
				// 												 dt);
					
				carrier->SetRoute(path);
				carrier->GetPackage()->GetStatus();
				carrier->GetStatus();
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
