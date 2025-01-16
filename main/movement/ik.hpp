//
//  Create by Ale - 1/8/23
//


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
#ifdef TESTING
    #define ACCESS public
#else
    #define ACCESS private
#endif

#ifndef IK_HPP
#define IK_HPP

#include <math.h>
#include <vector>
#include <array>
using namespace std;

class IK
{

ACCESS:
 
    float getP(const float& x, const float& z);
    float getAlpha(const float& femur_length, const float& tibia_length, const float& P);
    float getBeta(const float& femur_length, const float& tibia_length, const float& P);
    float getTheta0(const float& x, const float& y);
    float getTheta1(const float& x, const float& z, const float& alpha);
    float getTheta2(const float& beta, const float& theta1);
    
public:
    float coxa_yaw_offset = 0;
    std::array<float, 3> getAngles(const std::array<float, 3>& position, const float& coxa_length, const float& femur_length, const float& tibia_length);

};

#endif


