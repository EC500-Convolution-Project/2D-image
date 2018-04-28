#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

int main(int argc, char** argv) {
  unsigned error;
  unsigned char* image1D;
  unsigned width, height;

  error = lodepng_decode32_file(&image1D, &width, &height, "image.png");
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  char image[height][width];

  printf(" %c \n", image1D[0]);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image[i][j] = image1D[(i*height) + width];

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image1D[(i*height) + width] = image[i][j];
  
  error = lodepng_encode32_file("new_image.png", image1D, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error)); 
  
}

