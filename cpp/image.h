#include "CImg.h"

using namespace cimg_library;


/*
  Takes an image filename (defaults image.bmp), fills 2D array with
  pixels and returns image width.
  double **image - Pointer to 2D array to be populated
 */
int get_image_matrix(double **&image) {

  CImg<double> img("image.bmp");
  image = new double*[img.width()];
  for (int i = 0; i < img.width(); i++) image[i] = new double[img.height()];

  /* 
     CImg defines macros for looping over images. Examples:
     http://cimg.eu/reference/group__cimg__loops.html
  */

  cimg_forXY(img,x,y) image[x][y] = img(x,y);

  return img.width(); //We're only using square images
}

void save(double **image, int N) {
  CImg<double> img(N, N);
  cimg_forXY(img,x,y) img(x,y) =  image[x][y];
  img.save("new_image.bmp");
}
