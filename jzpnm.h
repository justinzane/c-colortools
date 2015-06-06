/*****************************************************************************
 * @file         jzpnm.h
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

#ifndef JZPNM_H
#define JZPNM_H

#define _GNU_SOURCE

#include "clrtools.h"
#include "colorspaces.h"
#include <stdbool.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pcre.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** @brief Representation of a NetPBM PPM file. */
typedef struct {
    char* magic_num; /**< @brief The identification bytes at the beginning
                       * of the file. Should be "P3" for ASCII PPM. */
    int max_val;     /**< @brief The actual brieghtest subpixel. */
    char* comments;  /**< @brief hash symbol devined text comments. */
    img_rgb8_t* img; /**< @brief The actual image. */
} ppm_t;

/**
 * @brief           Determine the "magic number" of a
 *                  [PPM file](https://en.wikipedia.org/wiki/Netpbm_format).
 * @param [in] line The line of text to be processed.
 * @return          The file's "magic number"; should be 'P3' for ASCII PPMs.
 */
char* get_magic_num (const char* line);

/**
 * @brief WRITEME
 * @param line
 * @return
 */
char* get_comments (const char* line);

typedef struct {
    unsigned int width;
    unsigned int height;
} dimensions;

/**
 * @brief WRITEME
 * @param line
 * @return
 */
dimensions* get_dimensions (const char* line);

/**
 * @brief WRITEME
 * @param line
 * @return
 */
int get_max_val (const char* line);

/**
 * @brief Converts lines of image data-as-text from an ASCII PPM file into
 *        an array of pixels composed of R,G,B subpixels. This function works
 *        with 8 bit subpixels (24 bit pixels).
 * @param line [in]         The line of text to be processed; should not contain any
 *                          text besides image data.
 * @param counter [in,out]  Tracks the current pixel between lines.
 * @param subpix [in,out]   Tracks the current subpixel between lines.
 * @param data [out]        The binary image data.
 */
void get_data_8 (const char* line, size_t* counter, uint8_t* subpix, rgb8_t* data);

/**
 * @brief Loads and parses a PPM ASCII image file.
 * @param [in] src_file The "/path/file" ASCII PPM file to be loaded.
 * @param [out] src_img The PPM struct into which to place the parsed PPM image.
 */
void load_file (const char* src_file, ppm_t* src_img);

/**
 * @brief Writes a PPM image to file in ASCII format.
 * @note  This function is ONLY for RGB images, not RGBA images.
 * @param [in] img      The image to be written out.
 * @param [in] dst_file The "/path/filename" to write to.
 * @return  EXIT_SUCCESS/EXIT_FAILURE
 */
int save_file_rgb (const ppm_t img, const char* dst_file);

#endif // __JZPNM_H__
