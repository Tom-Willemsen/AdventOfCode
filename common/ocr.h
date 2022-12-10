#pragma once

#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

static const char ocr_on = '#';
static const char ocr_off = ' ';

static const char* const ocr_6x4_A = " ## "
                                     "#  #"
                                     "#  #"
                                     "####"
                                     "#  #"
                                     "#  #";

static const char* const ocr_6x4_B = "### "
                                     "#  #"
                                     "### "
                                     "#  #"
                                     "#  #"
                                     "### ";

static const char* const ocr_6x4_C = " ## "
                                     "#  #"
                                     "#   "
                                     "#   "
                                     "#  #"
                                     " ## ";

static const char* const ocr_6x4_E = "####"
                                     "#   "
                                     "### "
                                     "#   "
                                     "#   "
                                     "####";

static const char* const ocr_6x4_F = "####"
                                     "#   "
                                     "### "
                                     "#   "
                                     "#   "
                                     "#   ";

static const char* const ocr_6x4_G = " ## "
                                     "#  #"
                                     "#   "
                                     "# ##"
                                     "#  #"
                                     " ###";

static const char* const ocr_6x4_H = "#  #"
                                     "#  #"
                                     "####"
                                     "#  #"
                                     "#  #"
                                     "#  #";

static const char* const ocr_6x4_J = "  ##"
                                     "   #"
                                     "   #"
                                     "   #"
                                     "#  #"
                                     " ## ";

static const char* const ocr_6x4_K = "#  #"
                                     "# # "
                                     "##  "
                                     "# # "
                                     "# # "
                                     "#  #";

static const char* const ocr_6x4_L = "#   "
                                     "#   "
                                     "#   "
                                     "#   "
                                     "#   "
                                     "####";

static const char* const ocr_6x4_R = "### "
                                     "#  #"
                                     "#  #"
                                     "### "
                                     "# # "
                                     "#  #";

static const char* const ocr_6x4_Z = "####"
                                     "   #"
                                     "  # "
                                     " #  "
                                     "#   "
                                     "####";


static char ocr_6x4_char(char* data) {
    if (strncmp(data, ocr_6x4_A, 6*4) == 0) {
        return 'A';
    } else if (strncmp(data, ocr_6x4_B, 6*4) == 0) {
        return 'B';
    } else if (strncmp(data, ocr_6x4_C, 6*4) == 0) {
        return 'C';
    } else if (strncmp(data, ocr_6x4_E, 6*4) == 0) {
        return 'E';
    } else if (strncmp(data, ocr_6x4_F, 6*4) == 0) {
        return 'F';
    } else if (strncmp(data, ocr_6x4_G, 6*4) == 0) {
        return 'G';
    } else if (strncmp(data, ocr_6x4_H, 6*4) == 0) {
        return 'H';
    } else if (strncmp(data, ocr_6x4_J, 6*4) == 0) {
        return 'J';
    } else if (strncmp(data, ocr_6x4_K, 6*4) == 0) {
        return 'K';
    } else if (strncmp(data, ocr_6x4_L, 6*4) == 0) {
        return 'L';
    } else if (strncmp(data, ocr_6x4_R, 6*4) == 0) {
        return 'R';
    } else if (strncmp(data, ocr_6x4_Z, 6*4) == 0) {
        return 'Z';
    } else {
        printf("Unknown character in OCR:\n");
        for (int64_t row=0; row<6; ++row) {
            for (int64_t col=0; col<4; ++col) {
                printf("%c", data[row*4+col]);
            }
            puts("");
        }
        return '?';
    }
}

static void ocr_6x4_string(const char* const data, char* result, size_t slen, size_t row_length) {
    assert (row_length == (4+1) * slen || row_length == (4+1) * slen - 1);
    for (size_t c=0; c<slen; ++c) {
        char inp[6*4];
        for (size_t r=0; r<6; ++r) {
            size_t data_offset = row_length * r + (4+1) * c;
            memcpy(inp + r*4, data + data_offset, 4 * sizeof(char));
        }
        result[c] = ocr_6x4_char(inp);
    }
}
