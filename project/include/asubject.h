/**
 * @file ASubject
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <EntityProject/entity_observer.h>

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
            void Attach(IEntityObserver* observer);
            /**
             * @brief Deletes an observer from the list of observers for this subject
             * @param IEntityObserver* observer
             */
            void Detach(IEntityObserver* observer);
            /**
             * @brief Sends out Notification to the observer watching this subject
             * @param std::string name
             * @param std::string value
             */
            void Notify(std::string name, std::string value);
        private:
            /**
             * @brief List of pointers to the observers for this subject
             **/
            std::vector <IEntityObserver*> list;
    };
} // namespace 3081