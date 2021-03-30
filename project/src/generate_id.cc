#include <string>
#include "generate_id.h"
#include <string>
#include <iostream>

namespace csci3081 {

int GenerateId::id = 0;

int GenerateId::GenerateNewId() {
    return ++id;
}

}  // namespace csci3081