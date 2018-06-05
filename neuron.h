#ifndef __NEURON_H__
#define __NEURON_H__

#include <stdbool.h>

#define FIRE_TIME 1

typedef struct Neuron {
    bool is_firing;
    int fire_time;
    float pot;
    float current;
    float threshold;
    void (*fire_callback)(int);
} Neuron;

void neuron_step(Neuron *n);

#endif