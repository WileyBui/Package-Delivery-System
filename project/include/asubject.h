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
             * @brief Sends out Notification to the observer watching this subject
             * @param picojson::value& event 
             * @param const entity_project::IEntity& entity
             */
            void Notify(picojson::value& event, const entity_project::IEntity& entity);
        private:
            /**
             * @brief List of pointers to the observers for this subject
             **/
            std::vector <entity_project::IEntityObserver*> list;
    };
} // namespace 3081