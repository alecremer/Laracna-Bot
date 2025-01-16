#include <math.h>
#include <array>
#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

using namespace std;

class MathUtils {

public:

    static double degToRad(double deg) {
        return deg * M_PI / 180;
    }

    static double radToDeg(double rad) {
        return rad * 180 / M_PI;
    }

    static double cosDeg(double deg) {
        return cos(degToRad(deg));
    }

    static double sinDeg(double deg) {
        return sin(degToRad(deg));
    }

    static double tanDeg(double deg) {
        return tan(degToRad(deg));
    }

    static double acosDeg(double x) {
        return radToDeg(acos(x));
    }

    static double asinDeg(double x) {
        return radToDeg(asin(x));
    }

    static double atanDeg(double x) {
        return radToDeg(atan(x));
    }

    static double atan2Deg(double y, double x) {
        return radToDeg(atan2(y, x));
    }

    static double hypot(double x, double y) {
        return sqrt(x * x + y * y);
    }

    static array<float, 3> deg2rad_array(const array<float, 3>& angles_d){

        array<float, 3> rad;

        int idx = 0;
        for(auto& d : angles_d){
            rad[idx] = d*M_PI/180.0f;
            idx++;
        }

        return rad;

    }

    static array<float, 3> rad2deg_array(const array<float, 3>& angles_r){

        array<float, 3> deg;

        int idx = 0;
        for(auto& r : angles_r){
            deg[idx] = r*180.0f/M_PI;
            idx++;
        }

        return deg;

    }

    static float simplify_angle_rad(const float& angles_r){
        
        float angle = angles_r;

        while(angle > 2*M_PI){
            angle -= 2*M_PI;
        }
        return angle;
    }

    static float simplify_angle_deg(const float& angles_d){
        
        float angle = angles_d;

        while(angle > 360){
            angle -= 360;
        }
        return angle;
    }
    

};

#endif // MATH_UTILS_HPP