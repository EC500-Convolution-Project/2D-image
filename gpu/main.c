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


#define filter_N 3
#define IMAGE_N 16

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
  int filter[filter_N][filter_N] = {{0}};
  
  error = lodepng_decode32_file(&image1D, &width, &height, "image.png");
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  int image[IMAGE_N][IMAGE_N] = {{0}};
  int output[IMAGE_N][IMAGE_N] = {{0}};

  /* Need to convert 1D iamge to 2D */
  
for (int i = 0; i < IMAGE_N; i++) {
    for (int j = 0; j < IMAGE_N; j++) {
        //image[i][j] = (i+1)*(j+1);
        image[i][j] = 1;
    }
}
//printf("N: %d Last element in array is N^2: %d \n", IMAGE_N, image[IMAGE_N-1][IMAGE_N-1]);


  /* Convolve here */
  start = get_time();


  #pragma acc kernels copy(image[0:IMAGE_N][0:IMAGE_N]), copyout(output[0:IMAGE_N][0:IMAGE_N])
  {
    for(int x = 0; x < IMAGE_N; x++) 
      for(int y = 0; y < IMAGE_N; y++)
	for(int x_pos = 0; x_pos <filter_N; x_pos++)
	  for(int y_pos = 0 ; y_pos < filter_N; y_pos++) 
	    if (x+x_pos < height && y+y_pos < width){ //improve
	      // printf("%d %d \n", x, y);
	      output[x][y] += image[x+x_pos][y+y_pos]*filter[x_pos][y_pos];
	    }
  }



/* for (int i = 0; i < height; i++) { */
/*     for (int j = 0; j < width; j++) { */
 
/*       printf("%u ", output[i][j]); */
/*     } */
/* printf("\n"); */
/* } */
  double runtime = get_time() - start;
printf( "%d \t %8.4f seconds \n", IMAGE_N, runtime );
  
  /* Coonvert 2D image baxck to 1D for saving */
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image1D[(i*height) + width] = output[i][j];
  
  error = lodepng_encode32_file("new_image.png", image1D, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error)); 
  
}

