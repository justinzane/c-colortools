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
    img_rgb8_t v = {0, 0, &NTSC_RGB, NULL};
    ppm_t testimg = {NULL, 0, NULL, &v};
    load_file ("/home/justin/src/c-colortools/test/test.ppm", &testimg);
    printf ("Loaded testimg.\n");

    // RGB8 to RGBF
    img_rgbf_t rgbfsrc;
    rgbfsrc.cs = testimg.img->cs;
    rgbfsrc.width = testimg.img->width;
    rgbfsrc.height = testimg.img->height;
    rgbfsrc.data = malloc (sizeof (lhc_t) * rgbfsrc.width * rgbfsrc.height);
    img_rgb82rgbf (testimg.img, &rgbfsrc);
    printf ("Created rgbfsrc.\n");

    // RGB to XYZ
    img_xyz_t xyzsrc;
    xyzsrc.cs = testimg.img->cs;
    xyzsrc.width = testimg.img->width;
    xyzsrc.height = testimg.img->height;
    xyzsrc.data = malloc (sizeof (lhc_t) * xyzsrc.width * xyzsrc.height);
    img_rgb2xyz (&rgbfsrc, &xyzsrc);
    printf ("Created xyzsrc.\n");

    // XYZ to Lab
    img_lab_t labsrc;
    labsrc.cs = testimg.img->cs;
    labsrc.width = testimg.img->width;
    labsrc.height = testimg.img->height;
    labsrc.data = malloc (sizeof (lab_t) * labsrc.width * labsrc.height);
    img_xyz2lab (&xyzsrc, &labsrc);
    printf ("Created labsrc.\n");

    // Lab to Lhc
    img_lhc_t lhcsrc;
    lhcsrc.cs = testimg.img->cs;
    lhcsrc.width = testimg.img->width;
    lhcsrc.height = testimg.img->height;
    lhcsrc.data = malloc (sizeof (lhc_t) * lhcsrc.width * lhcsrc.height);
    img_lab2lhc (&labsrc, &lhcsrc);
    printf ("Created lhcsrc.\n");

    for (float adjustment = 0.0f; adjustment < 361.0f; adjustment += 60.0f) {
        /* Adjustment of hue goes here. */
        img_lhc_t lhcdst;
        lhcdst.cs = lhcsrc.cs;
        lhcdst.width = lhcsrc.width;
        lhcdst.height = lhcsrc.height;
        lhcdst.data = malloc (sizeof (lhc_t) * lhcdst.width * lhcdst.height);
        adj_hue_deg (&lhcsrc, &lhcdst, adjustment);

        // Lhc to Lab
        img_lab_t labdst;
        labdst.cs = testimg.img->cs;
        labdst.width = testimg.img->width;
        labdst.height = testimg.img->height;
        labdst.data = malloc (sizeof (lab_t) * labdst.width * labdst.height);
        img_lhc2lab (&lhcdst, &labdst);
        printf ("Created labdst.\n");

        // Lab to XYZ
        img_xyz_t xyzdst;
        xyzdst.cs = testimg.img->cs;
        xyzdst.width = testimg.img->width;
        xyzdst.height = testimg.img->height;
        xyzdst.data = malloc (sizeof (xyz_t) * xyzdst.width * xyzdst.height);
        img_lab2xyz (&labdst, &xyzdst);
        printf ("Created xyzdst.\n");

        // XYZ - RGBF
        img_xyz_t rgbfdst;
        rgbfdst.cs = testimg.img->cs;
        rgbfdst.width = testimg.img->width;
        rgbfdst.height = testimg.img->height;
        rgbfdst.data = malloc (sizeof (rgbf_t) * rgbfdst.width * rgbfdst.height);
        img_xyz2rgb (&xyzdst, &rgbfdst);
        printf ("Created rgbfdst.\n");

        // RGBf to RGB8
        img_rgb8_t rgb8dst;
        rgb8dst.cs = testimg.img->cs;
        rgb8dst.width = testimg.img->width;
        rgb8dst.height = testimg.img->height;
        rgb8dst.data = malloc (sizeof (rgb8_t) * rgb8dst.width * rgb8dst.height);
        img_rgbf2rgb8 (&rgbfdst, &rgb8dst);
        printf ("Created rgb8dst.\n");

        ppm_t outimg = {testimg.magic_num, testimg.max_val, testimg.comments, &rgb8dst};
        //    outimg.magic_num = malloc (sizeof (char) * strlen (testimg.magic_num));
        //    strncpy (testimg.magic_num, outimg.magic_num, strlen (testimg.magic_num));
        //    outimg.max_val = testimg.max_val;
        //    if (testimg.comments == NULL) {
        //        outimg.comments = NULL;
        //    } else {
        //        outimg.comments = malloc (sizeof (char) * strlen (testimg.comments));
        //        strncpy (testimg.comments, outimg.comments, strlen (testimg.comments));
        //    }
        printf ("Created outimg.\n");
        char outname[1024];
        snprintf (outname, 1024, "/home/justin/src/c-colortools/test/out_%d.ppm",
                  (int)adjustment);
        int didsave = save_file_rgb (outimg, outname);
        printf ("Did save: %d\n", didsave);
    }
}
