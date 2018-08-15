//
// Created by freiy on 8/15/2018.
//

#ifndef CURVES_CUBIC_HERMITE_CURVE_H
#define CURVES_CUBIC_HERMITE_CURVE_H

struct CubicHermiteCurve
{
    float beg_x;
    float beg_y;
    float end_x;
    float end_y;
    float beg_tan_x;
    float beg_tan_y;
    float end_tan_x;
    float end_tan_y;
};

void GetCurvePoint(float * res, const struct CubicHermiteCurve * curve, float t);

#endif //CURVES_CUBIC_HERMITE_CURVE_H
