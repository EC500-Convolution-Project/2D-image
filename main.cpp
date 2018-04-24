/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#define cimg_display 0
#include "conv2D.h"
#include "image.h"

using namespace std;


int main(int argc, char** argv)
{
  double **image;
  int N = get_image_matrix(image);
  save(image, N);
  
  return 0;
}
