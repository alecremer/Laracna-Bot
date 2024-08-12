// 
// Create by Ale on 1/8/23
// 
/*******************************************************
 * Spider IK
 * 
 * Spider leg:
 *            C
 *     femur / \
 *       L0 /   \
 *         /     \ L1 tibia
 *  A-----B       \
 *    L2           \
 *  coxa            \  
 *                (x, y, z)
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
#include <vector>
#include <array>
#include "ik.hpp"


float ik::getP(float x, float z){
    float p = sqrt(x*x + z*z);
    return p;
}
float ik::getAlpha(float femur_length, float tibia_length, float P){

    float a = P*P + femur_length*femur_length - tibia_length*tibia_length;
    float b = 2*P*femur_length;
    float alpha = acos(a/b);
    return alpha;
    
}
float ik::getBeta(float femur_length, float tibia_length, float P){

    float a = femur_length*femur_length + tibia_length*tibia_length - P*P;
    float b = 2*femur_length*tibia_length;
    float beta = acos(a/b);
    return beta;
    
}
float ik::getTheta0(float x, float y){
    float theta0 = atan(y/x);
    return theta0;
}
float ik::getTheta1(float x, float z, float alpha){
    
    float gama = atan(z/x);
    float theta1 = gama + alpha;
    return theta1;

}
float ik::getTheta2(float beta){

    float theta2 = 2*M_PI - beta;
    return theta2;

}
std::array<float, 3> ik::getAngles(const std::array<float, 3>& position, const float& coxa_length, const float& femur_length, const float& tibia_length){

    // split position vector
    const float x_original = position[0];
    const float y_original = position[1];

    // calculate first angle and transform to plain ref
    const float theta0 = getTheta0(x_original, y_original);
    const float x = x_original - coxa_length*cos(theta0)*cos(coxa_yaw_offset);
    const float z = position[2] - coxa_length*sin(coxa_yaw_offset);
    
    // ----------------------------------------
    // calculate angles
    // ----------------------------------------

    
    const float P = getP(x, z);
    const float alpha = getAlpha(femur_length, tibia_length, P);
    const float theta1 = getTheta1(x, z, alpha);

    const float beta = getBeta(femur_length, tibia_length, P);
    const float theta2 = getTheta2(beta);

    // ----------------------------------------

    // mount angle vector
    const std::array<float, 3> angles{{theta0, theta1, theta2}};

    return angles;

}