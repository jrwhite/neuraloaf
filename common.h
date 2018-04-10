#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void *xcalloc(size_t num_elems, size_t elem_size);
void *xmalloc(size_t num_bytes);
char *read_file(const char *path); 

#endif