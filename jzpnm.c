/*****************************************************************************
 * @file         jzpnm.c
 * @author       Justin Zane Chudgar <justin@justinzane.com>
 * @version
 * @copyright    Copyright 2014, Justin Zane Chudgar <justin@justinzane.com>
 * @brief
 * @license      GPLv3
 ***************************************************************************/

#include "jzpnm.h"

/* TODO: Refactor PCREs so that they are not regenerated on every friggin function call.
 * Use pcreprecompile, see http://www.gammon.com.au/pcre/pcreprecompile.html */

char* get_magic_num (const char* line) {
    const char* err_msg = NULL;
    int err_offset = 0;
    const int ov_size = 32;
    int ovec[ov_size];

    pcre* re = pcre_compile ("^[A-Z][0-9]\n", /* the pattern */
                             0,               /* default options */
                             &err_msg,        /* for error message */
                             &err_offset,     /* for error offset */
                             NULL);           /* use default character tables */
    int rc = pcre_exec (re,                   /* the compiled pattern */
                        NULL,                 /* no extra data - we didn't study the pattern */
                        line,                 /* the subject string */
                        (int)strlen (line),   /* the length of the subject */
                        0,                    /* start at offset 0 in the subject */
                        0,                    /* default options */
                        ovec,                 /* output vector for substring information */
                        ov_size);             /* number of elements in the output vector */
    if (rc != -1) {
        char* num = malloc (((size_t)strlen (line) - 1) * sizeof (char));
        strncpy (num, line, ((size_t)strlen (line) - 1));
        return num;
    }
    pcre_free (re);
    return NULL;
}

char* get_comments (const char* line) {
    const char* err_msg = NULL;
    int err_offset = 0;
    const int ov_size = 32;
    int ovec[ov_size];

    pcre* re = pcre_compile ("^[\t ]*#.*$", 0, &err_msg, &err_offset, NULL);
    int rc = pcre_exec (re, NULL, line, (int)strlen (line), 0, 0, ovec, ov_size);
    if (rc != -1) {
        char* cmt = malloc ((size_t)strlen (line) * sizeof (char));
        strncpy (cmt, line, (size_t)strlen (line));
        return cmt;
    }
    pcre_free (re);
    return NULL;
}

dimensions* get_dimensions (const char* line) {
    const char* err_msg = NULL;
    int err_offset = 0;
    const int ov_size = 32;
    int ovec[ov_size];
    dimensions* dim = NULL;

    pcre* re =
        pcre_compile ("^[\t ]*([0-9]+)[\t ]+([0-9]+)[\t\n ]*$", 0, &err_msg, &err_offset, NULL);
    if (re == NULL) {
        printf ("PCRE compilation failed at offset %d: %s\n", err_offset, err_msg);
        goto end;
    }
    int rc = pcre_exec (re, NULL, line, (int)strlen (line), 0, 0, ovec, ov_size);
    if (rc == 3) {
        /* Note that pcre_get_substring mallocs itself. Also, substring count starts from 1. */
        const char* width_str = NULL;
        pcre_get_substring (line, ovec, rc, 1, &width_str);
        const char* height_str = NULL;
        pcre_get_substring (line, ovec, rc, 2, &height_str);
        dim = malloc (sizeof (dimensions));
        dim->width = atoi (width_str);
        dim->height = atoi (height_str);
    }
end:
    pcre_free (re);
    return dim;
}

int get_max_val (const char* line) {
    const char* err_msg = NULL;
    int err_offset = 0;
    const int ov_size = 32;
    int ovec[ov_size];
    int max_val = -1;

    pcre* re = pcre_compile ("^[\t ]*([0-9]+)[\t\n ]*$", 0, &err_msg, &err_offset, NULL);
    if (re == NULL) {
        printf ("PCRE compilation failed at offset %d: %s\n", err_offset, err_msg);
        goto end;
    }
    int rc = pcre_exec (re, NULL, line, (int)strlen (line), 0, 0, ovec, ov_size);
    if (rc == 2) {
        /* Note that pcre_get_substring mallocs itself. Also, substring count starts from 1. */
        const char* max_str = NULL;
        pcre_get_substring (line, ovec, rc, 1, &max_str);
        max_val = atoi (max_str);
    }
end:
    pcre_free (re);
    return max_val;
}

