/*****************************************************************************
 * @file         colorspaces.c
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

#include "colorspaces.h"

// void get_whitepoint_xyz (const int cs, float* wp) {
//    switch (cs) {
//        case Adobe_RGB:
//            float foo = Adobe_RGB_WP_XYZ[0];
//            float tmp[3] = Adobe_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Apple_RGB:
//            float tmp[3] = Apple_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Best_RGB:
//            float tmp[3] = Best_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Beta_RGB:
//            float tmp[3] = Beta_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Bruce_RGB:
//            float tmp[3] = Bruce_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case CIE_RGB:
//            float tmp[3] = CIE_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case ColorMatch_RGB:
//            float tmp[3] = ColorMatch_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Don_RGB:
//            float tmp[3] = Don_RGB_4_WP_XYZ;
//            wp = tmp;
//            break;
//        case ECI_RGB:
//            float tmp[3] = ECI_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case Ekta_Space_PS5:
//            float tmp[3] = Ekta_Space_PS5_WP_XYZ;
//            wp = tmp;
//            break;
//        case NTSC_RGB:
//            float tmp[3] = NTSC_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case PAL_RGB:
//            float tmp[3] = PAL_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case ProPhoto_RGB:
//            float tmp[3] = ProPhoto_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case SMPTEC_RGB:
//            float tmp[3] = SMPTEC_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case sRGB:
//            float tmp[3] = sRGB_WP_XYZ;
//            wp = tmp;
//            break;
//        case WideGamut_RGB:
//            float tmp[3] = WideGamut_RGB_WP_XYZ;
//            wp = tmp;
//            break;
//        default:
//            printf ("Doh. Bad colorspace specified. %s:%d\n", __FILE__, __LINE__);
//            float tmp[3] = UNREAL_RGB_WP_XYZ;
//    }
//    return;
//}
