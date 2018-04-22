/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#define cimg_display 0
#include "conv2D.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char** argv)
{
  CImg<double> img("image.bmp");

  /* CImg defines macros for looping over images. Examples:
     http://cimg.eu/reference/group__cimg__loops.html
  */
  cimg_forXY(img,x,y) {
    cout << "x: " << x << " y: " << y << " pixel: " << img(x,y) << endl;
  }
  img.save("new_image.bmp");
	

	return 0;
}
