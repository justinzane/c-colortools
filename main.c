/*****************************************************************************
 * @file         main.c
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

/** TODO: Setup consistent debug output handling. zlog? log4c? syslog? RYO? */

#include "jzpnm.h"
#include "clrtools.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    img_rgb8_t v = {0, 0, &sRGB, NULL};
    ppm_t testimg = {NULL, 0, NULL, &v};
    load_file ("/home/justin/src/c-colortools/test.ppm", &testimg);
    printf ("Loaded testimg.\n");
    img_rgb8_t x = {0, 0, NULL, NULL};
    ppm_t outimg = {NULL, 0, NULL, &x};
    outimg.magic_num = malloc (sizeof (char) * strlen (testimg.magic_num));
    strncpy (testimg.magic_num, outimg.magic_num, strlen (testimg.magic_num));
    outimg.max_val = testimg.max_val;
    if (testimg.comments == NULL) {
        outimg.comments == NULL;
    } else {
        outimg.comments = malloc (sizeof (char) * strlen (testimg.comments));
        strncpy (testimg.comments, outimg.comments, strlen (testimg.comments));
    }
    printf ("Created outimg.\n");
    img_lhc_t srcimg;
    img_rgb2lhc (testimg.img, &srcimg);
    printf ("Converted testimg to Lhc.\n");
    img_lhc_t dstimg;
    adj_hue_deg (&srcimg, &dstimg, 180.0f);
    printf ("Adjusted hue of image.\n");
    free (srcimg.data);
}
