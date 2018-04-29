/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#define cimg_display 0
#include "conv2D.h"
#include <iostream>
#include <chrono>
#include "image.h"

using namespace std;


int main(int argc, char** argv)
{

	for(int N = 16; N <= 5000; N=N*2){


  // TIMING LINE 1: Get the starting timestamp. 
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
    std::chrono::steady_clock::now();	

  
  //double **image = 0;
  //int N = ;

//Convolve here!

  


	// Initilize arrays 
	//int image_N = get_image_matrix(image);
	int image_N = N;
	int filter_N = 16;
	//double *  stack = new double[image_N*image_N];
	//double *  outstack = new double[image_N*image_N];
	double ** image = new double*[image_N];
	double ** filter = new double*[filter_N];
	//double ** padfilter  = new double*[image_N];
	double ** output = new double*[image_N];
	//double ** circular = new double*[image_N*image_N];


		// Initlaize massive 2D array for circulant matrix

	for(int p=0; p< image_N*image_N; p++){
		//circular[p] = new double[image_N*image_N];
		//outstack[p] = 0;
	}


	
	// Initlaize full 2D arrays for images
	for(int p=0; p<image_N; p++){
		image[p] = new double[image_N];
		output[p] = new double[image_N];
		//padfilter[p] = new double[image_N];
	}

	// Initlize smaller 2D arrays

		for(int p=0; p<filter_N; p++){
		filter[p] = new double[filter_N];
	}


	for(int x = 0; x<image_N; x++){
		for(int y = 0; y < image_N; y++){
			image[x][y] = rand()%255;
			//padfilter[x][y] = 0; 
			output[x][y] = 0;

		}
	}


	for(int x = 0; x<filter_N; x++){
		for(int y = 0; y < filter_N; y++){
			if(x == 1 && y == 1){
				filter[x][y] = 1;
			}
			else{
			filter[x][y] = 0;

		}
	}
}




//cout << "this is the image" << endl;
//for(int x = 0; x <  image_N; x++){
//	for(int y = 0 ; y < image_N ; y++){

		//cout << image[x][y] << " "; 

	//}
	//cout << endl;
//}

//cout << "this is the filter" << endl;
//for(int x = 0; x <  filter_N; x++){
//	for(int y = 0 ; y < filter_N ; y++){

		//cout << filter[x][y] << " "; 

//	}
	//cout << endl;
//}


//adder2D(filter,image,padfilter,image,image_N);

//cout << endl;

//cout << "this is the padded filter" << endl;
//for(int x = 0; x <  image_N; x++){
//	for(int y = 0 ; y < image_N ; y++){

		//cout << padfilter[x][y] << " "; 

//	}
	//cout << endl;
//}




//circ2(padfilter,circular,image_N,image_N);

//int circsize = *(&circular[0] + 1) - circular[0]-2 ;

//cout << "circular size is " << circsize << endl;


//for(int x = 0; x <  circsize; x++){
//	for(int y = 0 ; y < circsize ; y++){

		//cout << circular[x][y] << " "; 

	//}
	//cout << endl;
//}




//stacker(image,stack,image_N);

//int stacksize = *(&stack + 1) - stack-2 ;

//cout << "stack size is " << stacksize << endl;

//for(int i = 0 ; i < stacksize ; i++){
	//cout<< stack[i] << endl;
//}


//cout << endl;

//conv2(circular,stack,outstack,image_N*image_N);

//int outstacksize = *(&outstack + 1) - outstack-2 ;

//cout << "outstack size is " << outstacksize << endl;

//for(int i = 0 ; i < image_N*image_N ; i++){
	//cout<< outstack[i] << endl;
//}



//unstacker(outstack,image,image_N);

conv2_dir(image, filter,output,image_N,filter_N);


//cout << endl;
//cout << "final image"<< endl;

//for(int x = 0; x <  image_N; x++){
//	for(int y = 0 ; y <image_N ; y++){

		//cout << output[x][y] << " "; 

//	}
	//cout << endl;
//}

//save(output, image_N);


 // TIMING LINE 2: Get the ending timestamp.
  std::chrono::time_point<std::chrono::steady_clock> end_time =
    std::chrono::steady_clock::now();

  // TIMING LINE 3: Compute the difference.
  std::chrono::duration<double> difference_in_time = end_time - begin_time;

  // TIMING LINE 4: Get the difference in seconds.
  double difference_in_seconds = difference_in_time.count();

// Print the integral.
  //if (my_rank == 0){
  cout << N << ' ';
  printf(" %.8f seconds.\n",difference_in_seconds);
 
}

	return 0;
}

