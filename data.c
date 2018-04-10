#include "data.h"

typedef struct DsetHdr {
    size_t len;
    size_t elem_size;
    char set[];
};

#define dset__hdr(d) ((DsetHdr *)((char *)(d) - offsetof(DsetHdr, set)))
