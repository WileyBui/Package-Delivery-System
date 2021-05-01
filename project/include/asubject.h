/**
 * @file ASubject
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <EntityProject/entity_observer.h>
#include <EntityProject/entity.h>
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the Abstract Subject class from which our subjects will inherit
 * Implements the Observer/subject pattern
 */
    class ASubject{
        public:
            /**
             * @brief Adds an observer to the list of observers for this subject
             * @param IEntityObserver* observer
             */
            void Attach(entity_project::IEntityObserver* observer);
            
            /**
             * @brief Deletes an observer from the list of observers for this subject
             * @param IEntityObserver* observer
             */
            void Detach(entity_project::IEntityObserver* observer);

            /**
             * @brief Getter function for the list of observers (mostly used in testing)
             * @return std::vector <entity_project::IEntityObserver*> list
             */
            std::vector <entity_project::IEntityObserver*> GetList();
            
            /**
             * @brief Sends out Notification to the observer watching this subject
             * @param picojson::value& event 
             * @param const entity_project::IEntity& entity
             */
            void Notify(picojson::value& event, const entity_project::IEntity& entity);

            /**
             * @brief Pure virtual function GetStatus that needs to implemented by derived
             * class based on their types of notification. This function creates the arguments 
             * required by Notify function and makes call to Notify function
             * @param picojson::value& event 
             * @param const entity_project::IEntity& entity
             */
            virtual void GetStatus() = 0;

            /**
             * @brief Pure virtual function Update that needs to implemented by derived
             * class based on their entity type. This function is used to advance time 
             * in the simulation. 
             * 
             * @param float dt refers to the  amount of time the update call should advance
             * the simulation by. For instance if a drone moves 1 unit of distance per unit 
             * of time, and Update is called with dt=.05, then the drone should move 
             * 1 * .05 = .05 units of distance.
             * 
             * Some things that should happen in the Update function: move drones, check if
             * packages have been delivered to customers, etc. 
             */
            virtual void Update(float dt) = 0;

        protected:
            /**
             * @brief List of pointers to the observers for this subject
             **/
            std::vector <entity_project::IEntityObserver*> list;
    };
} // namespace 3081