void get_data_8 (const char* line, size_t* counter, uint8_t* subpix, rgb8_t* data) {
    char tmp_str[3];
    int digits = 0;

    for (int i = 0; i < strlen (line); i++) {
        switch (line[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tmp_str[digits] = line[i];
                digits++;
                break;
            case ' ':
            case '\n':
            case '\t':
            case '\0':
                if (digits == 0) {
                    break;
                }
                if (digits == 1) {
                    tmp_str[1] = '\0';
                } else if (digits == 2) {
                    tmp_str[2] = '\0';
                }
                digits = 0;
                switch (*subpix) {
                    case 0:
                        data[*counter].r = (uint8_t)atoi (tmp_str);
                        (*subpix)++;
                        break;
                    case 1:
                        data[*counter].g = (uint8_t)atoi (tmp_str);
                        (*subpix)++;
                        break;
                    case 2:
                        data[*counter].b = (uint8_t)atoi (tmp_str);
                        (*subpix) = 0;
                        (*counter)++;
                        break;
                }
                break;
            default:
                printf ("DOH! I'm supposed to be unreachable! %s:%d", __FILE__, __LINE__);
        } // switch
    }     // for
}

void load_file (const char* filename, ppm_t* src_img) {
    FILE* src_lines = fopen (filename, "r");
    if (src_lines == NULL) {
        printf ("Could not open %s!", filename);
        return;
    }
    size_t buf_size = 1024;
    char* inbuf = NULL;
    ssize_t read;
    char* mn = NULL;
    char* cmts = NULL;
    dimensions* dim = NULL;
    int mv = -1;
    size_t counter = 0;
    uint8_t subpix = 0;

    while (!((read = getline (&inbuf, &buf_size, src_lines)) == -1)) {
        //        printf ("Read %ld chars.:    %s", read, inbuf);
        if ((cmts = get_comments (inbuf)) != NULL) {
            /* Working on the assumption that comments may appear anywhere in the
             * source file, we check for comments every line. */
            if (src_img->comments == NULL) {
                src_img->comments = malloc ((size_t)strlen (cmts) * sizeof (char));
            } else {
                void* res = realloc (src_img->comments, ((size_t)strlen (src_img->comments) +
                                                         (size_t)strlen (cmts)) *
                                                            sizeof (char));
                if (res == NULL) {
                    printf ("realloc failed.\n");
                }
            }
            strcat (src_img->comments, cmts);
            printf ("comments: %s\n", src_img->comments);
            cmts = NULL;
        } // cmts if
        else if ((src_img->magic_num == NULL) && ((mn = get_magic_num (inbuf)) != NULL)) {
            /* We only check for things like the magic number and dimensions if they
             * are not already known since they can only appear once in the "header". */
            src_img->magic_num = mn;
            printf ("magic_num: %s, mn: %s\n", src_img->magic_num, mn);
        } // magic_num if
        else if ((src_img->img->width * src_img->img->height == 0) &&
                 ((dim = get_dimensions (inbuf)) != NULL)) {
            printf ("dimensions: %d x %d.\n", src_img->img->width, src_img->img->height);
            src_img->img->width = dim->width;
            src_img->img->height = dim->height;
            printf ("dimensions: %d x %d.\n", src_img->img->width, src_img->img->height);
        } // img if
        else if ((src_img->max_val <= 0) && (mv = get_max_val (inbuf)) >= 0) {
            src_img->max_val = mv;
            printf ("max_val: %d.\n", src_img->max_val);
            /* Now that we have finished the useful part of the header, allocate the data. */
            src_img->img->data =
                malloc (sizeof (rgb8_t) * src_img->img->height * src_img->img->width);
        } // max_val if
        else {
            /* parse data
             * counter is used to track which subpixel the line finishes on.
             * I.e.,       "255 255 255 191 191 191 127 127"
             *              0/r 1/g 2/b 3/r 4/g 5/b 6/r 7/g */
            get_data_8 (inbuf, &counter, &subpix, src_img->img->data);
            if ((counter % 60) == 0) {
                printf ("Finished subpixel %zu, %05.1f\n", counter,
                        (100.0 * counter) / (3 * src_img->img->height * src_img->img->width));
            }
        } // else
    }     // while
}

int save_file_rgb (const ppm_t img, const char* dst_file) {
    FILE* dst = fopen (dst_file, "w");
    if (dst == NULL) {
        printf ("Could not open %s for writing.\n", dst_file);
        goto failure;
    }
    fprintf (dst, "%s\n", img.magic_num);
    fprintf (dst, "%d %d\n", img.img->width, img.img->height);
    fprintf (dst, "%d\n", img.max_val);
    if (img.comments != NULL) {
        fprintf (dst, "%s\n", img.comments);
    }
    int line_len = 0;
    char* tmp = malloc (12 * sizeof (uint8_t));

    for (int y = 0; y < img.img->height; y++) {
        for (int x = 0; x < img.img->width; x++) {
            snprintf (tmp, 12 * sizeof (uint8_t), "%" PRIu8 " %" PRIu8 " %" PRIu8,
                      img.img->data[y * img.img->width + x].r,
                      img.img->data[y * img.img->width + x].g,
                      img.img->data[y * img.img->width + x].b);
            line_len += strlen (tmp) + 1;
            if (line_len > 68) {
                fprintf (dst, "%s\n", tmp);
                line_len = 0;
            } else {
                fprintf (dst, "%s ", tmp);
            }
        } // x
    }     // y
          // success:
    if (dst != NULL) {
        fclose (dst);
    }
    return EXIT_SUCCESS;
failure:
    if (dst != NULL) {
        fclose (dst);
    }
    return EXIT_FAILURE;
}
