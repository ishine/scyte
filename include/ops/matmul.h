#ifndef MATMUL_H
#define MATMUL_H

#include "scyte.h"

scyte_node* scyte_matmul(scyte_node* x, scyte_node* y);

void scyte_matmul_forward(scyte_node* node);
void scyte_matmul_backward(scyte_node* node);

#endif
