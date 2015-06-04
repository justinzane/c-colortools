/*****************************************************************************
 * @file         clrtools.c
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

#include "clrtools.h"

void adj_hue_deg (const img_lhc_t* src, img_lhc_t* dst, const float adj_deg) {
    if (src == NULL) {
        printf ("Input Lhc image was NULL!\n");
        return;
    }
    if (dst == NULL) {
        printf ("Output Lhc image was NULL!\n");
        return;
    }
    float adj;
    if (adj_deg < 0.0f) {
        adj = (-1.0f * fmodf (adj_deg, 360.0f)) / (2.0f * M_PI_F);
    }
    if (adj_deg >= 360.0f) {
        adj = fmodf (adj_deg, 360.0f) / (2.0f * M_PI_F);
    }
    dst->cs = src->cs;
    dst->width = src->width;
    dst->height = src->height;
    void* result = realloc (src->data, sizeof (lhc_t) * dst->width * dst->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < src->height; y++) {
        for (unsigned int x = 0; x < src->width; x++) {
            dst->data[y * dst->width + x].l = src->data[y * src->height + x].l;
            dst->data[y * dst->width + x].h = src->data[y * src->height + x].h + adj;
            if (dst->data[y * dst->width + x].h >= (2.0f * M_PI_F)) {
                dst->data[y * dst->width + x].h -= (2.0f * M_PI_F);
            } else if (dst->data[y * dst->width + x].h < 0.0f) {
                dst->data[y * dst->width + x].h -= (2.0f * M_PI_F);
            }
            dst->data[y * dst->width + x].l = src->data[y * src->height + x].l;
            dst->data[y * dst->width + x].l = src->data[y * src->height + x].l;
        }
    }
    return;
}

void img_lab2lhc (const img_lab_t* labimg, img_lhc_t* lhcimg) {
    if (labimg == NULL) {
        printf ("Input Lab image was NULL!\n");
        return;
    }
    if (lhcimg == NULL) {
        lhcimg = malloc (sizeof (img_lhc_t));
    }
    lhcimg->cs = labimg->cs;
    lhcimg->height = labimg->height;
    lhcimg->width = labimg->width;
    void* result = realloc (lhcimg->data, sizeof (xyz_t) * labimg->width * labimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < labimg->height; y++) {
        for (unsigned int x = 0; x < labimg->width; x++) {
            lhcimg->data[(y * labimg->width) + x] =
                lab2lhc (labimg->data[(y * labimg->width) + x]);
        }
    }
    return;
}

void img_lab2xyz (const img_lab_t* labimg, img_xyz_t* xyzimg) {
    if (labimg == NULL) {
        printf ("Input Lab image was NULL!\n");
        return;
    }
    if (xyzimg == NULL) {
        xyzimg = malloc (sizeof (img_xyz_t));
    }
    xyzimg->cs = labimg->cs;
    xyzimg->height = labimg->height;
    xyzimg->width = labimg->width;
    void* result = realloc (xyzimg->data, sizeof (xyz_t) * labimg->width * labimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < labimg->height; y++) {
        for (unsigned int x = 0; x < labimg->width; x++) {
            xyzimg->data[(y * labimg->width) + x] =
                lab2xyz (labimg->data[(y * labimg->width) + x], labimg->cs);
        }
    }
}

void img_lhc2lab (const img_lhc_t* lhcimg, img_lab_t* labimg) {
    if (lhcimg == NULL) {
        printf ("Input Lhc image was NULL!\n");
        return;
    }
    if (labimg == NULL) {
        labimg = malloc (sizeof (img_lab_t));
    }
    labimg->cs = lhcimg->cs;
    labimg->height = lhcimg->height;
    labimg->width = lhcimg->width;
    void* result = realloc (labimg->data, sizeof (xyz_t) * lhcimg->width * lhcimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < lhcimg->height; y++) {
        for (unsigned int x = 0; x < lhcimg->width; x++) {
            labimg->data[(y * lhcimg->width) + x] =
                lhc2lab (lhcimg->data[(y * lhcimg->width) + x]);
        }
    }
}

void img_lhc2rgb (const img_lhc_t* lhcimg, img_rgbf_t* rgbimg) {
    img_lab_t lab;
    img_lhc2lab (lhcimg, &lab);
    img_xyz_t xyz;
    img_lab2xyz (&lab, &xyz);
    free (lab.data);
    img_xyz2rgb (&xyz, rgbimg);
    free (xyz.data);
}

void img_lhc2rgb8 (const img_lhc_t* lhcimg, img_rgb8_t* rgbimg) {
    img_rgbf_t rgbfimg;
    img_lhc2rgb (lhcimg, &rgbfimg);
    img_rgbf2rgb8 (&rgbfimg, rgbimg);
}

void img_rgb2lhc (const img_rgbf_t* rgbimg, img_lhc_t* lhcimg) {
    img_xyz_t xyz;
    img_rgb2xyz (rgbimg, &xyz);
    img_lab_t lab;
    img_xyz2lab (&xyz, &lab);
    free (xyz.data);
    img_lab2lhc (&lab, lhcimg);
    free (lab.data);
}

void img_rgbf2rgb8 (const img_rgbf_t* fltimg, img_rgb8_t* intimg) {
    if (fltimg == NULL) {
        printf ("Input image NULL!\n");
        return;
    }
    if (intimg == NULL) {
        intimg = malloc (sizeof (img_rgb8_t));
    }
    intimg->cs = fltimg->cs;
    intimg->width = fltimg->width;
    intimg->height = fltimg->height;
    rgb8_t* result = realloc (intimg->data, sizeof (rgb8_t) * intimg->width * intimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < fltimg->height; y++) {
        for (unsigned int x = 0; x < fltimg->height; x++) {
            intimg->data[y * intimg->width + x].r =
                (uint8_t)(fltimg->data[y * fltimg->width + x].r + 0.5f);
            intimg->data[y * intimg->width + x].g =
                (uint8_t)(fltimg->data[y * fltimg->width + x].g + 0.5f);
            intimg->data[y * intimg->width + x].b =
                (uint8_t)(fltimg->data[y * fltimg->width + x].b + 0.5f);
        }
    }
}

void img_rgbf2rgba8 (const img_rgbf_t* fltimg, img_rgba8_t* intimg) {
    if (fltimg == NULL) {
        printf ("Input image NULL!\n");
        return;
    }
    if (intimg == NULL) {
        intimg = malloc (sizeof (img_rgba8_t));
    }
    intimg->cs = fltimg->cs;
    intimg->width = fltimg->width;
    intimg->height = fltimg->height;
    rgb8_t* result = realloc (intimg->data, sizeof (rgba8_t) * intimg->width * intimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < fltimg->height; y++) {
        for (unsigned int x = 0; x < fltimg->height; x++) {
            intimg->data[y * intimg->width + x].r =
                (uint8_t)(fltimg->data[y * fltimg->width + x].r + 0.5f);
            intimg->data[y * intimg->width + x].g =
                (uint8_t)(fltimg->data[y * fltimg->width + x].g + 0.5f);
            intimg->data[y * intimg->width + x].b =
                (uint8_t)(fltimg->data[y * fltimg->width + x].b + 0.5f);
            intimg->data[y * intimg->width + x].a =
                (uint8_t)(fltimg->data[y * fltimg->width + x].a + 0.5f);
        }
    }
}

void img_rgbf2rgb16 (const img_rgbf_t* fltimg, img_rgb16_t* intimg) {
    if (fltimg == NULL) {
        printf ("Input image NULL!\n");
        return;
    }
    if (intimg == NULL) {
        intimg = malloc (sizeof (img_rgb16_t));
    }
    intimg->cs = fltimg->cs;
    intimg->width = fltimg->width;
    intimg->height = fltimg->height;
    rgb8_t* result = realloc (intimg->data, sizeof (rgb16_t) * intimg->width * intimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < fltimg->height; y++) {
        for (unsigned int x = 0; x < fltimg->height; x++) {
            intimg->data[y * intimg->width + x].r =
                (uint16_t)(fltimg->data[y * fltimg->width + x].r + 0.5f);
            intimg->data[y * intimg->width + x].g =
                (uint16_t)(fltimg->data[y * fltimg->width + x].g + 0.5f);
            intimg->data[y * intimg->width + x].b =
                (uint16_t)(fltimg->data[y * fltimg->width + x].b + 0.5f);
        }
    }
}

void img_rgbf2rgba16 (const img_rgbf_t* fltimg, img_rgba16_t* intimg) {
    if (fltimg == NULL) {
        printf ("Input image NULL!\n");
        return;
    }
    if (intimg == NULL) {
        intimg = malloc (sizeof (img_rgba16_t));
    }
    intimg->cs = fltimg->cs;
    intimg->width = fltimg->width;
    intimg->height = fltimg->height;
    rgb8_t* result = realloc (intimg->data, sizeof (rgba16_t) * intimg->width * intimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < fltimg->height; y++) {
        for (unsigned int x = 0; x < fltimg->height; x++) {
            intimg->data[y * intimg->width + x].r =
                (uint16_t)(fltimg->data[y * fltimg->width + x].r + 0.5f);
            intimg->data[y * intimg->width + x].g =
                (uint16_t)(fltimg->data[y * fltimg->width + x].g + 0.5f);
            intimg->data[y * intimg->width + x].b =
                (uint16_t)(fltimg->data[y * fltimg->width + x].b + 0.5f);
            intimg->data[y * intimg->width + x].a =
                (uint16_t)(fltimg->data[y * fltimg->width + x].a + 0.5f);
        }
    }
}

void img_rgb82lhc (const img_rgb8_t* rgbimg, img_lhc_t* lhcimg) {
    img_rgbf_t rgbfimg;
    img_rgb82rgbf (rgbimg, &rgbfimg);
    img_rgb2lhc (&rgbfimg, lhcimg);
}

void img_rgba82lhc (const img_rgba8_t* rgbimg, img_lhc_t* lhcimg) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}

void img_rgb162lhc (const img_rgb16_t* rgbimg, img_lhc_t* lhcimg) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}

void img_rgba162lhc (const img_rgba16_t* rgbimg, img_lhc_t* lhcimg) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}

void img_rgb82rgbf (const img_rgb8_t* rgb8, img_rgbf_t* rgbf) {
    if (rgb8 == NULL) {
        printf ("Input img null!\n");
    }
    if (rgbf == NULL) {
        rgbf = malloc (sizeof (img_rgbf_t));
    }
    rgbf->cs = rgb8->cs;
    rgbf->width = rgb8->width;
    rgbf->height = rgb8->height;
    void* result = realloc (rgbf->data, sizeof (float) * rgbf->width * rgbf->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
    }
    for (unsigned int y = 0; y < rgbf->height; y++) {
        for (unsigned int x = 0; x < rgbf->width; x++) {
            rgbf->data[y * rgbf->width + x].r =
                (float)(rgb8->data[y * rgb8->width + x].r) / 255.0f;
            rgbf->data[y * rgbf->width + x].g =
                (float)(rgb8->data[y * rgb8->width + x].g) / 255.0f;
            rgbf->data[y * rgbf->width + x].b =
                (float)(rgb8->data[y * rgb8->width + x].b) / 255.0f;
            rgbf->data[y * rgbf->width + x].a = 1.0f;
        }
    }
}

void img_rgba82rgbf (const img_rgb8_t* rgba8, img_rgbf_t* rgbf) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}
void img_rgb162rgbf (const img_rgb8_t* rgb16, img_rgbf_t* rgbf) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}
void img_rgba162rgbf (const img_rgb8_t* rgba16, img_rgbf_t* rgbf) {
    /* TODO WRITEME */
    printf ("NOT IMPLEMENTED! FIXME!\n");
}

