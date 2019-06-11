OPENBLAS ?= 0
OPENCV ?= 0
OPENMP ?= 0
DEBUG  ?= 0

OBJ= main.o blas.o utils.o scyte.o op.o
OBJ+= add.o sub.o square.o exp.o log.o relu.o sigmoid.o tanh.o softmax.o dropout.o sin.o mul.o mse.o matmul.o cmatmul.o max.o avg.o select.o reduce_sum.o reduce_mean.o slice.o concat.o reshape.o logxent.o categoricalxent.o normalize.o
EXECOBJA= 

VPATH=./src/:./examples:./src/ops
EXEC=scyte
OBJDIR=./obj/

CC=gcc
OPTS=-Ofast
LDFLAGS= -lm -pthread
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq ($(OPENMP), 1)
CFLAGS+= -fopenmp
endif

ifeq ($(OPENBLAS), 1)
CFLAGS+= -DOPENBLAS
LDFLAGS+= `pkg-config --libs openblas`
COMMON+= `pkg-config --cflags openblas`
endif

ifeq ($(DEBUG), 1)
OPTS=-O0 -g
endif

CFLAGS+=$(OPTS)

ifeq ($(OPENCV), 1)
COMMON+= -DOPENCV
CFLAGS+= -DOPENCV
LDFLAGS+= `pkg-config --libs opencv`
COMMON+= `pkg-config --cflags opencv`
endif

EXECOBJS = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS   = $(addprefix $(OBJDIR), $(OBJ))
DEPS   = $(wildcard include/*.h) Makefile

all: obj $(EXEC)

$(EXEC): $(OBJS) $(EXECOBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean
clean:
	rm -rf $(OBJS) $(ALIB) $(EXEC) $(EXECOBJS) $(OBJDIR)/* $(OBJDIR)
