CC = g++
OBJS = main.o conv2D.o fft.o
FLAGS = -lm -lpthread
CFLAGS = -std=c++11

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
