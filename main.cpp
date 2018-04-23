/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#include "conv2D.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{


	int N = 16;
	double *  stack = new double[N*N];
	double ** image = new double*[N];
	double ** filter = new double*[N-4];
	double ** output = new double*[N];
	

	for(int p=0; p<N; p++){
		image[p] = new double[N];
	}

		for(int p=0; p<N-4; p++){
		filter[p] = new double[N-4];
	}


	for(int x = 0; x<N; x++){
		for(int y = 0; y < N; y++){
			image[x][y] = 0.0;

		}
	}


	for(int x = 0; x<N-4; x++){
		for(int y = 0; y < N-4; y++){
			filter[x][y] = 1.0;

		}
	}



for(int x = 0; x<N; x++){
		for(int y = 0; y < N; y++){
			cout << image[x][y] << " ";

		}
		cout << endl;
	}



padder2D(filter, filter,image,image,2);


cout << endl;

for(int x = 0; x<N; x++){
		for(int y = 0; y < N; y++){
			cout << image[x][y] << " ";

		}
		cout << endl;
	}



	

	return 0;
}