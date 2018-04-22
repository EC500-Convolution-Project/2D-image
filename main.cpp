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
	for(int p=0; p<N; p++){
		image[p] = new double[N];
	}


	for(int x = 0; x<N; x++){
		for(int y = 0; y < N; y++){
			image[x][y] = 1.0;

		}
	}


	stacker(image,stack,N);

	for(int i = 0; i < N*N;  i++){
		cout << stack[i]<< endl; 
	}

	unstacker(stack,image,N);

	for(int x = 0; x < N; x++){
		for(int y = 0 ; y< N; y++ ){
			cout<< image[x][y]<< ' ';

		}
		cout<< endl;
	}


	
	

	return 0;
}