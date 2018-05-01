/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "lodepng.h"


#define filter_N 256
#define IMAGE_N 256

double get_time() {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return 1.0*tv.tv_sec+1.0E-6*tv.tv_usec;
}

int main(int argc, char** argv) {

  double start;  // Time measurements
  int filter[filter_N][filter_N] = {{0}};
  int image[IMAGE_N][IMAGE_N] = {{0}};
  int output[IMAGE_N][IMAGE_N] = {{0}};


  for (int i = 0; i < filter_N; i++)
    for (int j = 0; j < filter_N; j++)
      filter[i][j] = 1;
  
  int counter = 0;
  for (int i = 0; i < IMAGE_N; i++) {
    for (int j = 0; j < IMAGE_N; j++) {
      //image[i][j] = (i+1)*(j+1);
      image[i][j] = 1;
      //image[i][j] = ++counter;
    }
  }


  /*  
  printf("\n \n \n convolution input:\n");
  for (int i = 0; i < IMAGE_N; i++) {
    for (int j = 0; j < IMAGE_N; j++)
        printf("%d ", image[i][j]);
    printf("\n");
  }
  */

  //printf("N: %d Last element in array is N^2: %d \n", IMAGE_N, image[IMAGE_N-1][IMAGE_N-1]);


  /* Convolve here */
  start = get_time();


  #pragma acc kernels copy(image[0:IMAGE_N][0:IMAGE_N]), copyout(output[0:IMAGE_N][0:IMAGE_N])
  {
    for(int x = 0; x < IMAGE_N; x++) 
      for(int y = 0; y < IMAGE_N; y++)
	for(int x_pos = 0; x_pos <filter_N; x_pos++)
	  for(int y_pos = 0 ; y_pos < filter_N; y_pos++) 
	    if (x+x_pos < IMAGE_N && y+y_pos < IMAGE_N){ //improve
	      // printf("%d %d \n", x, y);
	      output[x][y] += image[x+x_pos][y+y_pos]*filter[x_pos][y_pos];
	    }
  }
  /*
  printf("\n \n \n convolution output:\n");
  for (int i = 0; i < IMAGE_N; i++) {
    for (int j = 0; j < IMAGE_N; j++)
        printf("%d ", output[i][j]);
    printf("\n");
  }
  */
  double runtime = get_time() - start;
  printf( "%d \t %8.4f seconds \n", IMAGE_N, runtime );
  
}

