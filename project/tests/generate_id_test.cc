#include "gtest/gtest.h"
#include "../include/generate_id.h"
#include <iostream>
#include <string>
#include <vector>

namespace csci3081 {

class GenerateIdTest : public ::testing::Test {
    protected:
        GenerateId id;
    public:
        void SetUp() {
            id = GenerateId();
        }
        void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(GenerateIdTest, ResetIdTests) {
    // restarts the ID
    ASSERT_EQ(0, id.ResetId()) << "ResetId does not match";
    id.ResetId();

    for (int i = 1; i < 100; i++){
        ASSERT_EQ(i, id.GenerateNewId()) << "GeneratenewId does not match";
    }

    ASSERT_EQ(0, id.ResetId()) << "ResetId does not match";
}

TEST_F(GenerateIdTest, GenerateNewIdTests) {
    id.ResetId();
    
    for (int i = 1; i < 100; i++){
        ASSERT_EQ(i, id.GenerateNewId()) << "GenerateNewId does not match";
    }
}

}

