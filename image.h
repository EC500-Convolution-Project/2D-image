#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>

int get_image_matrix(char **image) {
  unsigned error;
  unsigned char* image1D;
  unsigned width, height;

  error = lodepng_decode32_file(&image1D, &width, &height, "image.png");
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));


  image = (char**)malloc(sizeof(char*)*width);

  printf(" %c \n", image1D[0]);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {

      image[i][j] = image1D[(i*height) + width];
      printf(" %d %d \n", i, j);
    }
    
  return width; //We're only using square images
}

void save(char **image, int N) {
  unsigned width = N;
  unsigned height = N;
  unsigned char* image1D;
  
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      image1D[(i*height) + width] = image[i][j];
  
  unsigned error = lodepng_encode32_file("new_image", image1D, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error)); 
}

void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

