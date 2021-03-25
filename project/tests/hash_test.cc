#include "gtest/gtest.h"
#include "../include/hash.h"
#include <iostream>
#include <string>
#include <vector>

namespace csci3081 {

class HashTesting : public ::testing::Test {
    protected:
        Hash hash;
    public:
        void SetUp() {
            hash = Hash();
        }
        void TearDown() {}

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(HashTesting, ConstructorTesting) {
    ASSERT_EQ(0,hash.GetTotal()) << "Default Constructor or GetTotal not working";
    std::vector<int> checking;
    for (int i = 1; i<100; i++){
        checking.push_back(hash.nextNumber());
        ASSERT_EQ(i,hash.GetTotal()) << "Total Number does not match";
    }
    // Check for unique number
    for (int i = 0; i<checking.size(); i++){
        for (int j = 0; j<checking.size(); j++){
            if (j!=i) {
                ASSERT_FALSE(checking.at(i)==checking.at(j)) << "Non-unique number " << checking.at(i) << " at " << i << " and " << j;
            }
        }
    }
}

TEST_F(HashTesting, AddandContains) {
    Hash newHash;
    EXPECT_FALSE(newHash.Contain(1)) << "Contains is falty";
    newHash.Add(1);
    EXPECT_TRUE(newHash.Contain(1)) << "Contains or Add is falty";
}
}

