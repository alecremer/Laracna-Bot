// 
// Create by Ale on 1/8/23
// 
/*******************************************************
 * Spider IK
 * 
 * Spider leg:
 *       C
 *      / \
 *  L0 /   \
 *    /     \ L1
 *  AB       \
 *            \
 *             \  
 *           (x, y, z)
 * 
 * A       -> yaw axis
 * B and C -> pitch axis
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
*******************************************************/

#include <cmath>
#include <vector>
#include <array>
#include "ik.hpp"


float ik::getP(float x, float z){
    float p = sqrt(x*x + z*z);
    return p;
}
float ik::getAlpha(float L0, float L1, float P){

    float a = P*P + L0*L0 - L1*L1;
    float b = 2*P*L0;
    float alpha = acos(a/b);
    return alpha;
    
}
float ik::getBeta(float L0, float L1, float P){

    float a = L0*L0 + L1*L1 - P*P;
    float b = 2*L0*L1;
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
std::array<float, 3> ik::getAngles(const std::array<float, 3>& position, const float& L0, const float& L1){

    // split position vector
    const float x = position[0];
    const float y = position[1];
    const float z = position[2];

    // ----------------------------------------
    // calculate angles
    // ----------------------------------------

    const float theta0 = getTheta0(x, y);
    
    const float P = getP(x, z);
    const float alpha = getAlpha(L0, L1, P);
    const float theta1 = getTheta1(x, z, alpha);

    const float beta = getBeta(L0, L1, P);
    const float theta2 = getTheta2(beta);

    // ----------------------------------------

    // mount angle vector
    const std::array<float, 3> angles{{theta0, theta1, theta2}};

    return angles;

}