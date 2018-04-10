#ifndef __IMAGE_DATA_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "common.h"

typedef struct Image {
    uint8_t label;
    uint8_t **bitmap;
} Image;

typedef struct ImageDset {
    const size_t len;
    const size_t elem_size;
    const size_t x_len;
    const size_t y_len;
    const Image * images;
} ImageDset;

uint8_t ** bitmap_init(const uint8_t *arr, size_t x_len, size_t y_len);

#endif