void img_rgb2xyz (const img_rgbf_t* rgbimg, img_xyz_t* xyzimg) {
    if (rgbimg == NULL) {
        printf ("Input RGB image was NULL!\n");
        return;
    } else {
        // DEBUGGING
        printf ("rgbimg = {cs.id: %d, w: %ud, h: %ud, data: %f %f %f\n", rgbimg->cs->id,
                rgbimg->width, rgbimg->height, rgbimg->data[0].r, rgbimg->data[0].g,
                rgbimg->data[0].b);
    }
    if (xyzimg == NULL) {
        xyzimg = malloc (sizeof (img_xyz_t));
        xyzimg->data = malloc (sizeof (xyz_t) * rgbimg->width * rgbimg->height);
    }
    xyzimg->cs = rgbimg->cs;
    xyzimg->height = rgbimg->height;
    xyzimg->width = rgbimg->width;
    for (unsigned int y = 0; y < rgbimg->height; y++) {
        for (unsigned int x = 0; x < rgbimg->width; x++) {
            xyzimg->data[(y * rgbimg->width) + x] =
                rgbf2xvz (rgbimg->data[(y * rgbimg->width) + x], rgbimg->cs);
        }
    }
}

void img_xyz2lab (const img_xyz_t* xyzimg, img_lab_t* labimg) {
    if (xyzimg == NULL) {
        printf ("Input Lab image was NULL!\n");
        return;
    }
    if (labimg == NULL) {
        labimg = malloc (sizeof (img_lab_t));
    }
    labimg->cs = xyzimg->cs;
    labimg->height = xyzimg->height;
    labimg->width = xyzimg->width;
    void* result = realloc (labimg->data, sizeof (lab_t) * xyzimg->width * xyzimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < xyzimg->height; y++) {
        for (unsigned int x = 0; x < xyzimg->width; x++) {
            labimg->data[(y * xyzimg->width) + x] =
                xyz2lab (xyzimg->data[(y * xyzimg->width) + x], xyzimg->cs);
        }
    }
}

void img_xyz2rgb (const img_xyz_t* xyzimg, img_rgbf_t* rgbimg) {
    if (xyzimg == NULL) {
        printf ("Input XYZ image was NULL!\n");
        return;
    }
    if (rgbimg == NULL) {
        printf ("Output RGB image was NULL!\n");
        return;
    }
    rgbimg->cs = xyzimg->cs;
    rgbimg->height = xyzimg->height;
    rgbimg->width = xyzimg->width;
    void* result = realloc (rgbimg->data, sizeof (rgbf_t) * xyzimg->width * xyzimg->height);
    if (result == NULL) {
        printf ("realloc failed!\n");
        return;
    }
    for (unsigned int y = 0; y < xyzimg->height; y++) {
        for (unsigned int x = 0; x < xyzimg->width; x++) {
            /** @todo: Implement colorspace handling up the call chain. */
            rgbimg->data[(y * xyzimg->width) + x] =
                xyz2rgbf (xyzimg->data[(y * xyzimg->width) + x], xyzimg->cs);
        }
    }
}
