#include "../include/asubject.h"

namespace csci3081 {
    void ASubject::Attach(IEntityObserver* observer){
        list.push_back(observer);
    }
    void ASubject::Detach(IEntityObserver* observer){
        list.erase(std::remove(list.begin(), list.end(), observer), list.end());
    }
    void ASubject::Notify(std::string name, std::string value){
        for (IEntityObserver* observer : list){
            if (observer != NULL)
                observer ->Update(name, value);
        }
    }

} // namespace 3081