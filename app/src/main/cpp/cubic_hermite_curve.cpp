#include "cubic_hermite_curve.h"

void GetCurvePoint(float * res, const struct CubicHermiteCurve * curve, float t)
{
    if(!curve || !res)
        return;

    res[0]
            = (2*t*t*t - 3*t*t + 1) * curve->beg_x
              + (t*t*t - 2*t*t + t)   * curve->beg_tan_x
              + (-2*t*t*t + 3*t*t)    * curve->end_x
              + (t*t*t - t*t)         * curve->end_tan_x
            ;

    res[1]
            = (2*t*t*t - 3*t*t + 1) * curve->beg_y
              + (t*t*t - 2*t*t + t)   * curve->beg_tan_y
              + (-2*t*t*t + 3*t*t)    * curve->end_y
              + (t*t*t - t*t)         * curve->end_tan_y
            ;
}