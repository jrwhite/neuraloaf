#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdlib.h>
#include <stdint.h>

#include "neuron.h"
#include "synapse.h"

typedef struct Network {
    Neuron * neurons;
    size_t num_neurons;
    Synapse * synapses;
    size_t num_synapses;
    uint32_t step_num;
} Network;

void network_step(Network *nn);

#endif