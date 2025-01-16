#define TESTING


#include <unity.h>
#include "ik.hpp"
#include <iostream>
#include <sstream>

#define TESTING

IK ik;

void setUp(void) {

}

void tearDown(void) {

}

array<float, 3> deg2rad_array(const array<float, 3>& angles_d){

    array<float, 3> rad;

    int idx = 0;
    for(auto& d : angles_d){
        rad[idx] = d*M_PI/180.0f;
        idx++;
    }

    return rad;

}

array<float, 3> rad2deg_array(const array<float, 3>& angles_r){

    array<float, 3> deg;

    int idx = 0;
    for(auto& r : angles_r){
        deg[idx] = r*180.0f/M_PI;
        idx++;
    }

    return deg;

}

array<float, 3> get_pos_from_angles(const float& coxa_l, const float& femur_l, const float& tibia_l, const array<float, 3>& angles){

    array<float, 3> pos;
    
    float xy_footprint = coxa_l + femur_l*cos(angles[1]) + tibia_l*cos(angles[2]);
    
    pos[0] = xy_footprint*cos(angles[0]);
    pos[1] = xy_footprint*sin(angles[0]);
    pos[2] = femur_l*sin(angles[1]) - tibia_l*sin(angles[2]);

    return pos;
}

// array<float, 3> get_angles_from_IK(const float& coxa_l, const float& femur_l, const float& tibia_l, const array<float, 3>& desired_angles_d){
void get_angles_from_IK(const float& coxa_l, const float& femur_l, const float& tibia_l, const array<float, 3>& desired_angles_d, const bool& log=false){

    array<float, 3> desired_angles = deg2rad_array(desired_angles_d);
    array<float, 3> pos = get_pos_from_angles(coxa_l, femur_l, tibia_l, desired_angles);
    array<float, 3> angles = ik.getAngles(pos, coxa_l, femur_l, tibia_l);
    array<float, 3> angles_d = rad2deg_array(angles);
    array<float, 3> out_pos = get_pos_from_angles(coxa_l, femur_l, tibia_l, angles);

    stringstream data;
    
    if(log){

        data << "angles        : " << angles_d[0] << ", " << angles_d[1] << ", " << angles_d[2];
        TEST_MESSAGE(data.str().c_str());

        data.str("");
        data.clear();
        data << "desired_angles: " << desired_angles_d[0] << ", " << desired_angles_d[1] << ", " << desired_angles_d[2];
        TEST_MESSAGE(data.str().c_str());

        data.str("");
        data.clear();
        data << "pos    : " << pos[0] << ", " << pos[1] << ", " << pos[2];
        TEST_MESSAGE(data.str().c_str());
        
        data.str("");
        data.clear();
        data << "out_pos: " << out_pos[0] << ", " << out_pos[1] << ", " << out_pos[2];
        TEST_MESSAGE(data.str().c_str());

    }

    float arr_exp[3]{pos[0], pos[1], pos[2]};
    float arr_act[3]{out_pos[0], out_pos[1], out_pos[2]};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(arr_exp, arr_act, 3);

    // return angles;


}

void test_ik(const float& coxa_l, const float& femur_l, const float& tibia_l, const array<float, 3>& pos){
    array<float, 3> angles = ik.getAngles(pos, coxa_l, femur_l, tibia_l);
    array<float, 3> out_pos = get_pos_from_angles(coxa_l, femur_l, tibia_l, angles);
    float arr_exp[3]{pos[0], pos[1], pos[2]};
    float arr_act[3]{out_pos[0], out_pos[1], out_pos[2]};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(arr_exp, arr_act, 3);

}

void test_get_P(float x, float z, float expec){
    float P = ik.getP(x, z);
    TEST_ASSERT_EQUAL(expec, P);
}

void test_get_alpa(const float& coxa_l, const float& femur_l, const float& P, float expec){
    float alpha = ik.getAlpha(coxa_l, femur_l, P);
    TEST_ASSERT_EQUAL(expec, alpha);
}

int main(void) {
    UNITY_BEGIN();
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 45, 45});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 45, -45});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 30, 10});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 30, -10});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 10, 30});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 20, {0, 10, -30});});
    // RUN_TEST([]{get_angles_from_IK(10, 10, 10, {45, 45, 45}, true);});
    // RUN_TEST([]{test_ik(10, 10, 10, {17.0711f, 17.0711f, 0});});
    // RUN_TEST([]{test_get_P(10, 5, 11.18033f);});
    // RUN_TEST([]{test_get_P(13, -4, 13.601470f);});
    // RUN_TEST([]{test_get_alpa(10, 10, 10, );});
    return UNITY_END();
}