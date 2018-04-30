COMPILER ?= PGI-tesla
CC = pgcc
CFLAGS = -DUSE_DOUBLE
OBJS = main.o lodepng.o 

ifeq ($(COMPILER),GCC)
	CFLAGS += -std=c99 -march=native -O3 -lm
else ifeq ($(COMPILER),PGI)
	CFLAGS += -fast
else ifeq ($(COMPILER),PGI-tesla)
	CFLAGS += -Minfo=accel -fast -acc -ta=tesla:cc60
else ifeq ($(COMPILER),PGI-multicore)
	CFLAGS += -Minfo=accel -fast -acc -ta=multicore
endif



default: convolution2D

convolution2D: $(OBJS)
	$(CC) $(CFLAGS) -o convolution2D $(OBJS)

lodepng.o : lodepng.h
	pgcc lodepng.c -c -o lodepng.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c  -g

clean: 
	rm $(OBJS) convolution2D
