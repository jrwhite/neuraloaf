#include "common.h"

inline uint32_t check_endian(uint32_t num) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return (
        ((num & 0xFF000000) >> 24) |
        ((num & 0x00FF0000) >>  8) |
        ((num & 0x0000FF00) <<  8) |
        ((num & 0x000000FF) << 24)
    );
#else
    return in;
#endif
}

void *xcalloc(size_t num_elems, size_t elem_size) {
    void *ptr = calloc(num_elems, elem_size);
    if (!ptr) {
        perror("xcalloc failed");
        exit(1);
    }
    return ptr;
}

void *xmalloc(size_t num_bytes) {
    void *ptr = malloc(num_bytes);
    if (!ptr) {
        perror("xmalloc failed");
        exit(1);
    }
    return ptr;
}

char *read_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buf = xmalloc(len + 1);
    if (len && fread(buf, len, 1, file) != 1) {
        fclose(file);
        free(buf);
        return NULL;
    }
    fclose(file);
    buf[len] = 0;
    return buf;
}

bool *write_file(const char *path, const char *buf, size_t len) {
    FILE *file = fopen(path, "w");
    if (!file) {
        return false;
    }
    size_t n = fwrite(buf, len, 1, file);
    fclose(file);
    return n == 1;
}