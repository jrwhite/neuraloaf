#ifndef __SYNAPSE_H__
#define __SYNAPSE_H__

#include "neuron.h"

typedef struct Synapse {
    float weight;
    int delay;
    Neuron * axon;
    Neuron * dendrite;
} Synapse;

void synapse_step(Synapse *s);

#endif