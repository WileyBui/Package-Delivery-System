#include "../include/asubject.h"

namespace csci3081 {
    void ASubject::Attach(entity_project::IEntityObserver* observer){
        list.push_back(observer);
    }
    void ASubject::Detach(entity_project::IEntityObserver* observer){
        list.erase(std::remove(list.begin(), list.end(), observer), list.end());
    }
    std::vector <entity_project::IEntityObserver*> ASubject::GetList(){
        return list;
    }
    void ASubject::Notify(picojson::value& event, const entity_project::IEntity& entity){
        for (entity_project::IEntityObserver* observer : list){
            if (observer != NULL)
                observer->OnEvent(event, entity);
        }
    }

} // namespace 3081