#ifndef LAYERS_H
#define LAYERS_H

#include "scyte.h"

typedef enum {
    COST_BINARY_CROSS_ENTROPY,
    COST_CROSS_ENTROPY,
    COST_L1,
    COST_L2,
    //COST_HUBER,
} cost_type ;

// Generates a network from a computational graph.
// A network must have at least one scalar cost node (i.e. whose num_dims==0).
scyte_network scyte_make_network(scyte_node* cost_node);

scyte_node* scyte_layer_input(int num_input);
scyte_node* scyte_layer_dense(scyte_node* in, int num_units);
scyte_node* scyte_layer_dropout(scyte_node* in, float dropout_rate);
scyte_node* scyte_layer_layernorm(scyte_node* in);
scyte_node* scyte_layer_cost(scyte_node* t, int num_out, cost_type type);

#endif
