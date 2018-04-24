/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#define cimg_display 0
#include "conv2D.h"
#include <iostream>
#include "image.h"
using namespace std;


int main(int argc, char** argv)
{

  double **image;
  int N = get_image_matrix(image);
  save(image, N);


	// Initilize arrays 
	int image_N = 16;
	int filter_N = 3;
	double *  stack = new double[image_N*image_N];
	double *  outstack = new double[image_N*image_N];
	double ** image = new double*[image_N];
	double ** filter = new double*[filter_N];
	double ** padfilter  = new double*[image_N];
	double ** output = new double*[image_N];
	double ** circular = new double*[image_N*image_N];



		// Initlaize massive 2D array for circulant matrix

	for(int p=0; p< image_N*image_N; p++){
		circular[p] = new double[image_N*image_N];
	}


	
	// Initlaize full 2D arrays for images
	for(int p=0; p<image_N; p++){
		image[p] = new double[image_N];
		output[p] = new double[image_N];
		padfilter[p] = new double[image_N];
	}

	// Initlize smaller 2D arrays

		for(int p=0; p<filter_N; p++){
		filter[p] = new double[filter_N];
	}


	for(int x = 0; x<image_N; x++){
		for(int y = 0; y < image_N; y++){
			image[x][y] = x+y;

		}
	}


	for(int x = 0; x<filter_N; x++){
		for(int y = 0; y < filter_N; y++){
			filter[x][y] = x+y;

		}
	}




cout << "this is the image" << endl;
for(int x = 0; x <  image_N; x++){
	for(int y = 0 ; y < image_N ; y++){

		cout << image[x][y] << " "; 

	}
	cout << endl;
}

cout << "this is the filter" << endl;
for(int x = 0; x <  filter_N; x++){
	for(int y = 0 ; y < filter_N ; y++){

		cout << filter[x][y] << " "; 

	}
	cout << endl;
}


padder2D(filter,image,padfilter,image,16);

cout << endl;

cout << "this is the padded filter" << endl;
for(int x = 0; x <  image_N; x++){
	for(int y = 0 ; y < image_N ; y++){

		cout << padfilter[x][y] << " "; 

	}
	cout << endl;
}




circ2(padfilter,circular,16,16);

int circsize = *(&circular[0] + 1) - circular[0]-2 ;

cout << "circular size is " << circsize << endl;


for(int x = 0; x <  circsize; x++){
	for(int y = 0 ; y < circsize ; y++){

		cout << circular[x][y] << " "; 

	}
	cout << endl;
}




stacker(image,stack,image_N);

int stacksize = *(&stack + 1) - stack-2 ;

cout << "stack size is " << stacksize << endl;

for(int i = 0 ; i < stacksize ; i++){
	cout<< stack[i] << endl;
}


cout << endl;

conv2(circular,stack,outstack,256);

int outstacksize = *(&outstack + 1) - outstack-2 ;

cout << "outstack size is " << outstacksize << endl;

for(int i = 0 ; i < outstacksize ; i++){
	cout<< outstack[i] << endl;
}






unstacker(outstack,image,16);


cout << endl;
cout << "final image"<< endl;

for(int x = 0; x <  16; x++){
	for(int y = 0 ; y < 16 ; y++){

		cout << image[x][y] << " "; 

	}
	cout << endl;
}


	return 0;
}

