/*****************************************************************************
 * @file         pixels.c
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

#include "pixels.h"

/** @brief Private utility function for XYZ -> Lab conversion. */
static inline float _lab_f (float val) {
    if (val <= LAB_ETA) {
        return (LAB_LAMBDA * val + LAB_MU);
    } else {
        return cbrtf (val);
    }
}

/* Pixel Functions ***********************************************************/

lhc_t lab2lhc (const lab_t lab) {
    lhc_t ret;
    ret.l = lab.l;
    ret.c = sqrtf (powf (lab.a, 2) + powf (lab.b, 2));
    if (lab.a == 0.0f) {
        ret.h = 0.0f;
    } else {
        ret.h = atanf (lab.b / lab.a);
        if (ret.h < 0.0f) {
            ret.h += 2.0f * M_PI_F;
        }
    }
    ret.a = lab.alpha;
    return ret;
}

lab_t lhc2lab (const lhc_t lhc) {
    lab_t ret;
    ret.l = lhc.l;
    ret.a = lhc.c * cosf (lhc.h);
    ret.b = lhc.c * sinf (lhc.h);
    ret.alpha = lhc.a;
    return ret;
}

xyz_t lab2xyz (const lab_t lab, const colorspace_t* cs) {
    xyz_t ret;
    float p = (lab.l + 16.0f) / 116.0f;
    ret.x = cs->whitepoint_xyz[0] * pow ((p + (lab.a / 500.0f)), 3.0f);
    ret.y = cs->whitepoint_xyz[0] * pow (p, 3.0f);
    ret.z = cs->whitepoint_xyz[0] * pow ((p - (lab.b / 200.0)), 3.0f);
    ret.a = lab.alpha;
    /* DEBUGGING */
    if (ret.y <= LAB_ETA) {
        printf ("Lab->XYZ conversion produced Y(%f) <= %f. FIXME!\n", ret.y, LAB_ETA);
    }
    return ret;
}

xyz_t rgbf2xvz (const rgbf_t rgb, const colorspace_t* cs) {
    xyz_t ret;
    ret.x = (rgb.r * cs->xyz2rgb_m[0] + rgb.g * cs->xyz2rgb_m[1] + rgb.b * cs->xyz2rgb_m[2]);
    ret.y = (rgb.r * cs->xyz2rgb_m[3] + rgb.g * cs->xyz2rgb_m[4] + rgb.b * cs->xyz2rgb_m[5]);
    ret.z = (rgb.r * cs->xyz2rgb_m[6] + rgb.g * cs->xyz2rgb_m[7] + rgb.b * cs->xyz2rgb_m[8]);
    return ret;
}

lab_t xyz2lab (const xyz_t xyz, const colorspace_t* cs) {
    lab_t ret;
    /* These are relative to the D50 whitepoint coordinates. */
    float xw = xyz.x / cs->whitepoint_xyz[0];
    float yw = xyz.y / cs->whitepoint_xyz[1];
    float zw = xyz.z / cs->whitepoint_xyz[2];
    /* The conditionals are due to psychovisual dark adaptation. */
    if (yw <= LAB_ETA) {
        ret.l = LAB_KAPPA * yw;
    } else {
        ret.l = 116.0f * cbrtf (yw) - 16.0f;
    }
    ret.a = 500.0f * (_lab_f (xw) - _lab_f (yw));
    ret.b = 200.0f * (_lab_f (yw) - _lab_f (zw));
    return ret;
}

rgbf_t xyz2rgbf (const xyz_t xyz, const colorspace_t* cs) {
    rgbf_t ret;
    ret.r = (xyz.x * cs->xyz2rgb_m[0] + xyz.y * cs->xyz2rgb_m[1] + xyz.z * cs->xyz2rgb_m[2]);
    ret.g = (xyz.x * cs->xyz2rgb_m[3] + xyz.y * cs->xyz2rgb_m[4] + xyz.z * cs->xyz2rgb_m[5]);
    ret.b = (xyz.x * cs->xyz2rgb_m[6] + xyz.y * cs->xyz2rgb_m[7] + xyz.z * cs->xyz2rgb_m[8]);
    return ret;
}
