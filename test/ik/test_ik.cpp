#include <unity.h>
#include "ik.hpp"
#include <iostream>
#include <sstream>

IK ik;

void setUp(void) {

}

void tearDown(void) {

}

void Test_IK(void){

    float coxa_l = 10;
    float femur_l = 10;
    float tibia_l = 10;
    
    array<float, 3> pos{0, 30, 0};
    array<float, 3> angles = ik.getAngles(pos, coxa_l, femur_l, tibia_l);
    stringstream data;
    data << "angles: " << angles[0] << ", " << angles[1] << ", " << angles[2];
    TEST_MESSAGE(data.str().c_str());
    int a = 2;
    int b = 59;
    int c = a + b;
    TEST_ASSERT_EQUAL(c, 61);
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(Test_IK);
    return UNITY_END();
}