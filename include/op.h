#ifndef OP_H
#define OP_H

#include "scyte.h"

#include "ops/add.h"
#include "ops/sub.h"
#include "ops/square.h"
#include "ops/exp.h"
#include "ops/log.h"
#include "ops/relu.h"
#include "ops/sigmoid.h"
#include "ops/tanh.h"
#include "ops/softmax.h"
#include "ops/dropout.h"
#include "ops/sin.h"
#include "ops/mul.h"
#include "ops/mse.h"
#include "ops/matmul.h"
#include "ops/cmatmul.h"
#include "ops/max.h"
#include "ops/avg.h"
#include "ops/select.h"
#include "ops/reduce_sum.h"
#include "ops/reduce_mean.h"
#include "ops/slice.h"
#include "ops/concat.h"
#include "ops/reshape.h"
#include "ops/logxent.h"
#include "ops/categoricalxent.h"
#include "ops/normalize.h"
#include "ops/l1_norm.h"

scyte_node* make_op_node(scyte_op_type type, int num_dims, int num_children);
scyte_node* make_op1_node(scyte_op_type type, scyte_node* x);
scyte_node* make_op2_node(scyte_op_type type, scyte_node* x, scyte_node* y);
scyte_node* make_opn_node(scyte_op_type type, int n, scyte_node** x);
void free_op_node(scyte_node* node);

char* scyte_get_op_string(scyte_op_type op_type);
scyte_op_type scyte_get_op_type(char* s);

void (*scyte_get_forward_function(scyte_op_type op_type)) (struct scyte_node*);
void (*scyte_get_backward_function(scyte_op_type op_type)) (struct scyte_node*);

// shape0 is product of all shapes before axis,
// while shape1 is product of all shapes after axis
void get_reduced_dimensions(scyte_node* node, int axis, int* shape0, int* shape1);

// checks if gradients can flow through the op-node, if so set type to VAR
void scyte_propagate_gradient_mark(scyte_node* node);

#endif
