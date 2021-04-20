#include "gtest/gtest.h"
#include "../include/battery.h"
#include <iostream>
#include <string>
#include <vector>

namespace csci3081 {

class BatteryTesting : public ::testing::Test {
    protected:
        std::vector<Battery> myBattery;
        Battery negativeLife;
        Battery greaterMaxLife;
        Battery half;
        Battery normal;
    public:
        void SetUp() {
            for (int i = 0; i<5; i++){
                myBattery.push_back(Battery());
            }
            negativeLife = Battery(-100);
            greaterMaxLife = Battery(20000);
            normal = Battery(5000);
        }
        void TearDown() {}

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BatteryTesting, ConstructorTesting) {
    // Check if Default Construction Generate Unique ID
    for (int i = 0; i<5; i++){
        EXPECT_TRUE(myBattery.at(i).GetRemainingLife() == 0) << "Remaining Life for Default Constuctor Faulty";
        for (int j = 0; j <5; j++){
            if (i!=j){
                ASSERT_FALSE(myBattery.at(i).GetId() == myBattery.at(j).GetId()) << "Non-unique ID for Battery"; 
            }
        }
    }
}

TEST_F(BatteryTesting, Getters) {
    // Check remainingLife condition between 0 and 10000
    EXPECT_FLOAT_EQ(negativeLife.GetRemainingLife(),0) << "GetRemainingLife or Constructor is faulty for negative";
    EXPECT_FLOAT_EQ(greaterMaxLife.GetRemainingLife(),10000) << "GetRemainingLife or Constructor is faulty for over";
    EXPECT_FLOAT_EQ(normal.GetRemainingLife(),5000) << "GetRemainingLife or Constructor is faulty for normal";
    
    // Check displayBar
    EXPECT_TRUE(negativeLife.GetDisplayBar() == 0) << "GetDisplayBar or Constructor is faulty for negative";
    EXPECT_TRUE(greaterMaxLife.GetDisplayBar() == 5) << "GetDisplayBar or Constructor is faulty for over";
    EXPECT_TRUE(normal.GetDisplayBar() == 2) << "GetRemainingLife or Constructor is faulty for normal";

    // Check IsDead
    EXPECT_TRUE(negativeLife.IsDead()) << "IsDead or Constructor is faulty for negative";
    EXPECT_FALSE(greaterMaxLife.IsDead()) << "IsDead or Constructor is faulty for over";
    EXPECT_FALSE(normal.IsDead()) << "IsDead or Constructor is faulty for normal";
}

TEST_F(BatteryTesting, DisplayBar){
       // Check displayBar
    EXPECT_TRUE(negativeLife.GetDisplayBar() == 0) << "GetDisplayBar or Constructor is faulty for negative";
    EXPECT_TRUE(greaterMaxLife.GetDisplayBar() == 5) << "GetDisplayBar or Constructor is faulty for over";
    EXPECT_TRUE(normal.GetDisplayBar() == 2) << "GetRemainingLife or Constructor is faulty for normal";
}

TEST_F(BatteryTesting, Depleting) {
    // Check remainingLife condition between 0 and 10000
    // sec > remaining
    negativeLife.Depleting(1000);
    EXPECT_TRUE(negativeLife.GetRemainingLife() == 0) << "Depleting is faulty for negative";
    EXPECT_TRUE(negativeLife.IsDead()) << "Depleting is faulty for negative";
    
    // Depleting 
    // negative sec
    normal.Depleting(-2000);
    EXPECT_TRUE(normal.GetRemainingLife() == 5000) << "Depleting is faulty for negative";
    EXPECT_FALSE(normal.IsDead()) << "Depleting is faulty for negative";
    
    // more than remainingLife
    normal.Depleting(10000);
    EXPECT_TRUE(normal.GetRemainingLife() == 0) << "Depleting is faulty for big sec";
    EXPECT_TRUE(normal.IsDead()) << "Depleting is faulty for big sec";
    
    // regular depleting
    EXPECT_FLOAT_EQ(greaterMaxLife.GetRemainingLife(), 10000) << "Depleting is faulty for normal sec";
    greaterMaxLife.Depleting(9660.200000000000);
    EXPECT_TRUE(greaterMaxLife.GetRemainingLife()-339.8<0.0001) << "Depleting is faulty for normal sec";
    greaterMaxLife.Depleting(-1000000);
    EXPECT_FALSE(greaterMaxLife.IsDead()) << "Depleting is faulty for normal sec";
}

TEST_F(BatteryTesting, Charging){
    // Charging 
    // negative sec
    normal.Charging(-2000);
    EXPECT_TRUE(normal.GetRemainingLife() == 5000) << "Depleting is faulty for negative";
    EXPECT_FALSE(normal.IsDead()) << "Depleting is faulty for negative";
    
    // more than remainingLife
    normal.Charging(10000);
    EXPECT_TRUE(normal.GetRemainingLife() == 10000) << "Depleting is faulty for big sec";
    EXPECT_FALSE(normal.IsDead()) << "Depleting is faulty for big sec";
    
    // regular charging
    negativeLife.Charging(5000);
    EXPECT_TRUE(greaterMaxLife.GetRemainingLife() > 5000) << "Depleting is faulty for normal sec";
    EXPECT_FALSE(greaterMaxLife.IsDead()) << "Depleting is faulty for normal sec";
}

TEST_F(BatteryTesting, TimeToFull){
    EXPECT_TRUE(greaterMaxLife.TimeToFull() == 0) << "TimeToFull does not work";
    EXPECT_TRUE(normal.TimeToFull() == 5000) << "TimeToFull does not work";
    EXPECT_TRUE(negativeLife.TimeToFull() == 10000) << "TimeToFull does not work"; 
}
}
