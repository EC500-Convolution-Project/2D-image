/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#include "conv2D.h"
using namespace std;

/*
	*** INPUTS ***
	array is an array of doubles that need to be made circulant (assumes already zero padded)
	circArray is where the circulant matrix produced will be stored
	
*/
void circ(double * array, double ** circArray){

}

/*
	*** INPUTS ***
	f is 2D matrix of our signal/image
	h is 2D matrix of our TF/Filter/Kernel
	fpad is place to put zero-padded f
	hpad is place to put zero-padded h
*/
void padder2D(double ** f, double ** h, double ** fpad, double** hpad){

}

/*
	*** INPUTS ***
	which - char signifying if stacking or unstacking (s or u)
	image - matrix to be row stacked or storage for unstacked image
	stacked - array to be unstacked or storage for stacked image
*/
void stacker(double ** image, double * stacked, char which){

}