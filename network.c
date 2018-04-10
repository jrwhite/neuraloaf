#include "network.h"

void network_step(Network * nn) {
    /* step neurons */
    for (size_t i = 0; i < nn->num_neurons; i++) {
        neuron_step(&(nn->neurons[i]));
    }
    /* step synapses */
    for (size_t i = 0; i < nn->num_synapses; i++) {
        synapse_step(&nn->synapses[i]);
    }
}