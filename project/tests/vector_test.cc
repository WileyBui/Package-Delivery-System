#include "gtest/gtest.h"
#include "../include/vector.h"
#include <iostream>
#include <string>

namespace csci3081 {

class VectorTesting : public ::testing::Test {
  protected:
    Vector2D allZeros2D,xnegzpos,xposzneg,decimal2D;
    Vector3D allZeros3D,v2,v3,decimal3D;
    float threshold = 1e-6;
 public:
  void SetUp() {
    allZeros2D = Vector2D(0,0);
    allZeros3D = Vector3D(0,0,0);
    xnegzpos = Vector2D(-5,4);
    xposzneg = Vector2D(5,-4);
    decimal2D = Vector2D(2.1,-3.4);
    v2 = Vector3D(-2,-1,4);
    v3 = Vector3D(-100,10,20);
    decimal3D = Vector3D(-1.6,-2.3,5.7);
  }
  void TearDown() {}

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(VectorTesting, ConstructorsTesting) {
  // Default Constructor for 2D
  Vector2D v1;
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  v1.Print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output,"<0.000,0.000>") << "Either Vector2D default constructor or Print Function Doesn't Work";

  // Constructor for 2D
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  allZeros2D.Print();
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1,"<0.000,0.000>") << "Either Vector2D constructor or Print Function Doesn't Work";

  // Constructor for 2D with decimal
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  decimal2D.Print();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2,"<2.100,-3.400>") << "Either Vector2D constructor or Print Function Doesn't Work for Decimal Number";

  // Copy constructor for 2D
  Vector2D iAmACopy2D(xnegzpos);
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  iAmACopy2D.Print();
  std::string output2b = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2b,"<-5.000,4.000>") << "Either Vector2D copy constructor or Print Function Doesn't Work";

  // Default Constructor for 2D
  Vector3D v2;
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  v2.Print();
  std::string output3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output3,"<0.000,0.000,0.000>") << "Either Vector3D default constructor or Print Function Doesn't Work";

  // Normal Vector3D Constructor
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  allZeros3D.Print();
  std::string output4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output4,"<0.000,0.000,0.000>") << "Either Vector3D constructor or Print Function Doesn't Work";

  // Normal Vector3D Constructor with decimal
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  decimal3D.Print();
  std::string output5 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output5,"<-1.600,-2.300,5.700>") << "Either Vector3D constructor or Print Function Doesn't Work for Decimal Number";
  
  // Copy constructor for 3D
  Vector3D iAmACopy3D(decimal3D);
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  iAmACopy3D.Print();
  std::string output6 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output6,"<-1.600,-2.300,5.700>") << "Either Vector3D copy constructor or Print Function Doesn't Work";  

  // Vector3D vector<float> argument
  std::vector<float> arg;
  arg.push_back(12.34);
  arg.push_back(13.34);
  arg.push_back(14.34);
  Vector3D vfloat(arg);
  EXPECT_FLOAT_EQ(vfloat.GetX(),arg.at(0)) << "Faulty vector constructor";
  EXPECT_FLOAT_EQ(vfloat.GetY(),arg.at(1)) << "Faulty vector constructor";
  EXPECT_FLOAT_EQ(vfloat.GetZ(),arg.at(2)) << "Faulty vector constructor";

}


TEST_F(VectorTesting, Getters) {
  EXPECT_LE(fabs(allZeros2D.GetX()-0),threshold) << "2D Getter X returns value bigger than threshold";
  EXPECT_LE(fabs(allZeros3D.GetX()-0),threshold) << "3D Getter X returns value bigger than threshold";
  EXPECT_LE(fabs(decimal2D.GetX()-2.1),threshold) << "2D Getter X returns value bigger than threshold for decimal numbers";
  EXPECT_LE(fabs(decimal3D.GetX()-(-1.6)),threshold) << "3D Getter X returns value bigger than threshold for decimal numbers";
  EXPECT_LE(fabs(decimal3D.GetY()-(-2.3)),threshold) << "3D Getter Y returns value bigger than threshold for decimal numbers";
  EXPECT_LE(fabs(decimal2D.GetZ()-(-3.4)),threshold) << "2D Getter Z returns value bigger than threshold for decimal numbers";
  EXPECT_LE(fabs(decimal3D.GetZ()-5.7),threshold) << "3D Getter Z returns value bigger than threshold for decimal numbers";
}


TEST_F(VectorTesting, Setters) {
  float threshold = 1e-6;
  allZeros2D.SetX(2.1);
  EXPECT_LE(fabs(allZeros2D.GetX()-2.1),threshold) << "Either 2D Getter X or Setter X returns value bigger than threshold";
  allZeros3D.SetX(-3.4);
  EXPECT_LE(fabs(allZeros3D.GetX()-(-3.4)),threshold) << "Either 3D Getter X or Setter X returns value bigger than threshold";
  allZeros3D.SetY(-2.9);
  EXPECT_LE(fabs(allZeros3D.GetY()-(-2.9)),threshold) << "Either 3D Getter Y or Setter Y returns value bigger than threshold";
  allZeros2D.SetZ(50);
  EXPECT_LE(fabs(allZeros2D.GetZ()-50),threshold) << "Either 2D Getter Z or Setter Z returns value bigger than threshold";
  allZeros3D.SetZ(100);
  EXPECT_LE(fabs(allZeros3D.GetZ()-100),threshold) << "Either 3D Getter Z or Setter Z returns value bigger than threshold";
}

