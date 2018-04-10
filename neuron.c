#include "neuron.h"

void neuron_step(Neuron *n) {
    /* add current */
    n->pot += n->current;

    /* check potential */
    if (n->pot >= n->threshold) {
        n->is_firing = true;
        n->pot = 0;
    }
    
    if (n->is_firing && n->fire_time++ == FIRE_TIME) {
        /* done firing. reset. */
        n->is_firing = false;
        n->fire_time = 0;
    }

}

