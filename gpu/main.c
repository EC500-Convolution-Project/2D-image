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


#define filter_N 16
#define image_N 64

double get_time() {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return 1.0*tv.tv_sec+1.0E-6*tv.tv_usec;
}

int main(int argc, char** argv) {
  unsigned error;
  unsigned char* image1D;
  unsigned width, height;
  double start;  // Time measurements
  char filter[filter_N][filter_N] = {{0}};
  filter[1][1] = 1;
  
  error = lodepng_decode32_file(&image1D, &width, &height, "image.png");
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  char image[image_N][image_N] = {{0}};
  char output[image_N][image_N] = {{0}};

  /* Need to convert 1D iamge to 2D */
  
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image[i][j] = image1D[(i*height) + width];

  /* Convolve here */
  start = get_time();

  int N = width;
  #pragma acc kernels
  for(int x = 0; x < N; x++) 
    for(int y = 0; y < N ; y++)
      for(int x_pos = 0; x_pos <filter_N; x_pos++)
	for(int y_pos = 0 ; y_pos < filter_N; y_pos++) 
	  if (x+x_pos < N && y+y_pos < N)
	    output[x][y] += image[x+x_pos][y+y_pos]*filter[x_pos][y_pos];
	  

  double runtime = get_time() - start;
  printf( "Runtime: %8.4f \n", runtime );
  
  /* Coonvert 2D image baxck to 1D for saving */
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image1D[(i*height) + width] = output[i][j];
  
  error = lodepng_encode32_file("new_image.png", image1D, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error)); 
  
}
