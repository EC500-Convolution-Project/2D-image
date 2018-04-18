CC=g++

OBJS=main.o conv2D.o

default: convolution2D

convolution2D: $(OBJS)
	$(CC) -o convolution2D $(OBJS) 

conv2D.o: conv2D.cpp conv2D.h
	$(CC) -c conv2D.cpp -o conv2D.o 
	
main.o: main.cpp conv2D.h
	$(CC) -c main.cpp

clean: 
	rm $(OBJS) convolution2D