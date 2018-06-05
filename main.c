#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "mnist.h"

#include "neuron.h"
#include "synapse.h"
#include "network.h"

int num_periods = 0;
int period_count = 0;

void period_counter(int new_period) {
   period_count += new_period;
   num_periods += 1; 
}

#define SENSORY_NEURON {.pot = 0, .threshold = 100.0, .fire_callback = &period_counter}
// #define SENSORY_NEURON {.pot = 0.0, threshold = 1.0}
#define MOTOR_NEURON {.pot = 0, .threshold = 100000.0}

#define SYNAPSE(A, D) {.weight = 1, .delay = 1, .axon = A, .dendrite = D}

void neuron_test() {
    Neuron n = SENSORY_NEURON;
    n.current = 128;
    neuron_step(&n);
    printf("Neuron potential %d\n", n.pot);
}

void synapse_test() {
    Neuron n[] = {
       SENSORY_NEURON,
       MOTOR_NEURON
    };
    const size_t num_neurons = sizeof(n);

    Synapse s[] = {
        SYNAPSE(&n[0], &n[1])
    };
    const size_t num_synapses = sizeof(s);

    synapse_step(&s[0]);
    printf("synapse tst\n");
}

void network_test() {
    const uint32_t SENSE_STEPS = 4;
    const uint32_t NUM_STEPS = 5;

    Neuron n[] = {
       SENSORY_NEURON,
       MOTOR_NEURON
    };
    const size_t num_neurons = sizeof(n) / sizeof(Neuron);

    Synapse s[] = {
        SYNAPSE(&n[0], &n[1])
    };
    const size_t num_synapses = sizeof(s) / sizeof(Synapse);

    Network nn = {
       .neurons = n,
       .num_neurons = num_neurons,
       .synapses = s,
       .num_synapses = num_synapses
    };

    printf("Simulation started\n");
    for (uint32_t i = 0; i < NUM_STEPS; i++) {
        /* set sensory neuron current */
        n[0].current = i;
        for (uint32_t j = 0; j < SENSE_STEPS; j++) {
            network_step(&nn);
        printf("%d\n", n[0].pot);
        }
        /* check motor neuron potential */
        // printf("%d\n", n[1].pot);
        /* clear motor potential */
        n[0].pot = 0;
        n[1].pot = 0;
    }

}

void sense_test() {
    const uint32_t SENSE_STEPS = exp2(16);
    const uint32_t NUM_STEPS = 16;

    Neuron n[] = {
       SENSORY_NEURON,
       MOTOR_NEURON
    };
    const size_t num_neurons = sizeof(n) / sizeof(Neuron);

    Synapse s[] = {
        SYNAPSE(&n[0], &n[1])
    };
    const size_t num_synapses = sizeof(s) / sizeof(Synapse);

    Network nn = {
       .neurons = n,
       .num_neurons = num_neurons,
       .synapses = s,
       .num_synapses = num_synapses
    };

    printf("Simulation started\n");
    for (uint32_t i = 0; i < NUM_STEPS; i++) {
        /* set sensory neuron current */
        n[0].current = exp2(i);
        n[1].current = 0;
        for (uint32_t j = 0; j < SENSE_STEPS; j++) {
            network_step(&nn);
        }
        /* check motor neuron potential */
        printf("%d\n", (uint32_t) log2(n[1].pot));
        /* clear motor potential */
        n[1].pot = 0;
    }

}

#define SENSE(val) (exp(val))
void sense_test2() {
    const uint32_t SENSE_STEPS = 16;
    const uint32_t NUM_STEPS = 16;

    Neuron n[] = {
       SENSORY_NEURON,
       MOTOR_NEURON
    };
    const size_t num_neurons = sizeof(n) / sizeof(Neuron);

    Synapse s[] = {
        SYNAPSE(&n[0], &n[1])
    };
    const size_t num_synapses = sizeof(s) / sizeof(Synapse);

    Network nn = {
       .neurons = n,
       .num_neurons = num_neurons,
       .synapses = s,
       .num_synapses = num_synapses
    };

    printf("Simulation started\n");
    for (uint32_t i = 0; i < NUM_STEPS; i++) {
        /* set sensory neuron current */
        // n[0].current = i > SENSE_FLOOR ? (uint32_t) log(i-SENSE_FLOOR) : 0;
        n[0].current = 0.1;
        for (uint32_t j = 0; j < SENSE_STEPS; j++) {
            network_step(&nn);
        }
        /* check motor neuron potential */
        printf("%f\n", n[1].pot > 0 ? log(n[1].pot) : 0);
        /* clear motor potential */
        n[1].pot = 0;
    }

}


int current_test(float current) {
    const uint32_t NUM_STEPS = 100000;

    Neuron n[] = {
        SENSORY_NEURON,
        MOTOR_NEURON
    };

    Synapse s[] = {
        SYNAPSE(&n[0], &n[1])
    };
    const size_t num_synapses = sizeof(s) / sizeof(Synapse);

    Network nn = {
        .neurons = n,
        .num_neurons = 2,
        .synapses = s,
        .num_synapses = 1
    };
    n[0].current = current;
    for (uint32_t i = 0; i < NUM_STEPS; i++) {
        network_step(&nn);
    }
    printf("%f\n", n[1].pot > 0 ? (n[1].pot) : 0);
    return period_count / num_periods;
}

int main(int argc, char *argv[]) {
    printf("hello world!\n");
    // mnist_test(); 

    // neuron_test();
    // synapse_test();
    // network_test();
    // sense_test2();
    float c = 0.0;
    // for (float c = 0.0; c < 30.0; c += 1.0) {
    //     current_test(c);
        // printf("Current: %f, Period: %d", c, current_test(c));
    // }
    while (c < 40.0) {
        c = c + 1.0;
        printf("Current: %f, Period: %d\n", c, current_test(c));
    }
}

