#include "synapse.h"

void synapse_step(Synapse *s) {
    /* check if axon fired */
    if (s->axon->fire_time == s->delay) {
        s->dendrite->pot += s->weight;
    }
} 