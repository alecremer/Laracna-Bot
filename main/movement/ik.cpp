
/*******************************************************
 * Spider IK
 * 
 *  Spider leg:
 *  
 *  z
 *             C
 *      femur / \
 *        L0 /   \
 *          /     \ L1 tibia
 *   A-----B       \
 *     L2           \
 *   coxa            \  
 *                 (x, y, z)
 *  
 *  femur-tibia plane
 *  
 *  ^z
 *  |    C_____
 *  |   / \ t2    t1 = theta1
 *  |  /   \      t2 = theta2
 *  | / t1  \ 
 *  |B-------\---------------------> x`
 *  |         \
 *  |          \  
 *  |        (x, y, z)
 * 
 *  Top view
 * 
 *            ^ y 
 *            |    /
 *            |   /
 *            |  /
 *            | /
 *            |/ theta0
 * ------------------------> x
 *            | Leg base
 *
 * A       -> yaw axis
 * B and C -> pitch axis
 * 
 *  -- Without coxa
 * 
 * A - theta_0 (yaw)    = atg(y/x)
 * B - theta_1 (pitch)  = gama +- alpha 
 * C - theta_2 (pitch)  = 180° - beta
 * alpha    = acos((P² + L0² - L1²)/(2PL0))
 * beta     = acos((L0² + L1² -P²)/(2L0L1))
 * gama     = atg(z/x)
 * 
 * x, y -> footprint
 * z    -> height
 * 
 * With coxa
 * 
 * pitch_coxa -> mechanical joint variation
 * 
 * x_real = x + L2*cos(yaw_coxa)*cos(pitch_of_coxa)
 * y_real = y + L2*sin(yaw_coxa)*cos(pitch_coxa)
 * z_real = z + L2*cos(yaw_coxa)*sin(pitch_coxa)
 * 
*******************************************************/

#include <cmath>
#include <math.h>
#include <vector>
#include <array>
#include "ik.hpp"
// #include "data_manager.hpp"
#include <iostream>
#include <string>
#include <sstream>

float IK::getP(const float& x, const float& z){
    float p = sqrt(x*x + z*z);
    return p;
}
float IK::getAlpha(const float& femur_length, const float& tibia_length, const float& P){

    float a = P*P + femur_length*femur_length - tibia_length*tibia_length;
    float b = 2*P*femur_length;
    float ratio = a / b;
    if (ratio < -1.0) ratio = -1.0;
    if (ratio > 1.0) ratio = 1.0;
    float alpha = acos(ratio);
    return alpha;
    
}
float IK::getBeta(const float& femur_length, const float& tibia_length, const float& P){

    float a = femur_length*femur_length + tibia_length*tibia_length - P*P;
    float b = 2*femur_length*tibia_length;
    float ratio = a / b;
    if (ratio < -1.0) ratio = -1.0;
    if (ratio > 1.0) ratio = 1.0;
    float beta = acos(ratio);
    return beta;
    
}
float IK::getTheta0(const float& x, const float& y){
    float theta0 = atan2(y, x);
    return theta0;
}
float IK::getTheta1(const float& x, const float& z, const float& alpha){
    
    float gama = atan2(z, x);
    // float hip1 = gama + alpha;
    // float hip2 = gama + alpha;
    // float theta1 = (alpha >= gama)? gama - alpha 
    // float theta1 = (gama < 0)? alpha - gama : alpha + gama; 
    float theta1_hip0 = alpha - gama; 
    float theta1_hip1 = alpha + gama;
    float theta1 = theta1_hip0; 
    
    if(theta1_hip0 < 0) theta1 = theta1_hip1;
    else if(theta1_hip1 < theta1_hip0) theta1 = theta1_hip1;

    return theta1_hip1;

}
float IK::getTheta2(const float& beta, const float& theta1){

    // float theta2 = M_PI - beta -theta1;
    float theta2 = M_PI - beta;
    return theta2;

}
// float IK::getTheta2(const float& beta){

//     float theta2 = 2*M_PI - beta;
//     return theta2;

// }
std::array<float, 3> IK::getAngles(const std::array<float, 3>& position, const float& coxa_length, const float& femur_length, const float& tibia_length){

    // split position vector
    float x_original = position[0];
    float y_original = position[1];
    

    // calculate first angle and transform to plain ref
    float theta0 = getTheta0(x_original, y_original);

    // float x = x_original - coxa_length*cos(theta0)*cos(coxa_yaw_offset);
    float x = sqrt(x_original*x_original + y_original*y_original) - coxa_length;
    float z = position[2] - coxa_length*sin(coxa_yaw_offset);

    
    std::ostringstream data;
    data << "original x, y: " << x_original << ", " << y_original << "\n";
    data << "x, z: " << x << ", " << z << "\n";
    
    // ----------------------------------------
    // calculate angles
    // ----------------------------------------

    
    float P = getP(x, z);
    float alpha = getAlpha(femur_length, tibia_length, P);
    float theta1 = getTheta1(x, z, alpha);

    const float beta = getBeta(femur_length, tibia_length, P);
    const float theta2 = getTheta2(beta, theta1);

    data << "P: " << P << "\n";
    data << "alpha: " << alpha << "\n";
    data << "length c, f, t: " << coxa_length << ", " << femur_length << ", " << tibia_length << "\n";
    data << "theta1: " << theta1 << "\n";
    data << "beta: " << beta << "\n";
    data << "theta2: " << theta2 << "\n";
    data << "--------------------------------------" << "\n";


    // ----------------------------------------

    // mount angle vector
    const std::array<float, 3> angles{{theta0, theta1, theta2}};

    // DataManager::write_file(data.str(), "log3");
    return angles;

}