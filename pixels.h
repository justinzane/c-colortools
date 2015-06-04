/*****************************************************************************
  * @file         pixels.h
  * @author       Justin Zane Chudgar <justin@justinzane.com>
  * @version
  * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
  * @description  Temporary header, split from clrtools.h for readability.
  * @license      GPLv3
  ***************************************************************************/

#ifndef JZ_PIXELS_H
#define JZ_PIXELS_H

#include "colorspaces.h"
#include "defines.h"
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/** @def Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_ETA 0.008856452f
/** @def Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_KAPPA 903.2963f
/** @def Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_LAMBDA 7.787f
/** @def Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_MU 0.1379310f

/**
 * @defgroup PixelTypes PixelTypes
 * @note Though all of the float valued pixels are structurally identical,
 *       they are written as "different" structs for clarity and readability
 *       of dependent code.
 */

/**@ingroup PixelTypes
 * @brief CIE Lab colorspace pixel, with alpha, floats. */
typedef struct {
    float l;
    float a;
    float b;
    float alpha;
} lab_t;

/**@ingroup PixelTypes
 * @brief CIE Lhc colorspace pixel, with alpha, floats. */
typedef struct {
    float l;
    float h;
    float c;
    float a;
} lhc_t;

/**@ingroup PixelTypes
 * @brief CIE XYZ colorspace pixel, with alpha, floats */
typedef struct {
    float x;
    float y;
    float z;
    float a;
} xyz_t;

/**@ingroup PixelTypes
 * @brief Generic colorspace RGB, with alpha, floats. */
typedef struct {
    float r;
    float g;
    float b;
    float a;
} rgbf_t;

/**@ingroup PixelTypes
 * @brief Generic colorspace RGB, 8 bit per channel. */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb8_t;

/**@ingroup PixelTypes
 * @brief Generic colorspace RGB, with alpha, floats. */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} rgba8_t;

/**@ingroup PixelTypes
 * @brief Generic colorspace RGB, 16 bit per channel. */
typedef struct {
    uint16_t r;
    uint16_t g;
    uint16_t b;
} rgb16_t;

/**@ingroup PixelTypes
 * @brief Generic colorspace RGB, with alpha, 16 bit per channel. */
typedef struct {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t a;
} rgba16_t;

/* Pixel Functions ***********************************************************/

/**
 * @brief Convert a CIE Lab pixel to CIE Lhc space.
 * @param [in] lab  The Lab pixel.
 * @return          The Lhc pixel.
 * @note See http://www.brucelindbloom.com/index.html?Equations.html .
 */
lhc_t lab2lhc (const lab_t lab);

/**
 * @brief Convert a CIE Lhc pixel to a CIE Lab space.
 * @param [in] lhc  The Lhc pixel.
 * @return          The Lab pixel.
 * @note  See http://www.brucelindbloom.com/index.html?Equations.html .
 */
lab_t lhc2lab (const lhc_t lhc);

/**
 * @brief Convert a CIE Lab pixel to CIE XYZ space.
 * @param [in] lab  The pixel in Lab space.
 * @return          The pixel in XYZ space.
 */
xyz_t lab2xyz (const lab_t lab, const colorspace_t* cs);

/**
 * @brief           Conversion to RGB from CIE XYZ space
 * @param [in] xyz  The XYZ pixel.
 * @param [in] cs   The RGB variant desired.
 * @return          The RGB pixel.
 * @note: See http://www.brucelindbloom.com/Eqn_RGB_XYZ_Matrix.html .
 */
xyz_t rgbf2xvz (const rgbf_t rgb, const colorspace_t* cs);
/**
 * @brief           Conversion to RGB from CIE XYZ space
 * @param [in] xyz  The XYZ pixel.
 * @param [in] cs   The RGB variant desired.
 * @return          The RGB pixel.
 * @note: See http://www.brucelindbloom.com/Eqn_RGB_XYZ_Matrix.html .
 */
rgbf_t xyz2rgbf (const xyz_t xyz, const colorspace_t* cs);

/**
 * @brief Convert a CIE XYZ pixel to CIE Lab space, assuming a D50 illuminant.
 * @param [in] xyz  The pixel in XYZ space.
 * @return          The pixel in Lab space.
 * @note: See http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html .
 */
lab_t xyz2lab (const xyz_t xyz, const colorspace_t* cs);

#endif
