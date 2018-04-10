all:
	gcc main.c mnist.c common.c image_data.c neuron.c synapse.c network.c -lm -o main