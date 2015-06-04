/*****************************************************************************
 * @file         clrtools.h
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief        WRITEME
 * @license      GPLv3
 * @note         A convention used here is that functions with names including
 * "rgb" without a type qualifier like "rgba8" or "rgb16" refer to images with
 * 4 channels and float subpixels.
 * @todo         Refactor some names to limit confusion between img_XXX_t
 * image structs and imgXXX2YYY conversion functions.
 * @todo         Check and verify docstrings.
 ***************************************************************************/

#ifndef CLRTOOLS_H
#define CLRTOOLS_H

#include "colorspaces.h"
#include "defines.h"
#include "pixels.h"
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Image Type Definitions *****************************************************
 */

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    lhc_t data[];
} img_lhc_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    lab_t* data;
} img_lab_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    xyz_t* data;
} img_xyz_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    rgbf_t* data;
} img_rgbf_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    rgb8_t* data;
} img_rgb8_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    rgba8_t* data;
} img_rgba8_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    rgb16_t* data;
} img_rgb16_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    colorspace_t* cs;
    rgba16_t* data;
} img_rgba16_t;

/*
 * Function Declarations ******************************************************
 */

/* Image Functions ***********************************************************/

/**
 * @brief Adjusts the hue of an image by the given angle.
 * @description
 * The hue of a pixel is based on 0 degrees being red, 120 being green and
 * 240 being blue. Therefore a pixel with an initial hue of 60 degrees (yellow)
 * that is shifted by 240 degrees ends up being purple. This is done in CIE
 * LHC space so that the percieved shift is better than in typical HSV space.
 * @param [in] src      The original image.
 * @param [out] dst     The adjusted image.
 * @param [in] adj_deg  0.0f <= adj_deg < 360.0f
 */
void adj_hue_deg (const img_lhc_t* src, img_lhc_t* dst, const float adj_deg);

/**
 * @brief Converts an image from CIE Lab to CIE Lhc
 * @param [in] labimg
 * @param [out] lhcimg
 */
void img_lab2lhc (const img_lab_t* labimg, img_lhc_t* lhcimg);

/**
 * @brief Convert an image from CIE Lab to CIE XYZ space.
 * @param labimg
 * @param [out] xyzimg  The output data. If NULL, will be malloc'd to appropriate
 *                      size. If not NULL, will realloc to be sure.
 */
void img_lab2xyz (const img_lab_t* labimg, img_xyz_t* xyzimg);

/**
 * @brief Converts an image from CIE Lhc to CIE Lab
 * @param [in] lhcimg
 * @param [out] labimg
 */
void img_lhc2lab (const img_lhc_t* lhcimg, img_lab_t* labimg);

/**
 * @brief Convert an image from CIE Lhc to RGB, float, with alpha.
 * @param [in] lhcimg
 * @param [out] rgbimg
 */
void img_lhc2rgb (const img_lhc_t* lhcimg, img_rgbf_t* rgbimg);

/**
 * @brief Convert an image from CIE Lhc to RGB with 24 bits per pixel.
 * @param [in] lhcimg
 * @param [out] rgbimg
 */
void img_lhc2rgb8 (const img_lhc_t* lhcimg, img_rgb8_t* rgbimg);

void img_rgb2lhc (const img_rgbf_t* rgbimg, img_lhc_t* lhcimg);

void img_rgbf2rgb8 (const img_rgbf_t* fltimg, img_rgb8_t* intimg);

void img_rgbf2rgba8 (const img_rgbf_t* fltimg, img_rgba8_t* intimg);

void img_rgbf2rgb16 (const img_rgbf_t* fltimg, img_rgb16_t* intimg);

void img_rgbf2rgba16 (const img_rgbf_t* fltimg, img_rgba16_t* intimg);

void img_rgb82lhc (const img_rgb8_t* rgbimg, img_lhc_t* lhcimg);

void img_rgba82lhc (const img_rgba8_t* rgbimg, img_lhc_t* lhcimg);

void img_rgb162lhc (const img_rgb16_t* rgbimg, img_lhc_t* lhcimg);

void img_rgba162lhc (const img_rgba16_t* rgbimg, img_lhc_t* lhcimg);

void img_rgb82rgbf (const img_rgb8_t* rgb8, img_rgbf_t* rgbf);

/**
 * @brief WRITEME
 * @param [in] rgba8
 * @param [out] rgbf
 */
void img_rgba82rgbf (const img_rgb8_t* rgba8, img_rgbf_t* rgbf);

/**
 * @brief WRITEME
 * @param [in] rgb16
 * @param [out] rgbf
 */
void img_rgb162rgbf (const img_rgb8_t* rgb16, img_rgbf_t* rgbf);

/**
 * @brief WRITEME
 * @param [in] rgba16
 * @param [out] rgbf
 */
void img_rgba162rgbf (const img_rgb8_t* rgba16, img_rgbf_t* rgbf);

/**
 * @brief Convert a RGB image to CIE XYZ space, using float subpixels,
 *        in the provided colorspace.
 * @param [in] rgbimg   The RGB image.
 * @param [out] xyzimg  The RGB image.
 */
void img_rgb2xyz (const img_rgbf_t* rgbimg, img_xyz_t* xyzimg);

/**
 * @brief Convert an image from CIE Lab to CIE XYZ space.
 * @param [in] labimg
 * @param [out] xyzimg
 */
void img_xyz2lab (const img_xyz_t* xyzimg, img_lab_t* labimg);

/**
 * @brief Convert a CIE XYZ image to RGB space, using float subpixels,
          in the provided colorspace.
 * @param [in] xyzimg   The XYZ image.
 * @param [out] rgbimg  The RGB image.
 */
void img_xyz2rgb (const img_xyz_t* xyzimg, img_rgbf_t* rgbimg);

#endif // CLRTOOLS_H
