#include "image_data.h"


uint8_t ** bitmap_init(const uint8_t * arr, size_t x_len, size_t y_len) {
    uint8_t *row = arr;
    uint8_t ** bitmap = xmalloc(x_len);

    for (size_t i = 0; i < x_len; i++) {
        bitmap[i] = xmalloc(y_len);
        memcpy(bitmap[i], (arr+(i*y_len)), y_len); 
    }

    return bitmap;
}
