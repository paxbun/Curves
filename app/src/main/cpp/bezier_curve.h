//
// Created by freiy on 8/15/2018.
//

#ifndef CURVES_BEZIER_CURVE_H

struct BezierCurve
{
    float beg_x;
    float beg_y;
    float mid_x;
    float mid_y;
    float end_x;
    float end_y;
};

void GetCurvePoint(float * res, const struct BezierCurve * curve, float t);

#define CURVES_BEZIER_CURVE_H

#endif //CURVES_BEZIER_CURVE_H
