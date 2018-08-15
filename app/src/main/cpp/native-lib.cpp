#include <jni.h>
#include "helper.h"
#include "bezier_curve.h"
#include "cubic_hermite_curve.h"

extern "C" JNIEXPORT jfloatArray JNICALL
METHOD(MainActivity, getBezierCurve) (
    JNIEnv * env,
    jobject,
    jfloatArray arr
)
{
    auto len = env->GetArrayLength(arr);
    auto buf = env->GetFloatArrayElements(arr, 0);

    union {
        float copy[6];
        BezierCurve curve;
    } uni;

    for(int i = 0; i < 6 && i < len; i++)
        uni.copy[i] = buf[i];

    for(int i = len; i < 6; i++)
        uni.copy[i] = 0;

    jfloatArray rtn = env->NewFloatArray(20002);
    float rtn_buf[20002];

    for(int i = 0; i <= 10000; i++)
        GetCurvePoint(rtn_buf + 2*i, &(uni.curve), i/10000.f);

    env->SetFloatArrayRegion(rtn, 0, 20002, rtn_buf);
    return rtn;
}

extern "C" JNIEXPORT jfloatArray JNICALL
METHOD(MainActivity, getCubicHermiteCurve) (
    JNIEnv * env,
    jobject,
    jfloatArray arr
)
{
    auto len = env->GetArrayLength(arr);
    auto buf = env->GetFloatArrayElements(arr, 0);

    union {
        float copy[8];
        CubicHermiteCurve curve;
    } uni;

    for(int i = 0; i < 8 && i < len; i++)
        uni.copy[i] = buf[i];

    for(int i = len; i < 8; i++)
        uni.copy[i] = 0;

    jfloatArray rtn = env->NewFloatArray(20002);
    float rtn_buf[20002];

    for(int i = 0; i <= 10001; i++)
        GetCurvePoint(rtn_buf + 2*i, &(uni.curve), i/10000.f);

    env->SetFloatArrayRegion(rtn, 0, 20002, rtn_buf);
    return rtn;
}