TEST_F(VectorTesting, OverloadingOperator) {
  // ==
  EXPECT_TRUE(allZeros2D == Vector2D(0,0)) << "== does not work for 2D for all zeros";
  EXPECT_FALSE(allZeros2D == Vector2D(1,1)) << "== gives trivial result for 2D";
  EXPECT_TRUE(decimal2D == Vector2D(2.1,-3.4)) << "== does not work for 2D for decimal";
  EXPECT_TRUE(allZeros2D == allZeros3D) << "all zeros are not equal in 2D and 3D";
  EXPECT_FALSE(allZeros2D == Vector3D(0,1.0,0)) << "wrong equally between 3D and 2D";
  EXPECT_TRUE(decimal3D == Vector3D(-1.6,-2.3,5.7)) << "== does not work for 3D with decimal";

  // +
  EXPECT_TRUE(Vector2D(2.1,3.4) + Vector2D(-2.1,2.6) == Vector2D(0,6.0)) << "+ or == does not work for 2D";
  EXPECT_TRUE(Vector3D(2.1,3.4,5.4) + Vector3D(-2.1,2.6,0.0) == Vector3D(0,6.0,5.4)) << "+ or == does not work for 3D";

  // -
  EXPECT_TRUE(Vector2D(2.1,3.4) - Vector2D(-2.1,2.6) == Vector2D(4.2,0.8)) << "- or == does not work for 2D";
  EXPECT_FALSE(Vector3D(4.2,0.8,5.4)==Vector3D(4.2,0.8,5.0)) << "== for 3D is fuck up";
  EXPECT_FALSE((Vector3D(2.1,3.4,5.4) - Vector3D(-2.1,2.6,0.0)) == Vector3D(4.2,0.8,5.0)) << "- or == gives trivial answer for 3D";
  EXPECT_TRUE(Vector3D(2.1,3.4,5.4) - Vector3D(-2.1,2.6,0.0) == Vector3D(4.2,0.8,5.4)) << "- or == does not work for 3D";

  // /
  EXPECT_TRUE(Vector2D(2.1,3.4)/4 == Vector2D(0.525,0.850)) << "/ or == does not work for 2D";
  EXPECT_TRUE(Vector3D(0.8,3.4,5.4)/12.5 == Vector3D(0.8/12.5,3.4/12.5,5.4/12.5)) << "/ or == gives trivial answer for 3D";

  // *
  EXPECT_TRUE(Vector2D(2.1,3.4)*1.3 == Vector2D(2.1*1.3,3.4*1.3)) << "* or == does not work for 2D";
  EXPECT_TRUE(Vector3D(0.8,3.4,5.4)*0.08 == Vector3D(0.8*0.08,3.4*0.08,5.4*0.08)) << "* or == gives trivial answer for 3D";

}

TEST_F(VectorTesting, OtherVectorMath){
  // Dot Product
  EXPECT_LE(fabs(DotProduct(Vector2D(2.1,3.4),Vector2D(1.2,-2.4))-(2.1*1.2+3.4*(-2.4))),threshold) << "dot product does not work for 2D";
  EXPECT_TRUE(fabs(DotProduct(v2,v3)-(-2*(-100)+(-1)*10+4*20))<threshold) << "dot product does not work for 3D";

  // // Magnitude
  EXPECT_TRUE(fabs(Vector2D(2.1,3.4).Magnitude()-(sqrt(2.1*2.1+3.4*3.4)))<threshold) << "magnitude does not work for 2D";
  EXPECT_TRUE(fabs(v2.Magnitude()-sqrt(4+1+16))<threshold) << "magnitude does not work for 3D";

  // // Normalize
  EXPECT_TRUE(Vector2D(2.1,3.4).Normalize() == Vector2D(2.1,3.4)/(Vector2D(2.1,3.4).Magnitude())) << "normalize or magnitude does not work for 2D";
  EXPECT_TRUE(v2.Normalize() == v2/v2.Magnitude()) << "normalize or magnitude does not work for 3D";

  // Cross Product
  EXPECT_TRUE(CrossProduct(Vector3D(2,3,4),Vector3D(5,6,7))==Vector3D(-3,6,-3)) << "Cross Product is not functioning";
  EXPECT_FALSE(CrossProduct(Vector3D(2,3,4),Vector3D(1,1,1))==Vector3D(-3,6,-3)) << "Cross Product gives trivial result";
  
  // Distance
  EXPECT_LE(fabs(Distance(Vector3D(2,3,4),Vector3D(5,6,7))-5.1961524),threshold) << "Distance is not functioning for 3D";
  EXPECT_LE(fabs(Distance(decimal2D,xposzneg)-2.9614186),threshold) << "Distance is not functioning for 2D";
  EXPECT_FALSE(Distance(decimal2D,allZeros2D)==0) << "Distance gives a trivial result";
  EXPECT_FLOAT_EQ(Distance(Vector3D(100,253.883,431.292),Vector3D(2253.883,4938.292,2533.883)),5568.104575) << "Distance is not functioning for 3D";
} 

TEST_F(VectorTesting, toVectorFloat){
      // v2 = Vector3D(-2,-1,4);
    std::vector<float> hello;
    hello.push_back(-2);
    hello.push_back(-1);
    hello.push_back(4);
    std::vector<float> hi = toVectorFloat(v2);
    for (int i = 0; i<hi.size(); i++){
      EXPECT_FLOAT_EQ(hi.at(i),hello.at(i)) << "toVectorFloat is not functioning for 3D";
    }
}

}
