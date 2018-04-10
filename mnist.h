#ifndef __MNIST_H__
#define __MNIST_H__

#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "common.h"
#include "image_data.h"


const ImageDset * get_training_dataset(void);
void mnist_test(void);

#endif