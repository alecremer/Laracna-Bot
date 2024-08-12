//
//  Create by Ale - 1/8/23
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

#ifndef IK_HPP
#define IK_HPP

#include <math.h>
#include <vector>
#include <array>
using namespace std;

class ik
{
private:
    float getP(float x, float z);
    float getAlpha(float L0, float L1, float P);
    float getBeta(float L0, float L1, float P);
    float getTheta0(float x, float y);
    float getTheta1(float x, float z, float alpha);
    float getTheta2(float beta);
    
public:
    std::array<float, 3> getAngles(const std::array<float, 3>& position, const float& L0, const float& L1);

};

#endif


