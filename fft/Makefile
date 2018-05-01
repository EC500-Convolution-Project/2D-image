COMPILER ?= PGI-multicore
CC = pgc++
CFLAGS = -DUSE_DOUBLE
OBJS = main.o conv2D.o fft.o

ifeq ($(COMPILER),GCC)
	CFLAGS += 
else ifeq ($(COMPILER),PGI)
	CFLAGS += -fast
else ifeq ($(COMPILER),PGI-tesla)
	CFLAGS += -Minfo=accel -fast -acc -ta=tesla:cc60
else ifeq ($(COMPILER),PGI-multicore)
	CFLAGS += -Minfo=accel -fast -acc -ta=multicore
endif



default: convolution2D

convolution2D: $(OBJS)
	$(CC) $(CFLAGS) -o convolution2D $(OBJS) $(FLAGS)

conv2D.o: conv2D.cpp conv2D.h
	$(CC) $(CFLAGS) -c conv2D.cpp -o conv2D.o -g

fft.o: fft.cpp fft.h
	$(CC) $(CFLAGS) -c fft.cpp -o fft.o -g

main.o: main.cpp conv2D.h 
	$(CC) $(CFLAGS) -c main.cpp -g

clean: 
	rm $(OBJS) convolution2D
