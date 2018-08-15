#include "bezier_curve.h"

void GetCurvePoint(float * res, const struct BezierCurve * curve, float t)
{
    if(!curve || !res)
        return;

    res[0]
            = (1 - t) * (1 - t) * curve->beg_x
              + 2 * t * (1 - t) * curve->mid_x
              + t * t           * curve->end_x
              ;

    res[1]
            = (1 - t) * (1 - t) * curve->beg_y
              + 2 * t * (1 - t) * curve->mid_y
              + t * t           * curve->end_y
              ;
}