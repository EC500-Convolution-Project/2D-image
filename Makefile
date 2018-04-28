CC = gcc
OBJS = main.o lodepng.o
CFLAGS = -std=c99

default: convolution2D

convolution2D: $(OBJS)
	$(CC) $(CFLAGS) -o convolution2D $(OBJS)

# conv2D.o: conv2D.cpp conv2D.h
# 	$(CC) $(CFLAGS) -c conv2D.cpp -o conv2D.o -g

lodepng.o: lodepng.h

main.o: main.c image.h
	$(CC) $(CFLAGS) image.h -c main.c -g

clean: 
	rm $(OBJS) convolution2D
