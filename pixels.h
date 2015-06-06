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

/** @brief Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_ETA 0.008856452f

/** @brief Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_KAPPA 903.2963f

/** @brief Constant for Lab from XYZ conversion; see
 * (http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html). */
#define LAB_LAMBDA 7.787f

/** @brief Constant for Lab from XYZ conversion; see
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
    float l;     /**< Lightness */
    float a;     /**< GRN - MAG */
    float b;     /**< YEL - BLU */
    float alpha; /**< Alpha *.
} lab_t;

/**@ingroup PixelTypes
* @brief CIE Lhc / Lch colorspace pixel, with alpha, floats. */
    typedef struct {
        float l; /**< Lightness */
        float h; /**< Hue */
        float c; /**< Chroma */
        float a; /**< Lightness */
    } lhc_t;

    /**@ingroup PixelTypes
     * @brief CIE XYZ colorspace pixel, with alpha, floats */
    typedef struct {
        float x; /**< Longwave, ~R */
        float y; /**< Midwave, ~G */
        float z; /**< Shortwave, ~B */
        float a; /**< Alpha */
    } xyz_t;

    /**@ingroup PixelTypes
     * @brief Generic colorspace RGB, with alpha, floats. */
    typedef struct {
        float r; /**< Red */
        float g; /**< Green */
        float b; /**< Blue */
        float a; /**< Alpha */
    } rgbf_t;

    /**@ingroup PixelTypes
     * @brief Generic colorspace RGB, 8 bit per channel. */
    typedef struct {
        uint8_t r; /**< Red */
        uint8_t g; /**< Green */
        uint8_t b; /**< Blue */
    } rgb8_t;

    /**@ingroup PixelTypes
     * @brief Generic colorspace RGB, with alpha, floats. */
    typedef struct {
        uint8_t r; /**< Red */
        uint8_t g; /**< Green */
        uint8_t b; /**< Blue */
        uint8_t a; /**< Alpha */
    } rgba8_t;

    /**@ingroup PixelTypes
     * @brief Generic colorspace RGB, 16 bit per channel. */
    typedef struct {
        uint16_t r; /**< Red */
        uint16_t g; /**< Green */
        uint16_t b; /**< Blue */
    } rgb16_t;

    /**@ingroup PixelTypes
     * @brief Generic colorspace RGB, with alpha, 16 bit per channel. */
    typedef struct {
        uint16_t r; /**< Red */
        uint16_t g; /**< Green */
        uint16_t b; /**< Blue */
        uint16_t a; /**< Alpha */
    } rgba16_t;

    /* Pixel Functions ***********************************************************/

    /**
     * @brief Convert a CIE Lab pixel to CIE Lhc space.
     * @param [in] lab  The Lab pixel.
     * @param [out] ret The Lhc pixel.
     * @note See http://www.brucelindbloom.com/index.html?Equations.html .
     */
    void lab2lhc (const lab_t* lab, lhc_t* ret);

    /**
     * @brief Convert a CIE Lhc pixel to a CIE Lab space.
     * @param [in] lhc  The Lhc pixel.
     * @param [out] ret The Lab pixel.
     * @note  See http://www.brucelindbloom.com/index.html?Equations.html .
     */
    void lhc2lab (const lhc_t* lhc, lab_t* ret);

    /**
     * @brief Convert a CIE Lab pixel to CIE XYZ space.
     * @param [in] lab  The pixel in Lab space.
     * @param [in] cs   The RGB variant desired.
     * @param [out] ret The pixel in XYZ space.
     */
    void lab2xyz (const lab_t* lab, const colorspace_t* cs, xyz_t* ret);

    /**
     * @brief           Conversion to RGB from CIE XYZ space
     * @param [in] rgb  The RGB pixel.
     * @param [in] cs   The RGB variant desired.
     * @param [out] ret The XYZ pixel.
     * @note: See http://www.brucelindbloom.com/Eqn_RGB_XYZ_Matrix.html .
     */
    void rgbf2xvz (const rgbf_t* rgb, const colorspace_t* cs, xyz_t* ret);

    /**
     * @brief           Conversion to RGB from CIE XYZ space
     * @param [in] xyz  The XYZ pixel.
     * @param [in] cs   The RGB variant desired.
     * @param [out] ret The RGB pixel.
     * @note: See http://www.brucelindbloom.com/Eqn_RGB_XYZ_Matrix.html .
     */
    void xyz2rgbf (const xyz_t* xyz, const colorspace_t* cs, rgbf_t* ret);

    /**
     * @brief Convert a CIE XYZ pixel to CIE Lab space, assuming a D50 illuminant.
     * @param [in] xyz  The pixel in XYZ space.
     * @param [in] cs   The RGB variant desired.
     * @param [out] ret The pixel in Lab space.
     * @note: See http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html .
     */
    void xyz2lab (const xyz_t* xyz, const colorspace_t* cs, lab_t* ret);

#endif
