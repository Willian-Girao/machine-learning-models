#include "forward_helper.h"

/* Sums all the gradients of a given hidden layer */
double sum_gradients_from_layer(hidden_layer *layer_k) {
	double sum = 0.0;
	hidden_layer *aux_k = layer_k;

	while(aux_k) {
		sum += aux_k->n_j->g;
		aux_k = aux_k->next;
	}

	return sum;
}

/* HELPER FUNCTION - Updates the coeficients of a single neuron */
void make_neuron_respond_to_pull(neuron *n_j, datapoint *data, double pull) {
	coeficients *aux_y = n_j->coefs;
	datapoint *aux_x = data;

	while (aux_y) { /* Loop through all the neuron's coeficients and he given datapoint dimensions*/
		aux_y->y_i += (aux_x->x_i * (pull - aux_y->y_i));

		aux_y = aux_y->next;
		if (!aux_y->next) { /* All the "multipliables" coeficients have been updated */
			aux_y->y_i += 1.0 * pull; /* Last neuron coeficient responds to the pull by the partial derivative of a sum */
			return;
		}
		aux_x = aux_x->next;
	}
}

/* Updates the coeficienst of all the neurons in the given layer */
void make_layer_respond_to_pull(hidden_layer *layer_k, datapoint *data, double pull) {
	hidden_layer *aux_k = layer_k;

	while (aux_k) { /* Loops through each neuron of the given layer */
		make_neuron_respond_to_pull(aux_k->n_j, data, pull);
		aux_k = aux_k->next;
	}
}