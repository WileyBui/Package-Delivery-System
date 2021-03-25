#include <iostream>
#include "../include/hash.h"
#include <time.h>

namespace csci3081 {
Hash::Hash() {
    totalNumber = 0;
    range = 10000;
}

Hash::Hash(int range_) {
    totalNumber = 0;
}

int Hash::nextNumber() {
    srand(time(NULL));
    int num;
    bool sameNumber;
    while (true){
        num = rand() % range + 1;       // randomly generate a number between 1 and range
        sameNumber = Contain(num);      // Check if the number has already been generated
        if (sameNumber == false) {
            break;
        }
    }
    number.push_back(num);              // if not, then add it to the list and return it
    totalNumber++;
    return num;
}

bool Hash::Contain(int num){
    bool sameNumber = false;
    for (int i = 0; i<number.size(); i++){
            if (num==number.at(i)) {
                sameNumber = true;
                break;
            }
    }
    return sameNumber;
}

void Hash::Add(int num){
    bool exist = Contain(num);
    if (!exist){
        number.push_back(num);
        totalNumber++;
    }
}

int Hash::GetTotal() {
    return totalNumber;
}
}   // close namespace csci3081