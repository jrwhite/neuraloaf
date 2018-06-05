#include "neuron.h"

void neuron_step(Neuron *n) {
    static int fire_period = 0;
    fire_period += 1; 
    /* add current */
    n->pot += n->current;

    /* check potential */
    if (n->pot >= n->threshold) {
        n->fire_callback(fire_period);
        fire_period = 0;
        n->is_firing = true;
        n->pot = 0;
    }
    
    if (n->is_firing && n->fire_time++ == FIRE_TIME) {
        /* done firing. reset. */
        n->is_firing = false;
        n->fire_time = 0;
    }

}

